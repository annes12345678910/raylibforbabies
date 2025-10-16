#define RAYGUI_IMPLEMENTATION
#include "rfb.hpp"
#include "raylib.h"
#include "raygui.h"
#include <iostream>


namespace rfb
{
    Texture2D cache;
    Texture2D c2;
    Camera2D cam = {(Vector2){0,0}, (Vector2){0,0},0,1};
    Camera3D cam3d = {(Vector3){0,0,0}, (Vector3){0,0,0}, (Vector3){0,0,0}, 60, CAMERA_FREE};
    bool bocache;
    void changecamera2dpos(float x, float y) {
        cam.target = (Vector2){x,y};
    }
    void changecamera2dzoom(float zoom) {
        cam.zoom = zoom;
    }
    void changecamera2drot(float rotation) {
        cam.rotation = rotation;
    }
    namespace connect
    {
        std::function<void()> onupdate = _df;
        std::function<void(int)> onkeypress = _dfi;
    } // namespace connect

    
    // internal converters
    ::Color colortocolor(rfb::colors::Color color) {
        return {color.r, color.g, color.b, color.a};
    }
    ::Rectangle recttorec(rfb::rect ew) {
        return (Rectangle){static_cast<float>(ew.x),static_cast<float>(ew.y),static_cast<float>(ew.width),static_cast<float>(ew.height)};
    }
    ::Vector2 vector2tovec(vector2 thing) {
        return {thing.x, thing.y};
    }


    void GameObject::add() {
        _objects.push_back(this);
    }
    void GameObject::draw() {}

    GameObject::GameObject(float x, float y, rfb::colors::Color color)
    {
        this->x = x;
        this->y = y;
        this->color = color;
    }
    
    GameObject::~GameObject()
    {
    }

    // some draw overrides i guess

    void rect::draw() {
        DrawRectangle(x, y, width, height, colortocolor(color));
    }
    void sprite::draw() {
        //std::cout << "Drawing sprite at (" << x << ", " << y << ")\n";
        cache = (Texture2D){tex.id, tex.width, tex.height, tex.mipmaps, tex.format};
        DrawTextureEx(cache, (Vector2){x, y}, rotation, scale, rfb::colortocolor(color));
    }
    void button::draw() {
        bocache = GuiButton(recttorec(bg), text.c_str());
        if (bocache)
        {
            onclick();
        }
    }
    void text::draw() {
        DrawText(txt.c_str(), x, y, size, colortocolor(color));
    }
    void line::draw() {
        DrawLineEx(vector2tovec(p1), vector2tovec(p2), width, colortocolor(color));
    }
    void cube::draw() {
        DrawCube((Vector3){x, y, z}, width, height, depth, colortocolor(color));
    }



    void init() {
        if (!IsAudioDeviceReady()) {
            InitAudioDevice();
        }
    }
    Music music;
    void changemusic(std::string path, float volume) {
        if (IsMusicValid(music)) {
            StopMusicStream(music);
            UnloadMusicStream(music);
        }
        music = LoadMusicStream(path.c_str());
        SetMusicVolume(rfb::music, volume);
        if (IsMusicValid(music)) {
            PlayMusicStream(music);
        }
        else
        {
            std::cout << "Could not load music: " << path << std::endl;
        }
    }
    // poop
    void drawobjs(bool iscam, bool d3) {
        // skobido bum bum
        for (const auto& obj : rfb::_objects)
        {
            if (obj->camaffect == iscam and obj->d3 == d3)
            {
                obj->draw();
            }
        }
    }


    int k;
    void mainloop(bool resizeable, bool fullscreen, bool borderless, bool minimized) {
        if (resizeable)
        {
            SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        }
        if (fullscreen)
        {
            SetConfigFlags(FLAG_FULLSCREEN_MODE);
        }
        if (borderless)
        {
            SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
        }
        
        if (minimized)
        {
            SetConfigFlags(FLAG_WINDOW_MINIMIZED);
        }
        InitWindow(rfb::window::width, rfb::window::height, rfb::window::title.c_str());
        SetTargetFPS(60);
        if (IsMusicValid(music))
        {
            PlayMusicStream(music);
        }
        
        for (const auto& obj : rfb::_objects)
        {
            if (auto sp = dynamic_cast<rfb::sprite*>(obj)) {
                c2 = LoadTexture(sp->path.c_str());
                sp->tex = (MyTexture){c2.id, c2.width, c2.height, c2.mipmaps, c2.format};
            }
        }

        while (!WindowShouldClose())
        {
            rfb::connect::onupdate();
            k = GetKeyPressed();
            if (k != 0) {
                //std::cout << k << std::endl;
                rfb::connect::onkeypress(k);
            }
            // the music
            if (IsMusicValid(music))
            {
                UpdateMusicStream(music);
            }
            
            
            BeginDrawing();
            ClearBackground(rfb::colortocolor(rfb::window::fillcolor));
            BeginMode3D(cam3d);
            if (rfb::drawgrids == true)
            {
                DrawGrid(100,1);
            }
            drawobjs(false, true);
            
            EndMode3D();
            BeginMode2D(cam);

            drawobjs(true, false);

            EndMode2D();

            drawobjs(false, false);

            EndDrawing();
        }
        CloseWindow();
        CloseAudioDevice();
        
    }
    
} // namespace rfb
