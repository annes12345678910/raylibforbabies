#include "rfb.hpp"
void keydown(int key) {
    std::cout << key << std::endl;
}

int main() {
    rfb::init();
    rfb::drawgrids = true;
    rfb::window::title = "Test";
    rfb::connect::onkeypress = keydown;
    rfb::is3d = true;
    //std::cout << rfb::is3d << std::endl;
    
    rfb::mainloop();
}