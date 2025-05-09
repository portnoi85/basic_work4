#include "Dust.hpp"
#include <cmath>

/**
 * Создание объекта с заданием центра и скорости
 * @param radius значение радиуса
 * @param color значение цвета
 */
Dust::Dust(const Point& center, const Velocity& velocity) :
        center_{center}, velocity_{velocity}, color_{255,0,0} {
    // TODO: определиться с цветом частиц
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Dust::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Dust::getVelocity() const {
    return {velocity_};
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Dust::setCenter(const Point& center) {
    center_ = center;
}

/**
 * @return центр объекта
 */
Point Dust::getCenter() const {
    return {center_};
}


/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Dust::draw(Painter& painter) const {
    painter.draw(center_, 5, color_);
}
