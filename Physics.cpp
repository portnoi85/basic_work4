#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls);
    }
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust_time>& dusts, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        move(dusts);
        clearDusts(dusts);
        collideWithBox(balls, dusts);
        collideBalls(balls, dusts);
    }
}

Point Physics::getCollisionPoint(const Ball& a, const Ball& b) const {
    Point point;
    double ax = a.getCenter().x;
    double ay = a.getCenter().y;
    double ar = a.getRadius();
    double bx = b.getCenter().x;
    double by = b.getCenter().y;
    double br = b.getRadius();
    point.x = ax +(bx - ax) * (ar) / (ar + br);
    point.y = ay +(by - ay) * (ar) / (ar + br);
    return {point};
}

void Physics::collideBalls(std::vector<Ball>& balls) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (a->isCollidable() == false) {
            continue;
        }
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (b->isCollidable() == false) {
                continue;
            }
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
            }
        }
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust_time>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (a->isCollidable() == false) {
            continue;
        }
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (b->isCollidable() == false) {
                continue;
            }
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                Point p = getCollisionPoint(*a, *b);
                createDusts(dusts, p, 0, 360);
                processCollision(*a, *b, distanceBetweenCenters2);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if (ball.isCollidable() == false) {
            continue;
        }
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls, std::vector<Dust_time>& dusts) const {
    for (Ball& ball : balls) {
        if (ball.isCollidable() == false) {
            continue;
        }
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
            if (p.x < topLeft.x + r) {
                createDusts(dusts, {topLeft.x, p.y}, -90, 90);
            } else {
                createDusts(dusts, {bottomRight.x, p.y}, 90, 270);
            }
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
            if (p.y < topLeft.y + r) {
                createDusts(dusts, {p.x, topLeft.y}, 0, 180);
            } else {
                createDusts(dusts, {p.x, bottomRight.y}, 180, 360);
            }

        }
    }
}

void Physics::clearDusts(std::vector<Dust_time>& dusts) const {
    for (auto dust_time = dusts.begin(); dust_time != dusts.end();) {
        if (dust_time->time > 0) {
            dust_time->time -= timePerTick;
            ++dust_time;
        } else {
            dust_time = dusts.erase(dust_time);
        }
    }
}

void Physics::createDusts(std::vector<Dust_time>& dusts, Point center, int angle_min, int angle_max) const {
    double angle_r;
    int count = 5 + std::rand() % 10;
    double abs;
    double life_time;
    for (int i= 0; i < count; i++) {
        abs = 200 + std::rand() % 200;
        life_time = (700 + std::rand() % 600)/ 1000.;
        angle_r = (std::rand() % (angle_max - angle_min) + angle_min) / 57.3;
        Dust dust(center, Velocity{abs, angle_r});
        dusts.push_back({dust, life_time});
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::move(std::vector<Dust_time>& dusts) const {
    for (Dust_time& dust_time : dusts) {
        Point newPos =
            dust_time.dust.getCenter() + dust_time.dust.getVelocity().vector() * timePerTick;
        dust_time.dust.setCenter(newPos);
    }
}


void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
