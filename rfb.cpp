#include "rfb.hpp"
#include "raylib.h"
#include <ostream>


namespace rfb
{
    ::Color colortocolor(rfb::colors::Color color) {
        return {color.r, color.g, color.b, color.a};
    }
    void rect::add() {
        _rectd.push_back(this);
    }
    void mainloop() {
        InitWindow(rfb::window::width, rfb::window::height, rfb::window::title.c_str());
        InitAudioDevice();
        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
            rfb::connect::onupdate();
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