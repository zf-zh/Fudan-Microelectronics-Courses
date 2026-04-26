
typedef struct layer_params layer_params;
struct layer_params
{
    int input_w, input_h, input_c;  //input feature map: w*h*c
    int kernel_size, kernel_n;      //kernel: size*size*c*n
    int stride;
    int pad; 
};

typedef struct rectangle_box rectangle_box;
struct rectangle_box
{
    float x,y;      //The center point coordinates of the box is (x,y)
    float w,h;      //Width and Height of the box
};