/*#include <SDL.h>
#include <iostream>
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Etapa 5",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    bool running = true;
    SDL_Event event;
    SDL_Rect player = { 100, 100, 50, 50 };
    SDL_Rect wall = { 400, 250, 100, 100 };
    SDL_Rect wall2 = { 400, 400, 100, 100 };
    float speed = 200.0f;
    Uint32 lastTick = SDL_GetTicks();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Uint32 currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_W]) player.y -= static_cast<int>(speed * deltaTime);
        if (keystates[SDL_SCANCODE_S]) player.y += static_cast<int>(speed * deltaTime);
        if (keystates[SDL_SCANCODE_A]) player.x -= static_cast<int>(speed * deltaTime);
        if (keystates[SDL_SCANCODE_D]) player.x += static_cast<int>(speed * deltaTime);
        bool collided = checkCollision(player, wall);
        bool collided2 = checkCollision(player, wall2);
        bool anyCollision = collided || collided2;
        if (anyCollision) {
            std::cout << "Collision detected" << std::endl;
        }
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // gris oscuro
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 60, 150, 255, 255);
        SDL_RenderFillRect(renderer, &wall);
        SDL_SetRenderDrawColor(renderer, 120, 150, 255, 255);
        SDL_RenderFillRect(renderer, &wall2);
        SDL_SetRenderDrawColor(renderer, 
            anyCollision ? 255:0, 
            anyCollision ? 0:255, 
            0, 
            255); // rojo
        SDL_RenderFillRect(renderer, &player);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}*/
