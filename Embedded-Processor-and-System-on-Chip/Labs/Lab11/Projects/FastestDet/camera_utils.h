#ifndef __CAMERA_UTILS_H__
#define __CAMERA_UTILS_H__

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAM_DEV     "/dev/video0"
#define CAM_WIDTH   640
#define CAM_HEIGHT  480
#define NB_BUFFER   4

typedef struct
{
    unsigned char *tmpbuffer[NB_BUFFER];
    unsigned int tmpbytesused[NB_BUFFER];
}pic_data;

extern int cam_fd;
extern pic_data pic;

int v4l2_init(void);

int v4l2_close(void);

#ifdef __cplusplus
}
#endif

#endif
