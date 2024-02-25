
#include <cstdlib>
#include <cmath>

namespace raylib {
    #include "raylib\raylib.h"
}

#pragma once


class Particle
{
private:
    raylib::Vector2 pos;
    raylib::Vector2 vel;
    raylib::Color color;
private:
    void borderline_swap(const int screenWidth, const int screenHeight)
    {
        constexpr auto border = 10.f;
        constexpr auto mirror_force = 0.985f;

        if (pos.x < border)
        {
            pos.x = screenWidth - border;
            vel.x *= mirror_force;
        }
        else if (pos.x >= screenWidth - border)
        {
            pos.x = border;
            vel.x *= mirror_force;
        }

        if (pos.y < border)
        {
            pos.y = screenHeight - border;
            vel.y *= mirror_force;
        }
        else if (pos.y >= screenHeight - border)
        {
            pos.y = border;
            vel.y *= mirror_force;
        }
    }
private:
    float getDist(raylib::Vector2 pos);
    raylib::Vector2 getNormal(raylib::Vector2 otherPos);
public:
    explicit Particle(int screenWidth, int screenHeight);
    explicit Particle(raylib::Vector2 pos, raylib::Vector2 vel, raylib::Color color);
private:
    void attract(raylib::Vector2 posToAttract, float multiplier);
    void doFriction(float amount);
    void move(int screenWidth, int screenHeight);
public:
    void updatePosition(const raylib::Vector2 posToAttract, const float attraction, const float friction, const long width, const long height);
    void drawPixel();
};

Particle::Particle(int screenWidth, int screenHeight) {
    pos.x = raylib::GetRandomValue(0, screenWidth - 1);
    pos.y = raylib::GetRandomValue(0, screenHeight - 1);
    vel.x = raylib::GetRandomValue(-100, 100) / 100.f;
    vel.y = raylib::GetRandomValue(-100, 100) / 100.f;   
    color = raylib::Color{ 0, 0, 0, 255 };
}

Particle::Particle(raylib::Vector2 pos, raylib::Vector2 vel, raylib::Color color)
    : pos(pos), vel(vel), color(color)
{

}

float Particle::getDist(raylib::Vector2 otherPos) {
    const float dx = pos.x - otherPos.x;
    const float dy = pos.y - otherPos.y;
    return sqrt((dx * dx) + (dy * dy));
}

raylib::Vector2 Particle::getNormal(raylib::Vector2 otherPos) {
    float dist = getDist(otherPos);
    
    if (dist == 0.0f)
    {
        dist = 1;
    }

    const float dx = pos.x - otherPos.x;
    const float dy = pos.y - otherPos.y;

    return raylib::Vector2{ dx * (1 / dist), dy * (1 / dist) };
}


void Particle::attract(raylib::Vector2 posToAttract, float multiplier) {
    const float scalar_dist = std::fmax(getDist(posToAttract), 1.f);
    const raylib::Vector2 normal = getNormal(posToAttract);

    // for a more dramatic move, raylib::Vector2{ 1.f, 1.f };
    const auto dist = raylib::Vector2{ scalar_dist, scalar_dist };

    vel.x -= multiplier * normal.x / dist.x;
    vel.y -= multiplier * normal.y / dist.y;
}

void Particle::doFriction(float amount) {
    vel.x *= amount;
    vel.y *= amount;
}

void Particle::move(int screenWidth, int screenHeight) {
    pos.x += vel.x;
    pos.y += vel.y;

    borderline_swap(screenWidth, screenHeight);
}

void Particle::updatePosition(const raylib::Vector2 posToAttract, const float attraction, const float friction, const long width, const long height) {
    attract(posToAttract, attraction);
    doFriction(friction);
    move(width, height);
}

void Particle::drawPixel() {
    DrawPixelV(pos, color);
}
