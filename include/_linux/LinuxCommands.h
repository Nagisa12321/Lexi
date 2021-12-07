#ifndef LINUXCOMMANDS_H
#define LINUXCOMMANDS_H
#include "Commands.h"
#include "LinuxOriginal.h"
#include "LinuxWriter.h"
#include "SDL.h"
#include "Types.h"
#include "SDL_render.h"
#include "Logger.h"
#include <cstdio>
#include <string>
class CleanScreen : public Command {
public:
    CleanScreen(SDL_Renderer *renderer)
        : Command("clean screen"),
          m_renderer(renderer)
    {

    }
    void exec() override {
        Command::exec();
        Logger::get_logger()->debug("m_renderer: %p\n",  m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderFillRect(m_renderer, NULL);
        SDL_RenderPresent(m_renderer);
    }
    ~CleanScreen() = default;
private:
    SDL_Renderer *m_renderer;
};

class DrawRect : public Command {
public:
    DrawRect(SDL_Renderer *renderer, const WindowRect &rect, const Color &c)
        : Command("draw rect: " + to_string(rect)),
          m_renderer(renderer),
          m_rect(rect),
          m_c(dynamic_cast<const LinuxColor &>(c))
    {

    }
    void exec() override {
        Command::exec();
        SDL_SetRenderDrawColor(m_renderer, m_c.R(), m_c.G(), m_c.B(), m_c.D());
        SDL_Rect r{m_rect.x, m_rect.y, m_rect.width, m_rect.height};
        SDL_RenderDrawRect(m_renderer, &r);
        SDL_RenderPresent(m_renderer);
    }
    ~DrawRect() = default;
private:
    SDL_Renderer        *m_renderer;
    WindowRect          m_rect;
    LinuxColor          m_c;
};

class FillRect : public Command {
public:
    FillRect(SDL_Renderer *renderer, const WindowRect &rect, const Color &c)
        : Command("fill rect: " + to_string(rect)),
          m_renderer(renderer),
          m_rect(rect),
        m_c(dynamic_cast<const LinuxColor &>(c))
    {

    }
    void exec() override {
        Command::exec();
        SDL_SetRenderDrawColor(m_renderer, m_c.R(), m_c.G(), m_c.B(), m_c.D());
        SDL_Rect r{m_rect.x, m_rect.y, m_rect.width, m_rect.height};
        SDL_RenderFillRect(m_renderer, &r);
        SDL_RenderPresent(m_renderer);
    }
    ~FillRect() = default;
private:
    SDL_Renderer        *m_renderer;
    WindowRect          m_rect;
    LinuxColor          m_c;
};

class DrawLine : public Command {
public:
    DrawLine(SDL_Renderer *renderer, const Point &p1, const Point &p2, const Color &c) 
        : Command("draw line: " + to_string(p1) + ", " + to_string(p2)),
          m_renderer(renderer), 
          m_p1(p1),
          m_p2(p2),
          m_c(dynamic_cast<const LinuxColor &>(c))
    {

    }
    void exec() override {
        Command::exec();
        SDL_SetRenderDrawColor(m_renderer, m_c.R(), m_c.G(), m_c.B(), m_c.D());
        SDL_RenderDrawLine(m_renderer, m_p1.x, m_p1.y, m_p2.x, m_p2.y);
        SDL_RenderPresent(m_renderer);
    }

    ~DrawLine() = default;
private:
    SDL_Renderer *m_renderer;
    Point m_p1;
    Point m_p2;
    LinuxColor m_c;
};

class DrawText : public Command {
public:
    DrawText(LinuxWriter *text_writer, const Point &p, const std::string &text, const FontSize &fs)
        : Command("draw text: " + text),
          m_text_writer(text_writer),
          m_p(p),
          m_text(text),
          m_fs(fs)
    {

    }
    void exec() override {
        Command::exec();
        m_text_writer->write(m_p, m_text.c_str(), m_fs);
    }
private:
    LinuxWriter *m_text_writer;
    Point m_p;
    std::string m_text;
    FontSize m_fs;
};


#endif // LINUXCOMMANDS_H
