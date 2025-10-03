#include "rfb.hpp"
#include "raylib.h"
#include <iostream>


namespace rfb
{
    namespace connect
    {
        std::function<void()> onupdate = _df;
    } // namespace connect
    
    ::Color colortocolor(rfb::colors::Color color) {
        return {color.r, color.g, color.b, color.a};
    }
    void rect::add() {
        _rectd.push_back(this);
    }
    void init() {
        if (!IsAudioDeviceReady()) {
            InitAudioDevice();
        }
    }
    Music music;
    /**
     * Changes the currently playing music to the one specified by the path.
     * Stops and unloads previous music, loads new music, and starts playing it.
     */
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
            
            EndDrawing();
        }
        CloseWindow();
        CloseAudioDevice();
        
    }
    
} // namespace rfb