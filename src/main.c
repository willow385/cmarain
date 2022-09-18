#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <unistd.h>
#include "mchar_t.h"

struct sdl_context {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
};

void render_pixel_sdl(int x, int y, void *context) {
  struct sdl_context *sdlc = context;
  SDL_Rect pixel = {
    .x = x * 4,
    .y = y * 4,
    .w = 4,
    .h = 4
  };
  SDL_RenderFillRect(sdlc->renderer, &pixel);
}

int main(int argc, char *argv[]) {
  mchar_t hello_world[] = {
    mc_hek, mc_yoter, mc_le, mc_llewu, mc_ayyuhm, mc_space,
    mc_rek, mc_ayyuhm, mc_bat, mc_ihk, mc_nek, mc_stop
  };

  SDL_Init(SDL_INIT_VIDEO);
  struct sdl_context sdlc;
  sdlc.window = SDL_CreateWindow(
    "Marain Text Viewer",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    512,
    512,
    0
  );
  sdlc.renderer = SDL_CreateRenderer(sdlc.window, 0, 0);
  if (sdlc.window == NULL || sdlc.renderer == NULL) {
    printf("\nError! Something went horribly wrong!\n");
    printf("Error: %s\n", SDL_GetError());
    return 1;
  }
  _Bool window_open = 1;
  SDL_Event event;

  SDL_SetRenderDrawColor(sdlc.renderer, 0, 0, 0, 0);
  SDL_RenderClear(sdlc.renderer);

  // render the string
  SDL_SetRenderDrawColor(sdlc.renderer, 255, 255, 255, 255);
  mc_render_str(
    (struct mstr_t){ .length = 12, .chars = hello_world },
    s_3x3,
    1, 1,
    &render_pixel_sdl, (void *)&sdlc
  );

  do {
    SDL_RenderPresent(sdlc.renderer);
    SDL_PollEvent(&event);
    usleep(16667);
    if (event.type == SDL_QUIT) window_open = 0;
  } while (window_open);

  SDL_DestroyRenderer(sdlc.renderer);
  SDL_DestroyWindow(sdlc.window);
  SDL_Quit();
  return 0;
}
