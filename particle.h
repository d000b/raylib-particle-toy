
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
    pos.x = raylib::GetRandomValue(0, screenWidth-1);
    pos.y = raylib::GetRandomValue(0, screenHeight-1);
    vel.x = raylib::GetRandomValue(-100, 100) / 100.f;
    vel.y = raylib::GetRandomValue(-100, 100) / 100.f;
    // raylib::Color = (raylib::Color){GetRandomValue(0,255),GetRandomValue(0,255),GetRandomValue(0,255),255};
    color = raylib::Color{0,0,0,100};
}

Particle::Particle(raylib::Vector2 _pos, raylib::Vector2 _vel, raylib::Color color)
    : pos(_pos), vel(_vel), color(color)
{

}

float Particle::getDist(raylib::Vector2 otherPos) {
    const float dx = pos.x - otherPos.x;
    const float dy = pos.y - otherPos.y;
    return sqrt((dx*dx) + (dy*dy));
}

raylib::Vector2 Particle::getNormal(raylib::Vector2 otherPos) {
    float dist = getDist(otherPos);
    if (dist == 0.0f) dist = 1;
    const float dx = pos.x - otherPos.x;
    const float dy = pos.y - otherPos.y;
    raylib::Vector2 normal = raylib::Vector2{dx*(1/dist), dy*(1/dist)};
    return normal;
}


void Particle::attract(raylib::Vector2 posToAttract, float multiplier) {
    float dist = fmax(getDist(posToAttract),0.5);
    raylib::Vector2 normal = getNormal(posToAttract);

    vel.x -= normal.x/dist;
    vel.y -= normal.y/dist;
}

void Particle::doFriction(float amount) {
    vel.x *= amount;
    vel.y *= amount;
}

void Particle::move(int screenWidth, int screenHeight) {
    pos.x += vel.x;
    pos.y += vel.y;

    if (pos.x < 0)
        pos.x += screenWidth;
    else if (pos.x >= screenWidth)
        pos.x -= screenWidth;

    if (pos.y < 0)
        pos.y += screenHeight;
    else if (pos.y >= screenHeight)
        pos.y -= screenHeight;
}

void Particle::updatePosition(const raylib::Vector2 posToAttract, const float attraction, const float friction, const long width, const long height) {
    attract(posToAttract, attraction);
    doFriction(friction);
    move(width, height);
}


void Particle::drawPixel() {
    DrawPixelV(pos, color);
}
