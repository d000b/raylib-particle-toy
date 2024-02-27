#pragma once

#include "defines.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <execution>

#include "particle.h"


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    raylib::SetRandomSeed(1);

    const int particleCount = 100'000;
    std::vector<Particle> particles;
    particles.reserve(particleCount);

    std::generate_n(std::back_inserter(particles), particleCount, [=]() -> auto { return Particle{ screenWidth, screenHeight }; });

    raylib::InitWindow(screenWidth, screenHeight, "raylib test");

    raylib::SetTargetFPS(60);

    constexpr raylib::Color white_background = (raylib::RAYWHITE);

    while (!raylib::WindowShouldClose())
    {
        const auto mousePos = raylib::Vector2{static_cast<float>(raylib::GetMouseX()), static_cast<float>(raylib::GetMouseY())};

        const auto force = static_cast<float>(raylib::IsMouseButtonDown(raylib::MOUSE_BUTTON_LEFT))
                         - static_cast<float>(raylib::IsMouseButtonDown(raylib::MOUSE_BUTTON_RIGHT));

        std::for_each(std::execution::par_unseq, std::begin(particles), std::end(particles), [&](Particle& particle) {
            particle.updatePosition(mousePos, force, 0.99, screenWidth, screenHeight);
        });

        raylib::BeginDrawing();

        raylib::ClearBackground(white_background);

        std::for_each(std::execution::seq, std::begin(particles), std::end(particles), [&](Particle& particle) {
            particle.drawPixel();
        });

        raylib::DrawFPS(10, 10);

        raylib::EndDrawing();
    }

    raylib::CloseWindow();

    return 0;
}
