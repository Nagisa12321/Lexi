#include "LinuxWriter.h"
#include "Utils.h"
#include "Logger.h"

const SDL_Color default_text_color            = { 0x00, 0x00, 0x00, 0xFF };
const SDL_Color default_text_background_color = { 0xFF, 0xFF, 0xFF, 0xFF };

const int linux_min_font_size = 15;
const int linux_mid_font_size = 25;
const int linux_max_font_size = 35;

static int get_font_size(const FontSize &fs) {
    if (fs == FontSize::max) return linux_max_font_size;
    else if (fs == FontSize::min) return linux_min_font_size;
    else if (fs == FontSize::mid) return linux_mid_font_size;
    else return -1; 
}


LinuxWriter::LinuxWriter(const char *font_path, SDL_Renderer *render) 
    : m_font_max(TTF_OpenFont(font_path, linux_max_font_size)),
      m_font_min(TTF_OpenFont(font_path, linux_min_font_size)),
      m_font_mid(TTF_OpenFont(font_path, linux_mid_font_size)),
      m_render(render)
{
    if (!(m_font_max && m_font_min && m_font_mid)) { lexi_abort("Unable to load font!\n"); }
}

LinuxWriter::~LinuxWriter() {
    TTF_CloseFont(m_font_max);
    TTF_CloseFont(m_font_mid);
    TTF_CloseFont(m_font_min);
}

void LinuxWriter::write(const Point &p, const char *text, const FontSize &fs) {
    SDL_Texture *texture = NULL;
    Logger *logger = Logger::get_logger();
    SDL_Rect textRect;
    TTF_Font *cur_font;

    if (fs == FontSize::max) cur_font = m_font_max;
    else if (fs == FontSize::min) cur_font = m_font_min;
    else cur_font = m_font_mid;
    SDL_Surface *textSurface = 
        TTF_RenderText_Shaded(cur_font, 
                              text, 
                              default_text_color, 
                              default_text_background_color);
    if (!textSurface) { lexi_abort("Unable to render text surface!\n"); }

    texture = SDL_CreateTextureFromSurface(m_render, textSurface);
    if (!texture) { lexi_abort("Unable to create texture from rendered text!\n"); } 

    // Get text dimensions
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    textRect.x = p.x;
    textRect.y = p.y;
    logger->debug("textRect: w=%d, h=%d\n", textRect.w, textRect.h);

    SDL_FreeSurface(textSurface);

    // Set renderer color red to draw the square
    SDL_SetRenderDrawColor(m_render, 0xFF, 0x00, 0x00, 0xFF);

    // Draw text
    SDL_RenderCopy(m_render, texture, NULL, &textRect);

    // Update screen
    SDL_RenderPresent(m_render);
}
