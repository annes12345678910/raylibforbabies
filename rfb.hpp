#include <iostream>
namespace rfb
{
    namespace connect
    {
        void _df() {
        }
        extern std::function<void()> onupdate; // prevent OOF (specificaly std::__1::bad_function_call: std::exception)
    } // namespace connect
    
    namespace colors
    {
        typedef struct Color {
            unsigned char r;        // Color red value
            unsigned char g;        // Color green value
            unsigned char b;        // Color blue value
            unsigned char a;        // Color alpha value
        } Color;
        Color RED = {255,0,0,255};
        Color WHITE = {255,255,255,255};
        Color BLUE = {0,0,255,255};
        Color GREEN = {0,255,0,255};
        Color BLACK = {0,0,0,255};
    } // namespace colors
    namespace window
    {
        int width = 800;
        int height = 600;
        std::string title = "MROW!!!";
        rfb::colors::Color fillcolor = rfb::colors::WHITE;
    } // namespace window
    void mainloop();
    struct rect
    {
        int x;
        int y;
        int width;
        int height;
        colors::Color color;
        void add();
    };
    inline std::vector<rfb::rect*> _rectd;
} // namespace rfb