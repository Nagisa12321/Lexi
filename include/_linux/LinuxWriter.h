#ifndef LINUXFONT_H
#define LINUXFONT_H
#include "SDL_ttf.h"
#include "Types.h"

extern const SDL_Color default_text_color;
extern const SDL_Color default_text_background_color;

extern const int linux_min_font_size;
extern const int linux_mid_font_size;
extern const int linux_max_font_size;

class LinuxWriter {
public:
    LinuxWriter(const char *font_path, SDL_Renderer *render);
    ~LinuxWriter();

    void write(const Point &p, const char *text, const FontSize &fs);
private:
    TTF_Font        *m_font_min, *m_font_mid, *m_font_max;
    SDL_Renderer    *m_render;
};

#endif // LINUXFONT_H 
