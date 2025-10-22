#include "../src/rfb.hpp"
rfb::sound sounde;
/*
void rfb::onkeypress(int key) {
    sounde.play();
    std::cout << key << std::endl;
}
*/
int main() {
    rfb::init();
    sounde = rfb::load_sound("what.mp3");
    rfb::cube cube;
    rfb::sphere mmm;
    mmm.solid = true;
    mmm.wires = true;
    mmm.radius = 100;
    cube.wires = true;
    cube.solid = false;
    cube.add();
    mmm.add();
    rfb::cammode = rfb::cammodes::free;
    //rfb::colorpicker picker;
    //picker.add();
    rfb::drawgrids = true;
    rfb::window::title = "Test";
    //rfb::connect::onkeypress = keydown;
    rfb::is3d = true;
    rfb::mouselocked = true;
    //std::cout << rfb::is3d << std::endl;
    
    rfb::mainloop();
    sounde.unload();
}