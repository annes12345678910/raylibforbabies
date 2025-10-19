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
    extern bool drawgrids;
    // changes the music that constantly plays
    void changemusic(std::string path, float volume = 1.0f);
    // initialize stuff, required
    void init();
    void changecamera2dpos(float x, float y);
    void changecamera2dzoom(float zoom);
    void changecamera2drot(float rotation);
    void update(); // can be overridden by user
    void onkeypress(int key);
    extern bool is3d;
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
    struct vector2 {
        float x;
        float y;
    };
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
        extern std::string title;

        // The background color
        extern rfb::colors::Color fillcolor;

    } // namespace window
    // the most important function, run the game
    void mainloop(bool resizeable = false, bool fullscreen = false, bool borderless = false, bool minimized = false);


    // the key constants
    namespace keys
    {
        const int SPACE = 32;
        const int KEYUP = 265;
        const int KEYDOWN = 264;
        const int KEYRIGHT = 262;
        const int KEYLEFT = 263;
    } // namespace keys
    // Object base class
    class GameObject
    {
    private:
        /* data */
    public:
        float x = 0;
        float y = 0;
        rfb::colors::Color color = rfb::colors::WHITE;
        GameObject(float x=0, float y=0, rfb::colors::Color color=colors::WHITE);
        virtual ~GameObject();
        virtual void add();
        virtual void draw();
        bool camaffect = true;
        bool d3 = false;
    };
    // 3d object base class
    struct D3Object : GameObject
    {
        bool camaffect = false;
        float z = 0;
        bool d3 = true;
    };
    
    // A Rectangle
    struct rect : GameObject
    {
        int width= 100;
        int height= 100;
        void draw() override;
        rect(float x=0, float y=0, int w=100, int h=100, rfb::colors::Color c=rfb::colors::WHITE) : GameObject(x, y, c), width(w), height(h) {}
    };
    // A Sprite (Movable image)
    struct sprite : GameObject
    {
        std::string path;
        MyTexture tex;
        int rotation = 0;
        int scale = 1;
        void draw() override;
    };
    // a button you can click
    struct button : GameObject
    {
        rect bg = {0,0,200,100, rfb::colors::BLUE};
        std::string text = "Button";
        std::function<void()> onclick = rfb::connect::_df;
        void draw() override;
    };
    // some text
    struct text : GameObject
    {
        std::string txt = "Text";
        int size = 20;
        void draw() override;
    };
    // a line streching from p1 to p2
    struct line : GameObject
    {
        private: 
        using GameObject::x;
        using GameObject::y;

        public:
        vector2 p1 = {0,0};
        vector2 p2 = {0,100};
        float width = 4;
        void draw() override;
    };
    // a 2d circle
    struct circle : GameObject {
        float radius=100;
        void draw() override;
    };
    // a slider 
    struct slider : GameObject {
        rect bounds;
        // int GuiSlider(Rectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue)
        float minvalue = 0;
        float maxvalue = 100;
        float value = 50;
        std::string lefttext = std::to_string(minvalue);
        std::string righttext = std::to_string(maxvalue);
        void draw() override;
    };
    struct checkbox : GameObject {
        // int GuiCheckBox(Rectangle bounds, const char *text, bool *checked)
        rect bounds;
        std::string text = "Checkbox";
        bool checked = false;
        void draw() override;
    };
    // need to fix this freaking thing, cant ask chatgpt because im on a plane.
    struct colorpicker : GameObject {
        // int GuiColorPicker(Rectangle bounds, const char *text, Color *color)
        rect bounds;
        std::string text = "Color Picker";
        bool hsv = false;
        void draw() override;
    };
    // a 3d cube
    struct cube : D3Object
    {
        float width = 1;
        float height = 1;
        float depth = 1;
        void draw() override;
    };
    
    
    
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of rectangles.
    inline std::vector<rfb::rect*> _rectd;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of sprites.
    inline std::vector<rfb::sprite*> _sprited;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of buttons.
    inline std::vector<rfb::button*> _buttond;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of text.
    inline std::vector<rfb::text*> _textd;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of text.
    inline std::vector<rfb::line*> _lined;
    // INTERNAL, DO NOT INTERACT UNLESS YOU KNOW WHAT YOU ARE DOING!!! The drawing queue of text.
    inline std::vector<rfb::GameObject*> _objects;
} // namespace rfb
