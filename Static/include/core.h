#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

typedef struct core_window {
    int w;
    int h;
    char *title;
    void *data;
} core_window_t;

typedef struct core_renderer {
    void *backend;
    void *framebuffer;
    bool render_locked;
    core_window_t window;
} core_renderer_t;

typedef struct core_engine {
    core_renderer_t renderer;
    bool is_running;
} core_engine_t;

void core_renderer_startup(core_renderer_t *ctx, char *title, int w, int h) {
    ctx->window.title = title;
    ctx->window.w = w;
    ctx->window.h = h;
    ctx->render_locked = false;

    ctx->window.data = SDL_CreateWindow(ctx->window.title, ctx->window.w, ctx->window.h, SDL_WINDOW_OPENGL);
    ctx->backend = SDL_CreateRenderer(ctx->window.data, NULL);
    ctx->framebuffer = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);
    SDL_SetRenderVSync(ctx->backend, true);
}

void core_renderer_shutdown(core_renderer_t *ctx) {
    ctx->window.title = NULL;

    SDL_DestroySurface((SDL_Surface *)ctx->framebuffer);
    SDL_DestroyRenderer((SDL_Renderer *)ctx->backend);
    SDL_DestroyWindow((SDL_Window *)ctx->window.data);
    ctx->framebuffer = NULL;
    ctx->backend = NULL;
    ctx->window.data = NULL;

    SDL_Quit();
}

void core_renderer_frame_begin(core_renderer_t *ctx) {
    ctx->render_locked = true;

    SDL_SetRenderDrawColor(ctx->backend, 0, 60, 100, 255);
    SDL_RenderClear(ctx->backend);
}

void core_renderer_frame_end(core_renderer_t *ctx) {
    ctx->render_locked = false;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ctx->backend, ctx->framebuffer);

    SDL_FRect dstRect = {0, 0, ctx->window.w, ctx->window.h};

    SDL_RenderTexture(ctx->backend, texture, NULL, &dstRect);
    SDL_RenderPresent(ctx->backend);
    SDL_DestroyTexture(texture);
}

void core_engine_startup(core_engine_t *ctx) {
    ctx->is_running = true;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
    core_renderer_startup(&ctx->renderer, "Window", 800, 800);
}

void core_engine_shutdown(core_engine_t *ctx) {
    core_renderer_shutdown(&ctx->renderer);
}

void core_engine_update(core_engine_t *ctx) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            ctx->is_running = false;
        }
    }
}
