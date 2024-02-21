
#include <vector>
#include <algorithm>
#include <iterator>

#include "particle.h"


int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    SetRandomSeed(1);

    const int particleCount = 100000;
    std::vector<Particle> particles;
    particles.reserve(particleCount);

    const auto particle_ = Particle(screenWidth, screenHeight);
    std::fill_n(std::back_inserter(particles), particleCount, particle_);

    InitWindow(screenWidth, screenHeight, "raylib test");

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        auto mousePos = Vector2{static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())};

        for (long int i = 0; i < particleCount; i++)
        {   
            particles[i].updatePosition(mousePos, 1, 0.99, screenWidth, screenHeight);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < particleCount; i++)
        {
            particles[i].drawPixel();
        }

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
