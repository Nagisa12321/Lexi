#ifndef LINUXCOMMANDS_H
#define LINUXCOMMANDS_H
#include "Commands.h"
#include "LinuxOriginal.h"
#include "LinuxWriter.h"
#include "SDL.h"
#include "Types.h"
#include "SDL_render.h"
#include "Logger.h"
#include "Window.h"
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

class DrawCycle : public Command {
public:
    DrawCycle(SDL_Renderer *renderer, const Point &p, int radius, const Color &c)
        : Command("draw cycle: " + to_string(p) + ", " + std::to_string(radius)),
          m_renderer(renderer),
          m_p(p),
          m_radius(radius),
          m_c(dynamic_cast<const LinuxColor &>(c))
    {

    }
    void exec() override {
        Command::exec();
        SDL_SetRenderDrawColor(m_renderer, m_c.R(), m_c.G(), m_c.B(), m_c.D());
        int m_pos_x = m_p.x;
        int m_pos_y = m_p.y;
        // draw cycle
        for (int x = 0; x <= m_radius; ++x) {
            int _y = sqrt(pow(m_radius, 2) - pow((double) x, 2));
            SDL_RenderDrawPoint(m_renderer, m_pos_x + x, m_pos_y + _y);
            SDL_RenderDrawPoint(m_renderer, m_pos_x -x,  m_pos_y + _y);
            SDL_RenderDrawPoint(m_renderer, m_pos_x + x, m_pos_y - _y);
            SDL_RenderDrawPoint(m_renderer, m_pos_x - x, m_pos_y - _y);
        }
        for (int _y = 0; _y <= m_radius; ++_y) {
            int x = sqrt(pow(m_radius, 2) - pow((double) _y, 2));
            SDL_RenderDrawPoint(m_renderer, m_pos_x + x, m_pos_y + _y);
            SDL_RenderDrawPoint(m_renderer, m_pos_x -x,  m_pos_y + _y);
            SDL_RenderDrawPoint(m_renderer, m_pos_x + x, m_pos_y - _y);
            SDL_RenderDrawPoint(m_renderer, m_pos_x - x, m_pos_y - _y);
        }
        SDL_RenderPresent(m_renderer);
    }
private:
    SDL_Renderer *m_renderer;
    Point m_p;
    int m_radius;
    LinuxColor m_c;
};

class FillCycle : public Command {
public:
    FillCycle(SDL_Renderer *renderer, const Point &p, int radius, const Color &c)
        : Command("draw cycle: " + to_string(p) + ", " + std::to_string(radius)),
          m_renderer(renderer),
          m_p(p),
          m_radius(radius),
          m_c(dynamic_cast<const LinuxColor &>(c))
    {

    }
    void exec() override {
        Command::exec();
        SDL_SetRenderDrawColor(m_renderer, m_c.R(), m_c.G(), m_c.B(), m_c.D());
        int m_pos_x = m_p.x;
        int m_pos_y = m_p.y;
        // fill cycle
        for (int x = 0; x <= m_radius; ++x) {
            int _y = sqrt(pow(m_radius, 2) - pow((double) x, 2));
            SDL_RenderDrawLine(m_renderer,  m_pos_x + x,  m_pos_y + _y,  m_pos_x + x, m_pos_y - _y);
            SDL_RenderDrawLine(m_renderer,  m_pos_x - x,  m_pos_y + _y,  m_pos_x - x, m_pos_y - _y);
        }
        SDL_RenderPresent(m_renderer);
    }
private:
    SDL_Renderer *m_renderer;
    Point m_p;
    int m_radius;
    LinuxColor m_c;
};

class ProcessEvent : public Command {
public:
    /* TODO: out put the event name */
    ProcessEvent(Window *window, Event *event) 
        : Command("process event"),
          m_window(window),
          m_event(event) 
    {

    }

    void exec() override {
        Command::exec();
        m_window->process_event(*m_event);
    }

    ~ProcessEvent() { delete m_event; }
private:
    Window *m_window;
    Event *m_event;
};



#endif // LINUXCOMMANDS_H
