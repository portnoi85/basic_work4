#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Dust {
public:
    Dust() = default;
    Dust(const Point& center, const Velocity& velocity);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void setCenter(const Point& center);
    Point getCenter() const;
    void draw(Painter& painter) const;

private:
    Point center_{};
    Velocity velocity_{};
    Color color_{};
};

struct Dust_time {
    Dust dust;
    double time;
};
