#include <SDL.h>

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Erro ao inicializar o SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow("SNK Window", SDL_WINDOWPOS_CENTERED / 5, SDL_WINDOWPOS_CENTERED / 2, 640, 480, 0);

  if (window == NULL) {
    printf("SDL_CreateWindow Erro: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("SDL_CreateRenderer Erro: %s\n", SDL_GetError());
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  SDL_Delay(10000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
