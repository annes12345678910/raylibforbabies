#include "rfb.hpp"
rfb::sprite ada;
rfb::rect ract;
rfb::text txt;
void update() {
    //std::cout << "ract.x = " << ract.x << std::endl;
    ract.x += 1;
    ada.x += -1;
}
void frick(int key) {
    txt.txt = std::to_string(key);
    std::cout << key << std::endl;
}
int main() {
    rfb::init();
    rfb::changecamera2drot(10);
    txt.y = 10;
    txt.x = 10;
    ada.path = "sighting.png";
    ada.add();
    rfb::button but;
    but.add();
    
    rfb::changemusic("example.mp3");
    ract.add();
    txt.add();
    rfb::line la;
    la.p1 = {100,10};
    la.add();
    rfb::connect::onupdate = update;
    rfb::connect::onkeypress = frick;
    rfb::mainloop();
}