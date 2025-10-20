#include "../src/rfb.hpp"
rfb::sound sound;
void keydown(int key) {
    sound.play();
    std::cout << key << std::endl;
}

int main() {
    rfb::init();
    sound = {rfb::load_sound("fads.ogg")};
    rfb::drawgrids = true;
    rfb::window::title = "Test";
    rfb::connect::onkeypress = keydown;
    rfb::is3d = true;
    rfb::mouselocked = true;
    //std::cout << rfb::is3d << std::endl;
    
    rfb::mainloop();
}