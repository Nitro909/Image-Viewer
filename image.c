#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1000];

    // Skip magic number + comment
    fgets(buffer, 1000, stdin);
    fgets(buffer, 1000, stdin);

    int width, height;
    fgets(buffer, 1000, stdin);
    sscanf(buffer, "%d %d", &width, &height);

    // Skip max value
    fgets(buffer, 1000, stdin);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "PPM Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        0
    );

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint8 r = (Uint8)getchar();
            Uint8 g = (Uint8)getchar();
            Uint8 b = (Uint8)getchar();

            SDL_Rect pixel = {x, y, 1, 1};
            Uint32 color = SDL_MapRGB(surface->format, r, g, b);
            SDL_FillRect(surface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(window);

    int running = 1;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }
        }
    }
    SDL_Delay(100);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
