#include "maxpool_layer.h"
#include <stdio.h>
//#include <dlfcn.h>
#include "work.h"

image get_maxpool_image(maxpool_layer l)
{
    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;
    return float_to_image(w,h,c,l.output);
}

image get_maxpool_delta(maxpool_layer l)
{
    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;
    return float_to_image(w,h,c,l.delta);
}

maxpool_layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride, int padding)
{
    maxpool_layer l = {0};
    l.type = MAXPOOL;
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = c;
    l.pad = padding;
    l.out_w = (w + padding - size)/stride + 1;
    l.out_h = (h + padding - size)/stride + 1;
    l.out_c = c;
    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = h*w*c;
    l.size = size;
    l.stride = stride;
    int output_size = l.out_h * l.out_w * l.out_c * batch;
    l.indexes = calloc(output_size, sizeof(int));
    l.output =  calloc(output_size, sizeof(float));
    l.delta =   calloc(output_size, sizeof(float));
    l.forward = forward_maxpool_layer;
    l.backward = backward_maxpool_layer;
    #ifdef GPU
    l.forward_gpu = forward_maxpool_layer_gpu;
    l.backward_gpu = backward_maxpool_layer_gpu;
    l.indexes_gpu = cuda_make_int_array(0, output_size);
    l.output_gpu  = cuda_make_array(l.output, output_size);
    l.delta_gpu   = cuda_make_array(l.delta, output_size);
    #endif
    fprintf(stderr, "max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}

void resize_maxpool_layer(maxpool_layer *l, int w, int h)
{
    l->h = h;
    l->w = w;
    l->inputs = h*w*l->c;

    l->out_w = (w + l->pad - l->size)/l->stride + 1;
    l->out_h = (h + l->pad - l->size)/l->stride + 1;
    l->outputs = l->out_w * l->out_h * l->c;
    int output_size = l->outputs * l->batch;

    l->indexes = realloc(l->indexes, output_size * sizeof(int));
    l->output = realloc(l->output, output_size * sizeof(float));
    l->delta = realloc(l->delta, output_size * sizeof(float));

    #ifdef GPU
    cuda_free((float *)l->indexes_gpu);
    cuda_free(l->output_gpu);
    cuda_free(l->delta_gpu);
    l->indexes_gpu = cuda_make_int_array(0, output_size);
    l->output_gpu  = cuda_make_array(l->output, output_size);
    l->delta_gpu   = cuda_make_array(l->delta,  output_size);
    #endif
}

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

void forward_maxpool_layer(const maxpool_layer l, network net)
{
    /*void *mdlhandle;
    void (*maxpool_compute)(layer_params,float*,float*);
    char *mdlerror;
    mdlhandle = dlopen("./libwork_riscv.so",RTLD_LAZY);
    if(!mdlhandle)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    maxpool_compute = dlsym(mdlhandle,"maxpool_compute");
    if((mdlerror = dlerror())!= NULL)
    {
        fprintf(stderr,"%s\n",mdlerror);
        exit(1);
    }*/

    struct layer_params conv_para;
    conv_para.input_w = l.w;
    conv_para.input_h = l.h;
    conv_para.input_c = l.c;
    conv_para.kernel_n = l.n;
    conv_para.kernel_size = l.size;
    conv_para.stride = l.stride;
    conv_para.pad = l.pad;
    maxpool_compute(conv_para,net.input,l.output);

    /*if(dlclose(mdlhandle) < 0)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }*/

    
}

void backward_maxpool_layer(const maxpool_layer l, network net)
{
    int i;
    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;
    for(i = 0; i < h*w*c*l.batch; ++i){
        int index = l.indexes[i];
        net.delta[index] += l.delta[i];
    }
}

