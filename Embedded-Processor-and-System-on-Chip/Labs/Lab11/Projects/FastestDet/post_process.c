

#include "post_process.h"
#include "stb_image.h"
#include "stb_image_write.h"

#define JPG_FILE_LENGTH 1028 
#define JPG_CLASS_LENGTH 128
void GenerateOutputPicture(struct image_data *input_img, struct image_data *output_img, const char* filename)
{
    printf("GenerateOutputPicture\n");
    float conf_thresh = 0.8;
    float nms_thresh = 0.45;

    int C, H, W;
    int size;
    int num_cls;
    
    H = output_img->shape[0];
    W = output_img->shape[1];
    C = output_img->shape[2];

    size = C * H * W;
    //识别的手势类型数量
    num_cls = C - 5;

    // `pred = preds.permute(0, 2, 3, 1)`
    // chw2hwc(preds.data, C, H, W);

    float* pobj = (float *)malloc(sizeof(float) * H*W*1);
    float* preg = (float *)malloc(sizeof(float) * H*W*4);
    float* pcls = (float *)malloc(sizeof(float) * H*W*num_cls);

    int pobj_idx, preg_idx, pcls_idx;
    pobj_idx = 0;
    preg_idx = 0;
    pcls_idx = 0;
    // `pobj = pred[:, :, :, 0].unsqueeze(dim=-1)`
    // `preg = pred[:, :, :, 1:5]`
    // `pcls = pred[:, :, :, 5:]`
    for (int i = 0; i < size; i+=C)
    {
        pobj[pobj_idx++] = output_img->data[i];
        memcpy(preg+preg_idx, output_img->data+i+1, sizeof(float)*4);
        preg_idx += 4;
        memcpy(pcls+pcls_idx, output_img->data+i+5, sizeof(float)*num_cls);
        pcls_idx += num_cls;
    }

    float* bboxes    = (float *) malloc(sizeof(float) * H*W*6);
    float* max_value = (float *) malloc(sizeof(float) * H*W);
    int*   max_idx   = (int *)   malloc(sizeof(int)   * H*W);
    argmax(max_value, max_idx, pcls, H*W, num_cls);
    pobj_idx = 0;
    for (int i = 0; i < H*W*6; i+=6)
    {
        bboxes[i+4] = pow(pobj[pobj_idx], 0.6) * pow(max_value[pobj_idx], 0.4);
        bboxes[i+5] = max_idx[pobj_idx];
        pobj_idx++;
    }
    free(pcls);
    free(pobj);
    free(max_value);
    free(max_idx);

    int* gx = (int *)malloc(sizeof(int) * H*W);
    int* gy = (int *)malloc(sizeof(int) * H*W);
    meshgrid(gx, gy, H, W);

    float bcx, bcy, bw, bh;
    for (int i = 0; i < H*W; i++)
    {
        bboxes[6*i]   = (tanh(preg[4*i]) + gx[i])*1.0 / W;
        bboxes[6*i+1] = (tanh(preg[4*i+1]) + gy[i])*1.0 / H;
        bboxes[6*i+2] = sigmoid(preg[4*i+2]);
        bboxes[6*i+3] = sigmoid(preg[4*i+3]);
    }
    free(gx);
    free(gy);
    free(preg);

    struct image_data* box_img = calloc(1, sizeof(struct image_data));
    box_img->data = bboxes;
    
        
    // in hwc : h=H*W（20*20） w=6 c=1
    // box_img->data = (float*)malloc(sizeof(float) * (width * height * depth)); 
    box_img->shape = (uint32_t*)malloc(sizeof(uint32_t) * 3);
    box_img->shape[0] = H*W;
    box_img->shape[1] = 6;
    box_img->shape[2] = 1;
    box_img->dim = 3;

    struct image_data* output_bboxes = non_max_suppression(box_img, conf_thresh, nms_thresh);

    // generate jpg
    int in_h = input_img->shape[0];
    int in_w = input_img->shape[1];
    int in_c = input_img->shape[2];
    int in_size = in_c * in_w * in_h;

    uint8_t* input_char = (uint8_t *)malloc(sizeof(char) * in_size);
    for (int i = 0; i < in_size; i++)
    {
        input_char[i] = (uint8_t)(input_img->data[i] * 255);
    }

    int is_gesture = 0;
    if (output_bboxes->data != NULL)
    {
        // print_tensor(output_bboxes.data, output_bboxes.c, output_bboxes.h, output_bboxes.w);
        /* process the detection result */
        int x1, x2, y1, y2;
        for (int i = 0; i < output_bboxes->shape[0]; i++)
        {   
            printf("output_bboxes[0]: %f\n", output_bboxes->data[i*6+0]);
            printf("output_bboxes[1]: %f\n", output_bboxes->data[i*6+1]);
            printf("output_bboxes[2]: %f\n", output_bboxes->data[i*6+2]);
            printf("output_bboxes[3]: %f\n", output_bboxes->data[i*6+3]);
            printf("output_bboxes[4]: %f\n", output_bboxes->data[i*6+4]);
            printf("output_bboxes[5]: %f\n", output_bboxes->data[i*6+5]);

            int hw = (in_w > in_h) ? in_w : in_h;
            x1 = (int)((output_bboxes->data[i*6+0] - 0.5*output_bboxes->data[i*6+2]) * hw);
            y1 = (int)((output_bboxes->data[i*6+1] - 0.5*output_bboxes->data[i*6+3]) * hw);
            x2 = (int)((output_bboxes->data[i*6+0] + 0.5*output_bboxes->data[i*6+2]) * hw);
            y2 = (int)((output_bboxes->data[i*6+1] + 0.5*output_bboxes->data[i*6+3]) * hw);

            drawbox(input_char, in_w, in_h, x1, y1, x2, y2, 0, 255, 125);
            
            char jpgname[JPG_FILE_LENGTH] = {0};
            char classname[JPG_CLASS_LENGTH] = {0};
            int class = (int)output_bboxes->data[i*6+5];

            /**************optional: 为生成的图片添加手势识别结果与置信度*********************/

            snprintf(jpgname, JPG_FILE_LENGTH, "%s_%d_%f.jpg", filename, class, output_bboxes->data[i*6+4]);
            save_rgb(jpgname, in_w, in_h, 3, input_char, 80);
            is_gesture = 1;
        }
    }
    else
    {
        // fprintf(stderr, "No bbox left.\n");
        is_gesture = 0;
    }

    fprintf(
        stderr, 
        "-------------------------------\n"
        "Is Gesture         %d\n"
        "-------------------------------\n",
        is_gesture
    );

    free(bboxes);
    free_image_data(box_img);
    free_image_data(output_bboxes);
    
    return;
}

int chw2hwc(float* src, int C, int H, int W)
{
    int     size = C * H * W;
    int     index = 0;
    float*  temp  = (float *)malloc(size * sizeof(float));

    for (int i = 0; i < size; i++)
    {
        index = H * W * (i - C * (i / C)) + (i / C);
        temp[i] = src[index];
    }

    for (int i = 0; i < size; i++)
    {
        src[i] = temp[i];
    }
    free(temp);
    return size;
}

void argmax(float* value, int* idx, float* array, int h, int w)
{
    float max_val;
    int max_idx;
    for (int i = 0; i < h; i++)
    {
        max_val = array[i*w];
        max_idx = 0;
        for (int j = 0; j < w; j++)
        {
            if (array[i*w+j] > max_val)
            {
                max_val = array[i*w+j];
                max_idx = j;
            }
        }
        value[i] = max_val;
        idx[i] = max_idx;
    }
}

void meshgrid(int* gx, int* gy, int h, int w)
{
    int size = h * w;
    for (int i = 0; i < size; i++)
    {
        gx[i] = i % w;
        gy[i] = i / w;
    }
}

float sigmoid(float x)
{
    return 1.0 / (1.0 + exp(-x));
}

float bbox_iou(float* box1, float* box2, int xyxy)
{
    float b1_x1, b1_y1, b1_x2, b1_y2;
    float b2_x1, b2_y1, b2_x2, b2_y2;

    if (xyxy)
    {
        // x, y, x, y
        b1_x1 = box1[0];
        b1_y1 = box1[1];
        b1_x2 = box1[2];
        b1_y2 = box1[3];

        b2_x1 = box2[0];
        b2_y1 = box2[1];
        b2_x2 = box2[2];
        b2_y2 = box2[3];
    }
    else
    {
        // x, y, w, h
        b1_x1 = box1[0] - box1[2] / 2.0;
        b1_x2 = box1[0] + box1[2] / 2.0;
        b1_y1 = box1[1] - box1[3] / 2.0;
        b1_y2 = box1[1] + box1[3] / 2.0;

        b2_x1 = box2[0] - box2[2] / 2.0;
        b2_x2 = box2[0] + box2[2] / 2.0;
        b2_y1 = box2[1] - box2[3] / 2.0;
        b2_y2 = box2[1] + box2[3] / 2.0;
    }

    float inter_area, union_area;
    inter_area = MAX_VALUE(0, (MIN_VALUE(b1_x2, b2_x2) - MAX_VALUE(b1_x1, b2_x1))) * MAX_VALUE(0, (MIN_VALUE(b1_y2, b2_y2) - MAX_VALUE(b1_y1, b2_y1)));
    union_area = ((b1_x2 - b1_x1) * (b1_y2 - b1_y1) + 1e-16) + (b2_x2 - b2_x1) * (b2_y2 - b2_y1) - inter_area;

    return inter_area / union_area;
}

// 非极大值抑制函数
struct image_data* non_max_suppression(struct image_data *input_img, float conf_thres, float nms_thres)
{
    /*
    1. 非极大值抑制函数输入数据：
        1. image_datad 的数据结构在hhb_out/process.h中，如下
            struct image_data {
                float* data;      // the data of image
                uint32_t* shape;  // the shape of image, default to HWC
                uint32_t dim;     // the number of shape
            };
            a).通过input_img->data拿到浮点数据的指针数组。
            b).输入数据的形状shape为3维数组，
                H = 20*20 //代表共400个备选框，非极大值抑制即在这400个备选框中选出满足要求的框
                W = 6   //代表每个备选框的6个参数，6个值依次为：框的中心点的坐标x、y，框的宽度w，框的高度h，框对于识别结果的置信度，类别识别结果的编号。可能类别识别结果共六个（编号0-5），参考文档
                C = 1 //无意义
                data的数据排布方式为HWC，C维度是数据排布的最内层维度（举例而言，指针数组的前6个值为第1个框的6个参数）
        2. conf_thres为置信度的阈值。置信度低于该阈值的框应该被去除。已经设置为0.8
        3. nms_thres为交并比阈值，当两个备选框的交并比高于该阈值，则两个框中置信度较低的框应该被去除.已经设置为0.45

    2. 非极大值抑制函数主要工作：
        参考博客：https://zhuanlan.zhihu.com/output_data/587225859

        step1：先将置信度低于conf_thres的框移除，并将所有的边界框按照类别进行区分；

        step2：把每个类别中的边界框，按照置信度从高到低进行降序排列；

        step3：选择某类别所有边界框中置信度最高的边界框bbox1，然后从该类别的所有边界框列表中将该置信度最高的边界框bbox1移除并同时添加到输出列表中；

        step4：依次计算该bbox1和该类别边界框列表中剩余的bbox计算IOU；

        step5：将IOU与NMS预设阈值nms_thres进行比较，若某bbox与bbox1的IOU大于nms_thres，即视为bbox1的“邻域”，则在该类别边界框列表中移除该bbox，即去除冗余边界框；

        step6：重复step3~step5，直至该类别的所有边界框列表为空，此时即为完成了一个物体类别的遍历；

        step7：重复step2~step6，依次完成所有物体类别的NMS后处理过程；

        step8：输出列表即为想要输出的检测框，NMS流程结束。
    3. 非极大值抑制函数输出
        output_box_count为输出框的数量
        将输出数据赋值给output_data。输出数据保持HWC数据布局，与输入数据类似
        若无满足置信度阈值的框，则可保持output_data指针为空指针。

    */
    uint32_t input_dim = input_img->dim;
    int input_H = input_img->shape[0]; 
    int input_W = input_img->shape[0];
    int input_C = input_img->shape[0];

    int output_box_count = 0;// num of output boxes.
    float* output_data;// point of output data.

    // code here












    struct image_data* box_output = calloc(1, sizeof(struct image_data));
    box_output->data = output_data;
    // hwc h=count w=6 c=1
    box_output->shape = (uint32_t*)malloc(sizeof(uint32_t) * 3);
    box_output->shape[0] = output_box_count;
    box_output->shape[1] = 6;
    box_output->shape[2] = 1;
    box_output->dim = 3;
    // free(output_data);

    return box_output;
}

void confQuickSort(float* s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        float x[6];
        memmove(x, &s[6*l], sizeof(float) * 6);
        while (i < j)
        {
            while (i < j && s[6*j+4] <= x[4])  // right->left, find first number > x
                j--;
            if (i < j)
            {
                memmove(&s[6*i], &s[6*j], sizeof(float) * 6);
                i++;
            }
            
            while(i < j && s[6*i+4] > x[4])  // left->right, find first number <= x
                i++;  
            if(i < j)
            {
                memmove(&s[6*j], &s[6*i], sizeof(float) * 6);
                j--;
            }
        }
        memmove(&s[6*i], x, sizeof(float) * 6);
        confQuickSort(s, l, i - 1);
        confQuickSort(s, i + 1, r);
    }
}

void drawbox(unsigned char* data, int w, int h, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b)
{
    int i;
    if (x1 < 0)
        x1 = 0;
    if (x1 >= w)
        x1 = w - 1;
    if (x2 < 0)
        x2 = 0;
    if (x2 >= w)
        x2 = w - 1;

    if (y1 < 0)
        y1 = 0;
    if (y1 >= h)
        y1 = h - 1;
    if (y2 < 0)
        y2 = 0;
    if (y2 >= h)
        y2 = h - 1;

    for (i = x1; i <= x2; ++i)
    {
        data[3*(i + y1 * w) + 0] = r;
        data[3*(i + y2 * w) + 0] = r;

        data[3*(i + y1 * w) + 1] = g;
        data[3*(i + y2 * w) + 1] = g;

        data[3*(i + y1 * w) + 2] = b;
        data[3*(i + y2 * w) + 2] = b;
    }
    for (i = y1; i <= y2; ++i)
    {
        data[3*(x1 + i * w) + 0] = r;
        data[3*(x2 + i * w) + 0] = r;

        data[3*(x1 + i * w) + 1] = g;
        data[3*(x2 + i * w) + 1] = g;

        data[3*(x1 + i * w) + 2] = b;
        data[3*(x2 + i * w) + 2] = b;
    }
}

void print_tensor(float* data, int C, int H, int W)
{
    for (int c = 0; c < C; c++)
    {
        for (int h = 0; h < H; h++)
        {
            fprintf(stderr, "[");
            for (int w = 0; w < W; w++)
            {
                fprintf(stderr, "%f, ", data[c*(H)*(W) + h*(W) + w]);
            }
            fprintf(stderr, "]\n");
        }
        fprintf(stderr, "----------------------------\n");
    }
    fprintf(stderr, "\n");
}

void save_rgb(const char *filename, int x, int y, int comp, const void *data, int quality)
{
    stbi_write_jpg(filename, x, y, comp, data, quality);
    return;
}


