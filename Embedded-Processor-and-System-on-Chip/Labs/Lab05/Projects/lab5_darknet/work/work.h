#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

// Layer Parameters Structure
typedef struct layer_params layer_params;
struct layer_params {
    int input_w, input_h, input_c;  // input feature map: w*h*c
    int kernel_size, kernel_n;      // kernel: size*size*c*n
    int stride;
    int pad; 
};


// Rectangle Box Structure
typedef struct rectangle_box rectangle_box;
struct rectangle_box {
    float x,y;      // The center point coordinates of the box is (x,y)
    float w,h;      // Width and Height of the box
};


// ADDITIONAL DEFINITIONS

// Layer Structure and Operations
// layer structure forward declaration
typedef struct layer Layer;

// layer operations structure
typedef struct {
    float (*at)(Layer* layer, int h, int w, int c);
    float (*kernel)(Layer* layer, int x, int y, int c, int n);
} LayerOps;

// layer structure
struct layer {
    layer_params* para;     // Layer parameters
    float* input;           // Input feature map
    float* weight;          // Convolution kernel weights
    LayerOps* ops;          // Layer operations
};


// Layer Initialization
static inline void layer_init(
    Layer* layer, layer_params* para,
    float* input, float* weight, LayerOps* ops
) {
    layer->para = para;
    layer->input = input;
    layer->weight = weight;
    layer->ops = ops;
}


// IOU Computation
float iou_compute(rectangle_box a, rectangle_box b);


// Convolutional Layer Operations
// at operation
static float convolutional_at(Layer* layer, int w, int h, int c) {
    // Boundaries of the convolutional layer
    int layer_left = layer->para->pad;
    int layer_right = layer->para->input_w + layer->para->pad - 1;
    int layer_top = layer->para->pad;
    int layer_bottom = layer->para->input_h + layer->para->pad - 1;

    // Return the value at the specified position
    if (
        w >= layer_left && w <= layer_right
        && h >= layer_top && h <= layer_bottom
    ) {
        return layer->input[
            c * layer->para->input_w * layer->para->input_h
            + (h - layer->para->pad) * layer->para->input_w
            + (w - layer->para->pad)
        ];
    }
    else {
        return 0.0f;
    }

}

// kernel operation
static float convolutional_kernel(Layer* layer, int x, int y, int c, int n) {
    int size = layer->para->kernel_size;
    return layer->weight[
        n * size * size * layer->para->input_c
        + c * size * size
        + y * size
        + x
    ];

}

// convolutional layer operations structure
static LayerOps convolutional_ops = {
    .at = convolutional_at,
    .kernel = convolutional_kernel
};

// convolutional computaion declaration
void convolutional_compute(
    layer_params para, float* input, float* weight, float* output
);


// Maxpool Layer Operations
// at operation
static float maxpool_at(Layer* layer, int w, int h, int c) {
    // Boundaries of the maxpool layer
    int layer_width = layer->para->input_w;
    int layer_height = layer->para->input_h;

    // Return the value at the specified position
    if (w >= 0 && w < layer_width && h >= 0 && h < layer_height) {
        return layer->input[
            c * layer_width * layer_height + h * layer_width + w
        ];
    }
    else {
        return -FLT_MAX;
    }

}

// maxpool layer operations structure
static LayerOps maxpool_ops = {
    .at = maxpool_at,
    .kernel = NULL
};

// maxpool computaion declaration
void maxpool_compute(layer_params para, float* input, float* output);


// Upsample Layer Operations
// at operation
static float upsample_at(Layer* layer, int w, int h, int c) {
    // Boundaries of the upsample layer
    int layer_width = layer->para->input_w;
    int layer_height = layer->para->input_h;

    // Return the value at the specified position
    if (w >= 0 && w < layer_width && h >= 0 && h < layer_height) {
        return layer->input[
            c * layer_width * layer_height + h * layer_width + w
        ];
    }
    else {
        return 0.0f;
    }

}

// upsample layer operations structure
static LayerOps upsample_ops = {
    .at = upsample_at,
    .kernel = NULL
};

// upsample computaion declaration
void upsample_compute(layer_params para, float* input, float* output);

