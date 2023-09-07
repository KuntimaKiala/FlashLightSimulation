#include "KernelLauncher.cuh"

__device__
float gpu_smoothstep(float edge0, float edge1, float x) {
    float t = fmaxf(0.0f, fminf(1.0f, (x - edge0) / (edge1 - edge0)));
    return t * t * (3.0f - 2.0f * t);
}

__global__
void Kernel(uchar* data, double x, double y, int width, int height){
    int c = blockIdx.x * blockDim.x + threadIdx.x;
    int r = blockIdx.y * blockDim.y + threadIdx.y;
    const int offset = r*width + c; 
    
    if ((c >= width) || (r >= height)) return ;
   
    const float distance = sqrt((c-x)*(c-x) + (r-y)*(r-y)) ;
    const float flashlightRadius = sqrt(x*x + y*y) ;
    //  smooth interpolation function (e.g., smoothstep) to calculate intensity
    float intensity = gpu_smoothstep(-1.0f, 1.0f, 1.0f - (distance / flashlightRadius));
    
    intensity = fminf(fmaxf(intensity, 0.0f), 1.0f);
    data[4*offset+1] = 255 ;
    data[4*offset+2] = 255;
    data[4*offset+3] = 255 ;
    data[4*offset+4] = 255*intensity ;
   

}



void KernelLauncher::Launcher(uchar *data_host, double &x, double& y){
    std::cout << "(x,y) :(" << x << "," << y <<")"<<std::endl;
    //sizeof(uchar) = 1
    //p_nbchannels*p_height*p_width*sizeof(uchar) = 4*w*h*1

    cudaMalloc((void**)&data_device, p_nbchannels*p_height*p_width*sizeof(uchar));
    
    dim3 grid(p_width, p_height) ;
    Kernel<<<grid, 1>>>(data_device, x, y, p_width, p_height) ;
    cudaMemcpy(data_host, data_device,p_nbchannels*p_height*p_width*sizeof(uchar), cudaMemcpyDeviceToHost ) ;
}
 
KernelLauncher::KernelLauncher(const int& width, const int& height) 
: p_width(width), p_height(height) {
    p_data = new uchar[p_nbchannels*p_height*p_width*sizeof(uchar)] ;

}


KernelLauncher::~KernelLauncher(){

    delete [] p_data ;
    cudaFree(data_device) ;

}

