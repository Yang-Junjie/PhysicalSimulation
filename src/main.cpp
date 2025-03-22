#include "OEGraphics.hpp"
#include "OERender.hpp"
#include "OEShader.hpp"
OEWindow window(800, 800, "Physics Engine");

void mainWindow(){
    
}

int main() {
   
    if (!window.init()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return -1;
    }
   
    std::function<void()> runcode = mainWindow;
    window.mainWindow(runcode);
    window.run();
   
    return 0;
}

 

