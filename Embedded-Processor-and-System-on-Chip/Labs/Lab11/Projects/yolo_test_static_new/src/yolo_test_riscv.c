#include "darknet.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

extern void test_detector(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh, float hier_thresh, char *outfile, int fullscreen);


int main(int argc, char **argv)
{
    
        float thresh = 0.5;
        char *filename = "data/dog.jpg";
        char *outfile = 0;
        int fullscreen = 0;
        test_detector("cfg/coco.data", "cfg/yolov3-tiny.cfg", "cfg/yolov3-tiny.weights", filename, thresh, .5, outfile, fullscreen);

    return 0;
}

