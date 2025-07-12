# SDLMinigame

Expand on previous stages by adding player movement, collision detection, and a basic `EntityManager`.

## 🎯 Goals

- Move a player using keyboard input.
- Detect and respond to collisions with static wall objects.
- Apply simple inheritance with `Player` and `Wall` classes.
- Organize entities using an `EntityManager`.

## 🎮 Controls

- `W` – Move up  
- `A` – Move left  
- `S` – Move down  
- `D` – Move right  

## ▶️ How to Build

Compile with SDL2:

```bash
g++ -o SDLMinigame main.cpp -lSDL2
./SDLMinigame
