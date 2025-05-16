#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball() = delete;
    Ball(double radius, Color color);
    Ball(double radius, double mass, Color color);
    Ball(double radius, double mass, Color color, Point center, Velocity velosity);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    void setCollidable(bool collidable);
    bool isCollidable() const;
private:
    Point center_{};
    Velocity velocity_{};
    double radius_{};
    double mass_{};
    Color color_{};
    bool collidable_{true};
};
