#ifndef __POST_PROCESS_H__
#define __POST_PROCESS_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

#define MAX_VALUE( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN_VALUE( x, y ) ( ((x) < (y)) ? (x) : (y) )

/*
 * @brief Predictions post processing
 * @param [in] input_img: input image with layout hwc
 * @param [in] output_img: output data
 */
void GenerateOutputPicture(struct image_data *input_img, struct image_data *output_img, const char* filename);

int chw2hwc(float* src, int C, int H, int W);

void argmax(float* value, int* idx, float* array, int h, int w);

/*
 * @brief Creates grids of coordinates specified by height and width
 * @param [out] gx, gy: x, y coordinates
 * @param [in] h,w: tensor height, width
 */
void meshgrid(int* gx, int* gy, int h, int w);

/*
 * @brief Sigmoid function
 * @param [in] x: float32 variable
 * @return Sigmoid(x)
 */
float sigmoid(float x);

/*
 * @brief Apply activation functions to pred[..., :]
 * @param [in] pred: [pointer] the return value of model(input_tensor)
 * @param [in] img_size: image size, 416 default 
 * @param [in] nG: number of grid
 * @param [in] anchors: two as a pair, [(), (), ()]
 * @param [in] nA: number of anchors (n_tuples)
 */
// void activatePred(float* pred, int img_size, int nG, float* anchors, int nA);

/*
 * @brief IoU of two bounding boxes
 * @param [in] box1: {x1, y1, w1, h1}
 * @param [in] box2: {x2, y2, w2, h2}
 * @param [in] xyxy: 1 for xyxy, 0 for xywh
 * @return IoU of two boxes
 */
float bbox_iou(float* box1, float* box2, int xyxy);

/*
 * @brief Non-Max-Suppression (NMS) algorithm
 * @param [in] pred: prediction with shape (1, len_pred, 6)
 * @param [in] conf_thres: confidence threshold
 * @param [in] nms_thres: nms threshold
 * @return output with shape (x, y, x, y, object_conf, class_conf, class)
 */
struct image_data* non_max_suppression(struct image_data* pred, float conf_thres, float nms_thres);

/*
 * @brief Quick sort by object confidence (decrease)
 * @param [in] s: tensor data
 * @param [in] l: left side starting point
 * @param [in] r: right side starting point
 */
void confQuickSort(float* s, int l, int r);

/*
 * @brief Draw box on RGB image
 * @param [in] data: RGB data
 * @param [in] w, h: RGB width and height
 * @param [in] x1, x2, y1, y2: box coordinate
 * @param [in] r, g, b: box color
 */
void drawbox(unsigned char* data, int w, int h, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);

/*
 * @brief Print a tensor with shape (C, H, W)
 * @param [in] data: tensor data
 * @param [in] C, H, W: channel, height, width
 */
void print_tensor(float* data, int C, int H, int W);

void save_rgb(const char *filename, int x, int y, int comp, const void *data, int quality);


#endif