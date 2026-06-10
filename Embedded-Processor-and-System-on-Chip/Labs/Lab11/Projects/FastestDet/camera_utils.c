#include "camera_utils.h"

int cam_fd;

pic_data pic;

int v4l2_init(void)
{
    int i;
    int ret = 0;
 
    // 1、Open camera device
    if((cam_fd = open(CAM_DEV,O_RDWR)) == -1)
    {
        perror("ERROR opening V4L interface.");
        return -1;
    }
 
    // 2、Judge if the device is a camera device 
    struct v4l2_capability cam_cap = {};
    if(ioctl(cam_fd,VIDIOC_QUERYCAP,&cam_cap) == -1)
    {
        perror("Error opening device %s: unable to query device.");
        return -1;
    }
    if((cam_cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0) 
    {
        perror("ERROR video capture not supported.");
        return -1;
    }
 
    // 3、Setting output parameter.
    struct v4l2_format v4l2_fmt = {};
    v4l2_fmt.type = V4L2_CAP_VIDEO_CAPTURE;
    v4l2_fmt.fmt.pix.width = CAM_WIDTH;
    v4l2_fmt.fmt.pix.height = CAM_HEIGHT;
    v4l2_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    if (ioctl (cam_fd, VIDIOC_S_FMT, &v4l2_fmt) == -1) 
    {   
        perror("ERROR camera VIDIOC_S_FMT Failed.");
        return -1;
    }
    // 4、Check whether the parameters are set successfully 
    if (ioctl (cam_fd, VIDIOC_G_FMT, &v4l2_fmt) == -1) 
    {
        perror("ERROR camera VIDIOC_G_FMT Failed.");
        return -1;
    }
    if (v4l2_fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV)
    {
        printf("Set VIDIOC_S_FMT sucessful\n");
    }
    // 5、Require buffer to store image data
    struct v4l2_requestbuffers v4l2_req = {};
    v4l2_req.count = NB_BUFFER;
    v4l2_req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    v4l2_req.memory = V4L2_MEMORY_MMAP;
    if (ioctl (cam_fd, VIDIOC_REQBUFS, &v4l2_req) == -1) 
    {
        perror("ERROR camera VIDIOC_REQBUFS Failed.");
        return -1;
    } 
    // 6、Start memory map
    struct v4l2_buffer v4l2_buf = {};
    v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    v4l2_buf.memory = V4L2_MEMORY_MMAP;
    for(i = 0; i < NB_BUFFER; i++) 
    {
        v4l2_buf.index = i;
        if(ioctl(cam_fd, VIDIOC_QUERYBUF, &v4l2_buf) < 0)
        {
            perror("Unable to query buffer.");
            return -1;
        }
 
        pic.tmpbuffer[i] = (unsigned char*)mmap(NULL, v4l2_buf.length, PROT_READ|PROT_WRITE, MAP_SHARED, cam_fd, v4l2_buf.m.offset);
        if(pic.tmpbuffer[i] == MAP_FAILED)
        {
             perror("Unable to map buffer.");
             return -1;
        }
        if(ioctl(cam_fd, VIDIOC_QBUF, &v4l2_buf) < 0)
        {
            perror("Unable to queue buffer.");
            return -1;
        }
    }
    //7、Open stream input 
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(cam_fd, VIDIOC_STREAMON, &type) < 0)
    {
        perror("Unable to start capture.");
        return -1;
    }
    printf("Stream ON\n");
    return 0;
}

int v4l2_close(void)
{
    // Remove mmap.
    int i;
    for(i=0; i<NB_BUFFER; i++)
        munmap(pic.tmpbuffer[i],pic.tmpbytesused[i]);
    close(cam_fd);
    return 0;
}
