#include "upsample_layer.h"
#include "blas.h"
#include "work.h"
//#include <dlfcn.h>
#include <stdio.h>

layer make_upsample_layer(int batch, int w, int h, int c, int stride)
{
    layer l = {0};
    l.type = UPSAMPLE;
    l.batch = batch;
    l.w = w;
    l.h = h;
    l.c = c;
    l.out_w = w*stride;
    l.out_h = h*stride;
    l.out_c = c;
    if(stride < 0){
        stride = -stride;
        l.reverse=1;
        l.out_w = w/stride;
        l.out_h = h/stride;
    }
    l.stride = stride;
    l.outputs = l.out_w*l.out_h*l.out_c;
    l.inputs = l.w*l.h*l.c;
    l.delta =  calloc(l.outputs*batch, sizeof(float));
    l.output = calloc(l.outputs*batch, sizeof(float));;

    l.forward = forward_upsample_layer;
    l.backward = backward_upsample_layer;
    if(l.reverse) fprintf(stderr, "downsample         %2dx  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", stride, w, h, c, l.out_w, l.out_h, l.out_c);
    else fprintf(stderr, "upsample           %2dx  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", stride, w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}

void resize_upsample_layer(layer *l, int w, int h)
{
    l->w = w;
    l->h = h;
    l->out_w = w*l->stride;
    l->out_h = h*l->stride;
    if(l->reverse){
        l->out_w = w/l->stride;
        l->out_h = h/l->stride;
    }
    l->outputs = l->out_w*l->out_h*l->out_c;
    l->inputs = l->h*l->w*l->c;
    l->delta =  realloc(l->delta, l->outputs*l->batch*sizeof(float));
    l->output = realloc(l->output, l->outputs*l->batch*sizeof(float));
    
}



void backward_upsample_layer(const layer l, network net)
{
    if(l.reverse){
        upsample_cpu(l.delta, l.out_w, l.out_h, l.c, l.batch, l.stride, 1, l.scale, net.delta);
    }else{
        upsample_cpu(net.delta, l.w, l.h, l.c, l.batch, l.stride, 0, l.scale, l.delta);
    }
}

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


void forward_upsample_layer(const layer l, network net)
{
    /*void *mdlhandle;
    void (*upsample_compute)(layer_params,float*,float*);
    char *mdlerror;
    mdlhandle = dlopen("./libwork_riscv.so",RTLD_LAZY);
    if(!mdlhandle)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    upsample_compute = dlsym(mdlhandle,"upsample_compute");
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
    upsample_compute(conv_para,net.input,l.output);

    /*if(dlclose(mdlhandle) < 0)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }*/
}