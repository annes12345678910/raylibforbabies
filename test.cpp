#include "rfb.hpp"
rfb::rect ract = {0,0,100,100,rfb::colors::RED};
void update() {
    //std::cout << "ract.x = " << ract.x << std::endl;
    ract.x += 1;
}
int main() {
    rfb::init();
    rfb::changemusic("example.mp3");
    ract.add();
    rfb::connect::onupdate = update;
    rfb::mainloop();
}