#include "rfb.hpp"
rfb::sprite ada;
rfb::rect ract = {0,0,100,100,rfb::colors::RED};
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
    rfb::changecamerarot(10);
    txt.y = 10;
    txt.x = 10;
    txt.add();
    rfb::button but;
    but.add();
    ada.path = "sighting.png";
    ada.add();
    rfb::init();
    rfb::changemusic("example.mp3");
    ract.add();
    rfb::connect::onupdate = update;
    rfb::connect::onkeypress = frick;
    rfb::mainloop();
}