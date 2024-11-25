#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL3/SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "core.h"

core_engine_t engine_ctx;
core_renderer_t *renderer = (core_renderer_t *)&engine_ctx.renderer;

void mainloop(void) {
    if (engine_ctx.is_running) {
        core_engine_update(&engine_ctx);

        core_renderer_frame_begin(renderer);
        if (renderer->render_locked) {

            int w = renderer->window.w;
            int h = renderer->window.h;
            SDL_Surface *framebuffer = (SDL_Surface *)renderer->framebuffer;

            uint32_t *pixels;
            if (framebuffer->pixels != NULL) {
                pixels = (uint32_t *)framebuffer->pixels;
            }

            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    uint8_t r = rand() % 256;
                    uint8_t g = rand() % 256;
                    uint8_t b = rand() % 256;
                    uint8_t a = 255;

                    pixels[y * w + x] = SDL_MapSurfaceRGBA(framebuffer, r, g, b, a);
                }
            }
        }
        core_renderer_frame_end(renderer);
    }
#ifdef __EMSCRIPTEN__
    if (!engine_ctx.is_running) {
        // Reload app
    }
#endif
}

int main(int argc, char **argv) {
    srand(time(NULL));
    core_engine_startup(&engine_ctx);
    printf("Hello, C!\n");

#ifdef __EMSCRIPTEN__
    printf("Hello, Emscripten!\n");
#endif

#ifdef NDEBUG
    printf("Running release build...\n");
#elif defined(DEBUG)
    printf("Running debug build...\n");
#endif

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while (engine_ctx.is_running) {
        mainloop();
    }
#endif

    core_engine_shutdown(&engine_ctx);
    return 0;
}
