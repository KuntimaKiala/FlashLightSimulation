#pragma once 
#include <iostream>
#include <algorithm>
using uchar = unsigned char ;
struct Mouse
    {   Mouse(double x, double y) : x(0), y(0){}
        Mouse() : x(0.0f), y(0.0f){}
        double x, y;

    };

class KernelLauncher
{
    public :
    KernelLauncher()=delete;
    KernelLauncher(const int& width, const int& height );
    ~KernelLauncher();
    void kernelManager();
    void Launcher(uchar *data_host, double &x, double& y);
    uchar * data_device ;
    Mouse  mouse ;
    void createFlashlightTexture(uchar* flashlightTexture) ;
    
    private :
    const int p_width, p_height ;
    const int p_nbchannels{4};
    uchar* p_data;
};
