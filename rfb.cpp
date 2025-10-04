#include "rfb.hpp"
#include "raylib.h"
#include <iostream>


namespace rfb
{
    //std::vector<rfb::sprite*> _texvec;
    Texture2D cache;
    Texture2D c2;
    namespace connect
    {
        std::function<void()> onupdate = _df;
    } // namespace connect
    // internal converter
    ::Color colortocolor(rfb::colors::Color color) {
        return {color.r, color.g, color.b, color.a};
    }
    void rect::add() {
        _rectd.push_back(this);
    }

    void sprite::add() {
        _sprited.push_back(this);
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
            //cache = (Texture2D){sp->tex.id, sp->tex.width, sp->tex.height, sp->tex.mipmaps, sp->tex.format};
            sp->tex = (MyTexture){c2.id, c2.width, c2.height, c2.mipmaps, c2.format};
        }

        while (!WindowShouldClose())
        {
            rfb::connect::onupdate();
            k = GetKeyPressed();
            if (k != 0) {
                std::cout << k << std::endl;
            }
            if (IsMusicValid(music))
            {
                UpdateMusicStream(music);
            }
            
            BeginDrawing();
            ClearBackground(rfb::colortocolor(rfb::window::fillcolor));
            for (const auto& rect : rfb::_rectd)
            {
                DrawRectangle(rect->x, rect->y, rect->width, rect->height, rfb::colortocolor(rect->color));
            }
            for (const auto& sp : rfb::_sprited)
            {;
                cache = (Texture2D){sp->tex.id, sp->tex.width, sp->tex.height, sp->tex.mipmaps, sp->tex.format};
                DrawTexture(cache, 0,0, WHITE);
            }

            EndDrawing();
        }
        CloseWindow();
        CloseAudioDevice();
        
    }
    
} // namespace rfb