#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "work.h"




// Task 1: 编写交并比IOU计算函数
/*
输入：
    rectangle_box A, rectangle_box B:
        float x,y                   矩形框的中心点坐标
        float w,h                   矩形框的宽和高 

输出：交并比计算结果，一个float类型浮点数
*/
float iou_compute(rectangle_box A, rectangle_box B)
{
    //code here
	float x_a_left   = A.x - A.w/2, x_b_left   = B.x - B.w/2;
	float x_a_right  = A.x + A.w/2, x_b_right  = B.x + B.w/2;
	float y_a_top    = A.y + A.h/2, y_b_top    = B.y + B.h/2;
	float y_a_bottom = A.y - A.h/2, y_b_bottom = B.y - B.h/2;
	
	float i_w = fmin(x_a_right, x_b_right) - fmax(x_a_left  , x_b_left  );
	float i_h = fmin(y_a_top  , y_b_top  ) - fmax(y_a_bottom, y_b_bottom);
	i_w = (i_w > 0) ? i_w : 0;
	i_h = (i_h > 0) ? i_h : 0;
	float iou = (i_w * i_h) / (A.w * A.h + B.w * B.h - i_w * i_h);
	iou = (iou >= 0 && iou <= 1) ? iou : 0;
	return iou;
}






// Task 2: 编写卷积函数(optional)
/*
输入：
    layer_params para:
        input_w, input_h, input_c   输入特征图的宽、高、通道数(w*h*c)
        kernel_size, kernel_n       卷积核尺寸(size*size)、卷积核数量(n)
        stride                      卷积步长
        pad                         补0的数量，上下左右对称补0
    float *input:                   输入特征图数据，平铺的一维数组
    float *weight:                  卷积核的权重数据，平铺的一维数组
    float *output:                  保存计算结果的一维数组
*/
void convolutional_compute(layer_params para, float* input, float* weight, float* output)
{

    //code here
    int i,j,k;
    int c_i,c_j,c_k;
    int pad = para.pad;
    int kernel_size = para.kernel_size;
    int stride = para.stride;
    
    //step1 padding
    float *tmp_pad;
    int size_of_tmp1;
    size_of_tmp1 = (para.input_w + 2*pad) * (para.input_h + 2*pad) * para.input_c;
    tmp_pad = (float*)malloc(size_of_tmp1*sizeof(float));

    for (k=0;k<para.input_c;k++)
	for(j=0;j<para.input_h + 2*pad; j++)
	    for(i=0;i<para.input_w + 2*pad; i++)
	    {
		if(i<pad || j<pad || i>= (para.input_w + pad) || j >= (para.input_h + pad))
		    tmp_pad[i + j*(para.input_w + 2*pad) + k * (para.input_w + 2*pad)*(para.input_h + 2*pad)] = 0.0;
		else
		{
		    tmp_pad[i + j*(para.input_w + 2*pad) + k * (para.input_w + 2*pad)*(para.input_h + 2*pad)] = \
                    input[(i-pad) + (j-pad) * para.input_w + k * (para.input_w) * (para.input_h)];
                }
	    }
	
    //step2 convolution
    int padding_size_w = para.input_w + 2*pad;
    int padding_size_h = para.input_h + 2*pad;
    int padding_size_c = para.input_c;
    
    int conv_size_w = (padding_size_w - kernel_size) / stride + 1;
    int conv_size_h = (padding_size_h - kernel_size) / stride + 1;
    int conv_size_c = para.kernel_n;
    
    float conv_tmp;
    
    for (k=0; k<conv_size_c; k++)
        for(j=0; j<conv_size_h; j++)
            for(i=0; i<conv_size_w; i++)
            {   
                conv_tmp = 0;
                for (c_k=0; c_k<padding_size_c; c_k++)
                    for(c_j=0; c_j<kernel_size; c_j++)
                        for(c_i=0; c_i<kernel_size; c_i++)
                        {
                            conv_tmp += tmp_pad[(i*stride + c_i) + (j*stride*padding_size_w + padding_size_w * c_j) + \
                                        (padding_size_w * padding_size_h * c_k)] * 
                                        weight[c_i + c_j*kernel_size + c_k*kernel_size*kernel_size + k*kernel_size*kernel_size*padding_size_c];
							                                                                    
                        }
              	output[i + j*conv_size_w + k*conv_size_h*conv_size_w] = conv_tmp;               
            }
    
    free(tmp_pad);
  
    return;  
}



// Task 3: 编写最大值池化函数(optional)
/*
输入：
    layer_params para:
        input_w, input_h, input_c   输入特征图的宽、高、通道数(w*h*c)
        kernel_size                 最大值池化的核尺寸(size*size)
        kernel_n                    无意义
        stride                      池化步长
        pad                         在Darknet中无实际意义，详见文档说明
    float *input:                   输入特征图数据，平铺的一维数组
    float *output:                  保存计算结果的一维数组
*/
void maxpool_compute(layer_params para, float* input, float* output)
{
    //code here
    int b,i,j,k,m,n;
    int w_offset = -para.pad/2;
    int h_offset = -para.pad/2;

    int w = (para.input_w + para.pad - para.kernel_size) / para.stride + 1;
    int h = (para.input_h + para.pad - para.kernel_size) / para.stride + 1;
    int c = para.input_c;

    for(b = 0; b < 1; ++b){
        for(k = 0; k < c; ++k){
            for(i = 0; i < h; ++i){
                for(j = 0; j < w; ++j){
                    int out_index = j + w*(i + h*(k + c*b));
                    float max = -FLT_MAX;
                    int max_i = -1;
                    for(n = 0; n < para.kernel_size; ++n){
                        for(m = 0; m < para.kernel_size; ++m){
                            int cur_h = h_offset + i*para.stride + n;
                            int cur_w = w_offset + j*para.stride + m;
                            int index = cur_w + para.input_w*(cur_h + para.input_h*(k + b*para.input_c));
                            int valid = (cur_h >= 0 && cur_h < para.input_h &&
                                         cur_w >= 0 && cur_w < para.input_w);
                            float val = (valid != 0) ? input[index] : -FLT_MAX;
                            max_i = (val > max) ? index : max_i;
                            max   = (val > max) ? val   : max;
                        }
                    }
                    output[out_index] = max;
                }
            }
        }
    }
    return;
}


// Task 4: 编写上采样函数(optional)
/*
输入：
    layer_params para:
        input_w, input_h, input_c   输入特征图的宽、高、通道数(w*h*c)
        kernel_size                 无意义
        kernel_n                    无意义
        stride                      上采样系数
        pad                         无意义
    float *input:                   输入特征图数据，平铺的一维数组
    float *output:                  保存计算结果的一维数组

    上采样的方式为：原本的一个像素被简单地复制为 stride*stride 个像素
*/
void upsample_compute(layer_params para, float* input, float* output)
{
    //code here
    int out_w = para.input_w * para.stride;
    int out_h = para.input_h * para.stride;
    int out_c = para.input_c;
    int outputs = out_w * out_h * out_c;
    
    int i,j,k;
    for(i=0;i<outputs;i++)
    {
        output[i] = 0;
    }
        for(k = 0; k < para.input_c; ++k)
        {
            for(j = 0; j < para.input_h*para.stride; ++j)
            {
                for(i = 0; i < para.input_w*para.stride; ++i)
                {
                    int in_index = k*para.input_w*para.input_h + (j/para.stride)*para.input_w + i/para.stride;
                    int out_index = k*para.input_w*para.input_h*para.stride*para.stride + j*para.input_w*para.stride + i;
                    output[out_index] = input[in_index];
                }
            }
        }

    return;
}



