#include "work.h"

// IOU Computation
float iou_compute(rectangle_box a, rectangle_box b) {
    float width_inter = fmin(
        fmin(a.w, b.w),
        (a.w + b.w) / 2 - fabs(a.x - b.x)
    );
    float height_inter = fmin(
        fmin(a.h, b.h),
        (a.h + b.h) / 2 - fabs(a.y - b.y)
    );

    if (width_inter <= 0 || height_inter <= 0) {
        // No intersection
        return 0.0f;
    }

    float area_inter = width_inter * height_inter;
    float area_union_a = a.w * a.h - area_inter;
    float area_union_b = b.w * b.h - area_inter;

    float iou = area_inter / (area_union_a + area_union_b + area_inter);

    return iou;

}


// Convolutional Layer Computation
void convolutional_compute(
    layer_params para, float* input, float* weight, float* output
) {
    // Create and initialize the convolutional layer
    Layer layer;
    layer_init(&layer, &para, input, weight, &convolutional_ops);

    // Calculate the output feature map dimensions
    int output_w = (para.input_w + 2 * para.pad - para.kernel_size)
        / para.stride + 1;
    int output_h = (para.input_h + 2 * para.pad - para.kernel_size)
        / para.stride + 1;
    int output_c = para.kernel_n;

    // Perform convolutional computation
    float sum;
    for (int n = 0; n < output_c; n++) {
        for (int h = 0; h < output_h; h++) {
            for (int w = 0; w < output_w; w++) {
                sum = 0.0f;
                for (int c = 0; c < para.input_c; c++) {
                    for (int y = 0; y < para.kernel_size; y++) {
                        for (int x = 0; x < para.kernel_size; x++) {
                            sum += layer.ops->at(
                                &layer,
                                w * para.stride + x,
                                h * para.stride + y,
                                c
                            ) * layer.ops->kernel(&layer, x, y, c, n);
                        }
                    }
                }
                output[n * output_w * output_h + h * output_w + w] = sum;
            }
        }
    }

}


// Maxpool Layer Computation
void maxpool_compute(layer_params para, float* input, float* output) {
    // Create and initialize the maxpool layer
    Layer layer;
    layer_init(&layer, &para, input, NULL, &maxpool_ops);

    // Calculate the output feature map dimensions
    int output_w = (para.input_w + para.stride - 1) / para.stride;
    int output_h = (para.input_h + para.stride - 1) / para.stride;
    int output_c = para.input_c;

    // Perform maxpool computation
    float max_value;
    for (int c = 0; c < output_c; c++) {
        for (int h = 0; h < output_h; h++) {
            for (int w = 0; w < output_w; w++) {
                max_value = -FLT_MAX;
                for (int y = 0; y < para.kernel_size; y++) {
                    for (int x = 0; x < para.kernel_size; x++) {
                        float value = layer.ops->at(
                            &layer,
                            w * para.stride + x,
                            h * para.stride + y,
                            c
                        );
                        if (value > max_value) {
                            max_value = value;
                        }
                    }
                }
                output[c * output_w * output_h + h * output_w + w] = max_value;
            }
        }
    }

}


// Upsample Layer Computation
void upsample_compute(layer_params para, float* input, float* output) {
    // Create and initialize the upsample layer
    Layer layer;
    layer_init(&layer, &para, input, NULL, &upsample_ops);

    // Calculate the output feature map dimensions
    int output_w = para.input_w * para.stride;
    int output_h = para.input_h * para.stride;
    int output_c = para.input_c;

    // Perform upsample computation
    for (int c = 0; c < output_c; c++) {
        for (int h = 0; h < output_h; h++) {
            for (int w = 0; w < output_w; w++) {
                output[c * output_w * output_h + h * output_w + w] =
                    layer.ops->at(&layer, w / para.stride, h / para.stride, c);
            }
        }
    }

}

