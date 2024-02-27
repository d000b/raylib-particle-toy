
#include <algorithm>


raylib::Color HSVtoRGB(raylib::Vector3 hsv)
{
    const auto& h = 0.f > hsv.x ? 360.0 + hsv.x : hsv.x;
    const auto& s = hsv.y;
    const auto& v = hsv.z;

    const float fC = s * v;
    const float fX = fC * (1.0 - std::fabs(std::fmod(h / 60.0, 2.0) - 1.0));

    raylib::Vector3 color_;
    switch (static_cast<int>(h / 60))
    {
        case 0: color_ = raylib::Vector3{ fC, fX, 0 }; break;
        case 1: color_ = raylib::Vector3{ fX, fC, 0 }; break;
        case 2: color_ = raylib::Vector3{ 0, fC, fX }; break;
        case 3: color_ = raylib::Vector3{ 0, fX, fC }; break;
        case 4: color_ = raylib::Vector3{ fX, 0, fC }; break;
        case 5: color_ = raylib::Vector3{ fC, 0, fX }; break;
    }

    const float fM = v - fC;

    color_.x += fM;
    color_.y += fM;
    color_.z += fM;

    return raylib::Color{
        static_cast<decltype(raylib::Color::r)>(255 * color_.x),
        static_cast<decltype(raylib::Color::g)>(255 * color_.y),
        static_cast<decltype(raylib::Color::b)>(255 * color_.z),
        static_cast<decltype(raylib::Color::a)>(255.0)
    };
}

float color_value_curve(float v)
{
#undef min
    const auto speed = 0.0125f;

    return std::clamp((v - speed), 0.f, 1.f);
}
