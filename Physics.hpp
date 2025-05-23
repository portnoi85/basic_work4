#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, size_t ticks) const;
    void update(std::vector<Ball>& balls, std::vector<Dust_time>& dusts, size_t ticks) const;

  private:
    void collideBalls(std::vector<Ball>& balls) const;
    void collideBalls(std::vector<Ball>& balls, std::vector<Dust_time>& dusts) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void collideWithBox(std::vector<Ball>& balls, std::vector<Dust_time>& dusts) const;
    void clearDusts(std::vector<Dust_time>& dusts) const;
    void createDusts(std::vector<Dust_time>& dusts, Point center, int angle_min, int angle_max) const;
    void move(std::vector<Ball>& balls) const;
    void move(std::vector<Dust_time>& dusts) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;
    Point getCollisionPoint(const Ball& a, const Ball& b) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
    std::vector<Dust_time> dusts;
};
