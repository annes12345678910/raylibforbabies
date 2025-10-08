#include <iostream>
struct Music;
struct MyTexture {
    unsigned int id;        // OpenGL texture id
    int width;              // Texture base width
    int height;             // Texture base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (PixelFormat type)
};
namespace rfb
{
    // changes the music that constantly plays
    void changemusic(std::string path, float volume = 1.0f);
    // initialize stuff, required
    void init();
    void changecamerapos(float x, float y);
    void changecamerazoom(float zoom);
    void changecamerarot(float rotation);
    // the music (INTERNAL)
    extern Music music;
    namespace connect
    {
        void _df() {

        }
        void _dfi(int) {

        }
        extern std::function<void()> onupdate;  // the update sequence
        extern std::function<void(int)> onkeypress;
    } // namespace connect
    // color stuff
    namespace colors
    {
        typedef struct Color {
            unsigned char r;        // Color red value
            unsigned char g;        // Color green value
            unsigned char b;        // Color blue value
            unsigned char a;        // Color alpha value
        } Color;
        const Color RED = {255,0,0,255};
        const Color WHITE = {255,255,255,255};
        const Color BLUE = {0,0,255,255};
        const Color GREEN = {0,255,0,255};
        const Color BLACK = {0,0,0,255};
    } // namespace colors

    // we need to customize that window
    namespace window
    {
        int width = 800;
        int height = 600;
        std::string title = "MROW!!!";

        // The background color
        rfb::colors::Color fillcolor = rfb::colors::WHITE;

    } // namespace window
    // the most important function, run the game
    void mainloop(bool resizeable = false, bool fullscreen = false, bool borderless = false, bool minimized = false);

    // A Rectangle
    struct rect
    {
        // x position
        int x;
        // y position
        int y;

        int width;
        int height;
        colors::Color color;
        // Add the rect to the drawing loop
        void add();
        bool camaffect;
    };
    // the key constants
    namespace keys
    {
        const int SPACE = 32;
    } // namespace keys
    // A Sprite (Movable image)
    struct sprite
    {
        std::string path;
        MyTexture tex;
        float x = 0;
        float y = 0;
        int rotation = 0;
        int scale = 1;
        rfb::colors::Color tint = rfb::colors::WHITE;
        // Add the sprite to the drawing loop
        void add();
        bool camaffect;
    };
    struct button
    {
        rect bg = {0,0,200,100, rfb::colors::BLUE};
        std::string text = "Button";
        std::function<void()> onclick = rfb::connect::_df;
        void add();
        bool camaffect;
    };
    struct text
    {
        std::string txt = "Text";
        int size = 20;
        int x = 0;
        int y = 0;
        rfb::colors::Color color = rfb::colors::BLACK;
        void add();
        bool camaffect;
    };
    
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of rectangles.
    inline std::vector<rfb::rect*> _rectd;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of sprites.
    inline std::vector<rfb::sprite*> _sprited;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of buttons.
    inline std::vector<rfb::button*> _buttond;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of text.
    inline std::vector<rfb::text*> _textd;
} // namespace rfb
