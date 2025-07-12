#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class Entity {
public:
    /*SDL_Rect rect;
    SDL_Color color;

    Entity(int x, int y, int w, int h, SDL_Color c) {
        rect = { x, y, w, h };
        color = c;
    }

    virtual void update(float deltaTime) {}
    virtual void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }*/
    SDL_Rect rect;
    SDL_Texture* texture;
    Entity(int x, int y, int w, int h): texture(nullptr){
        rect = { x,y,w,h };
    }
    virtual void update(float deltaTime) {}
    virtual void render(SDL_Renderer* renderer) {
        if (texture) {
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
        }
    }
    void setTexture(SDL_Texture* tex) {
        texture = tex;
    }
    virtual ~Entity() {}
};

class EntityManager {
private:
    std::vector<Entity*> entities;

public:
    void AddEntity(Entity* entity) {
        entities.push_back(entity);
    }
    void updateAll(float deltaTime) {
        for (Entity* e : entities) {
            e->update(deltaTime);
        }
    }
    void renderAll(SDL_Renderer* renderer) {
        for (Entity* e : entities) {
            e->render(renderer);
        }
    }
    const std::vector<Entity*>& getEntities() const {
        return entities;
    }
};

class Player : public Entity {
public:
    float speed;

    //Player(int x, int y, int w, int h, SDL_Color c, float s)
    //    : Entity(x, y, w, h, c), speed(s) {
    //}
    Player(int x, int y, int w, int h, float s): Entity(x,y,w,h), speed(s) {}

    void update(float deltaTime) override {
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_W]) rect.y -= static_cast<int>(speed * deltaTime);
        if (keystates[SDL_SCANCODE_S]) rect.y += static_cast<int>(speed * deltaTime);
        if (keystates[SDL_SCANCODE_A]) rect.x -= static_cast<int>(speed * deltaTime);
        if (keystates[SDL_SCANCODE_D]) rect.x += static_cast<int>(speed * deltaTime);
    }
};

class Wall : public Entity {
public:
    //Wall(int x, int y, int w, int h, SDL_Color c)
    //    : Entity(x, y, w, h, c) {
    //}
    Wall(int x, int y, int w, int h):Entity(x,y,w,h){}
};
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {

    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
// Detección de colisión
/*bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}*/

int main(int argc, char* argv[]) {
    //SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "SDL_Init or IMG_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Etapa 5",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    float speed = 200.0f;
    //Player player(100, 100, 50, 50, { 0, 255, 0, 255 }, speed);
    //Wall wall1(400, 250, 100, 100, { 60, 150, 255, 255 });
    //Wall wall2(400, 400, 100, 100, { 120, 150, 255, 255 });
    Player player(100, 100, 64, 64, speed);
    Wall wall1(400, 250, 64, 64);
    Wall wall2(400, 400, 64, 64);

    SDL_Texture* playerTex = loadTexture("assets/player.png", renderer);
    SDL_Texture* wallTex = loadTexture("assets/wall.png", renderer);
    if (!playerTex || !wallTex) return 1;

    player.setTexture(playerTex);
    wall1.setTexture(wallTex);
    wall2.setTexture(wallTex);

    EntityManager manager;
    manager.AddEntity(&wall1);
    manager.AddEntity(&wall2);

    bool running = true;
    Uint32 lastTick = SDL_GetTicks();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        Uint32 currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        player.update(deltaTime);
        manager.updateAll(deltaTime);
        
        /*bool anyCollision = false;
        for (Entity* e : manager.getEntities()) {
            if (checkCollision(player.rect, e->rect)) {
                anyCollision = true;
            }
        }

        player.color = anyCollision ? SDL_Color{ 255, 0, 0, 255 } : SDL_Color{ 0, 255, 0, 255 };

        // Render
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);*/
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        //for (Entity* e : entities) {
          //  e->render(renderer);
        //}
        manager.renderAll(renderer);
        player.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(wallTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}