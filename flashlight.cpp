#include <iostream>
#include  "WindowManager.hpp"


int main()
{
    WindowManager *window = new WindowManager(600,600, "FlashLight Simulation") ;
    std::cout << "Welcome to the Fashlight Simulation\n" ;
    window->GLFWindowGeneration(); // generate the window
    window->simulation() ;

    delete window ;
    window = nullptr ;
    return 0;
}
