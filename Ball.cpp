#include "Ball.hpp"
#include <cmath>

/**
 * Создание объекта с заданием не изменяющихся полей и расчетом массы
 * @param radius значение радиуса
 * @param color значение цвета
 */
Ball::Ball(double radius, const Color& color) : 
        Ball(radius, radius * radius * radius, color) {}

/**
 * Создание объекта с заданием не изменяющихся полей
 * @param radius значение радиуса
 * @param mass значение массы
 * @param color значение цвета
 */
Ball::Ball(double radius, double mass, const Color& color) : 
        radius_{radius}, mass_{mass}, color_{color} {}

/**
 * Создание объекта с заданием дополнительных полей
 * @param radius значение радиуса
 * @param mass значение массы
 * @param color значение цвета
 * @param velosity значение скорости
 * @param center значение центра
 */
Ball::Ball(double radius, double mass, const Color& color, const Point& center, const Velocity& velosity) :
        center_{center}, velocity_{velosity}, radius_{radius}, mass_{mass}, color_{color} {}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return {velocity_};
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    center_ = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return {center_};
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return {radius_};
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return {mass_};
}

/**
 * Задает разрешение для обработки столкновений
 * @param collidable новое значение для разрешения обработки столкновений 
 */
void Ball::setCollidable(bool collidable) {
    collidable_ = collidable;
}

/**
 * @return разрешение для обработки столкновений
 */
bool Ball::isCollidable() {
    return {collidable_};
}
