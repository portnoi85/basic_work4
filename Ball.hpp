#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball() = delete;
    Ball(double radius, const Color& color);
    Ball(double radius, double mass, const Color& color);
    Ball(double radius, double mass, const Color& color, const Point& center, const Velocity& velosity);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    void setCollidable(bool collidable);
    bool isCollidable() const;
    void draw(Painter& painter) const;

private:
    Point center_{};
    Velocity velocity_{};
    double radius_{};
    double mass_{};
    Color color_{};
    bool collidable_{true};
};
