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
    bool bocache;
    void changecamerapos(float x, float y) {
        cam.target = (Vector2){x,y};
    }
    void changecamerazoom(float zoom) {
        cam.zoom = zoom;
    }
    void changecamerarot(float rotation) {
        cam.rotation = rotation;
    }
    namespace connect
    {
        std::function<void()> onupdate = _df;
        std::function<void(int)> onkeypress = _dfi;
    } // namespace connect
    // internal converter
    ::Color colortocolor(rfb::colors::Color color) {
        return {color.r, color.g, color.b, color.a};
    }
    ::Rectangle recttorec(rfb::rect ew) {
        return (Rectangle){static_cast<float>(ew.x),static_cast<float>(ew.y),static_cast<float>(ew.width),static_cast<float>(ew.height)};
    }
    void rect::add() {
        _rectd.push_back(this);
    }

    void sprite::add() {
        _sprited.push_back(this);
    }
    void button::add() {
        _buttond.push_back(this);
    }
    void text::add() {
        _textd.push_back(this);
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
    void drawcamaffects() {
        for (const auto& rect : rfb::_rectd)
        {
            if (rect->camaffect)
            {
                DrawRectangle(rect->x, rect->y, rect->width, rect->height, rfb::colortocolor(rect->color));
            }
        }
        for (const auto& sp : rfb::_sprited)
        {
            cache = (Texture2D){sp->tex.id, sp->tex.width, sp->tex.height, sp->tex.mipmaps, sp->tex.format};
            DrawTextureEx(cache, (Vector2){sp->x, sp->y}, sp->rotation, sp->scale, rfb::colortocolor(sp->tint));
        }
        for (const auto& but : rfb::_buttond)
        {
            bocache = GuiButton(recttorec(but->bg), but->text.c_str());
            if (bocache)
            {
                but->onclick();
            }
        }
        for (const auto& txt : rfb::_textd)
        {
            if (txt->camaffect)
            {
                /* code */
            }
            
            DrawText(txt->txt.c_str(), txt->x, txt->y, txt->size, rfb::colortocolor(txt->color));
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
        
        for (const auto& sp : rfb::_sprited)
        {
            c2 = LoadTexture(sp->path.c_str());
            sp->tex = (MyTexture){c2.id, c2.width, c2.height, c2.mipmaps, c2.format};
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
            BeginMode2D(cam);

            drawcamaffects();

            EndMode2D();
            EndDrawing();
        }
        CloseWindow();
        CloseAudioDevice();
        
    }
    
} // namespace rfb
