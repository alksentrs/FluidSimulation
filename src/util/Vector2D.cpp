/*
 * Vector2D.cpp
 *
 *  Created on: 26 de mar. de 2025
 *      Author: aleksander
 */

// Vector2D.cpp
#include <SFML/System/Vector2.hpp>
#include "Vector2D.hpp"
#include <random>
#include <cmath>
#define _USE_MATH_DEFINES

Vector2D::Vector2D() : x(0), y(0) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}
Vector2D::Vector2D(const sf::Vector2f& vec) : x(vec.x), y(vec.y) {}

Vector2D Vector2D::operator+(const Vector2D& other) const { return Vector2D(x + other.x, y + other.y); }
Vector2D Vector2D::operator-(const Vector2D& other) const { return Vector2D(x - other.x, y - other.y); }
Vector2D Vector2D::operator*(float scalar) const { return Vector2D(x * scalar, y * scalar); }
Vector2D Vector2D::operator/(float scalar) const { return Vector2D(x / scalar, y / scalar); }

Vector2D& Vector2D::operator+=(const Vector2D& other) { x += other.x; y += other.y; return *this; }
Vector2D& Vector2D::operator-=(const Vector2D& other) { x -= other.x; y -= other.y; return *this; }
Vector2D& Vector2D::operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
Vector2D& Vector2D::operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }


float Vector2D::getX() {
	return x;
}

float Vector2D::getY() {
	return y;
}

float Vector2D::length() const { return std::sqrt(x * x + y * y); }
Vector2D Vector2D::normalized() const {
    float len = length();
    return (len > 0) ? (*this / len) : Vector2D(0, 0);
}

Vector2D Vector2D::add(const Vector2D& other) const {
	return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::subtract(const Vector2D& other) const {
	return Vector2D(this->x - other.x, this->y - other.y);
}

void Vector2D::addSelf(const Vector2D& other) {
	this->x = this->x + other.x;
	this->y = this->y + other.y;
}

void Vector2D::subtractSelf(const Vector2D& other) {
	this->x = this->x - other.x;
	this->y = this->y - other.y;
}

Vector2D Vector2D::scale(float s) const {
	return Vector2D(x * s, y  * s);
}

void Vector2D::scaleSelf(float s) {
	this->x = this->x * s;
	this->y = this->y * s;
}

Vector2D Vector2D::divide(float s) const {
	return Vector2D(x / s, y  / s);
}

void Vector2D::divideSelf(float s) {
	this->x = this->x / s;
	this->y = this->y / s;
}

Vector2D Vector2D::rotate(float radians) const {
    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);
    return Vector2D(x * cosTheta - y * sinTheta, x * sinTheta + y * cosTheta);
}

void Vector2D::rotateSelf(float radians) {
    float cosTheta = std::cos(radians);
    float sinTheta = std::sin(radians);
    float newX = x * cosTheta - y * sinTheta;
    float newY = x * sinTheta + y * cosTheta;
    x = newX; y = newY;
}

float Vector2D::dotProduct(const Vector2D& other) const { return x * other.x + y * other.y; }
Vector2D Vector2D::orthogonal() const { return Vector2D(-y, x); }
Vector2D Vector2D::orthonormal() const { return orthogonal().normalized(); }

float Vector2D::cos(const Vector2D& other) const {
    float lenProduct = length() * other.length();
    return (lenProduct != 0) ? dotProduct(other) / lenProduct : 0.f;
}

float Vector2D::distance(const Vector2D& other) const {
	float xx = x-other.x;
	float yy = y-other.y;
	return std::sqrt(xx * xx + yy * yy);
}

float Vector2D::distance2(const Vector2D& other) const {
	float xx = x-other.x;
	float yy = y-other.y;
	return xx * xx + yy * yy;
}

Vector2D Vector2D::clone() const { return Vector2D(x, y); }
sf::Vector2f Vector2D::toSFML() const { return sf::Vector2f(x, y); }
Vector2D Vector2D::fromSFML(const sf::Vector2f& vec) { return Vector2D(vec.x, vec.y); }

Vector2D Vector2D::addRotate(const Vector2D& b, const Vector2D& a, float rad) {
    Vector2D p = b.clone();
    p += a;
    p.rotateSelf(rad);
    return p;
}

Vector2D Vector2D::rotateAdd(const Vector2D& b, const Vector2D& a, float rad) {
    Vector2D p = b.clone();
    p.rotateSelf(rad);
    p += a;
    return p;
}

Vector2D Vector2D::subtractRotate(const Vector2D& b, const Vector2D& a, float rad) {
    Vector2D p = b.clone();
    p -= a;
    p.rotateSelf(rad);
    return p;
}

Vector2D Vector2D::rotateSubtract(const Vector2D& b, const Vector2D& a, float rad) {
    Vector2D p = b.clone();
    p.rotateSelf(rad);
    p -= a;
    return p;
}

Vector2D Vector2D::interpol(const Vector2D& begin, const Vector2D& end, float t) {
    return begin + (end - begin) * t;
}

Vector2D Vector2D::intersection(const Vector2D& begin, const Vector2D& end, const Vector2D& vector, const Vector2D& base) {
    float s = (vector.y * (base.x - begin.x) - vector.x * (base.y - begin.y)) /
              (vector.y * (end.x - begin.x) - vector.x * (end.y - begin.y));
    float t = ((end.x - begin.x) * s - (base.x - begin.x)) / vector.x;
    if ((s <= 1) && (s >= 0) && (t > 0)) {
        return base + vector * t;
    } else {
        return Vector2D(NAN, NAN);
    }
}

Vector2D Vector2D::intersection2(const Vector2D& begin, const Vector2D& end, const Vector2D& vector, const Vector2D& base) {
    float t = ((end.x - begin.x) * (base.y - begin.y) - (end.y - begin.y) * (base.x - begin.x)) /
              ((end.y - begin.y) * vector.x - (end.x - begin.x) * vector.y);
    if (t > 0) {
        return base + vector * t;
    } else {
        return Vector2D(NAN, NAN);
    }
}

Vector2D Vector2D::mean(const Vector2D& a, const Vector2D& b) {
    return Vector2D((a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f);
}

Vector2D Vector2D::ramdon() {
	Vector2D v(1.f, 0.f);
	std::mt19937 rng(std::random_device{}()); // @suppress("Type cannot be resolved")
	std::uniform_real_distribution<float> radians(0, 2.f * M_PI); // @suppress("Type cannot be resolved")
	v.rotateSelf( radians(rng));
	return v;
}

Vector2D Vector2D::zero() {
	return Vector2D(0.f, 0.f);
}

void Vector2D::setLocation(Vector2D location) {
	x = location.x;
	y = location.y;
}

void Vector2D::setLocation(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2D::setMagnitude(float mag) {
    float currentLength = length();
    if (currentLength > mag && currentLength > 0.f) {
        float scale = mag / currentLength;
        x = x*scale;
        y = y*scale;
    }
}

bool Vector2D::isNan() const {
    return (std::isnan(x) || std::isnan(y));
}


