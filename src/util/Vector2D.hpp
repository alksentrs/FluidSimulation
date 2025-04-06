// Vector2D.hpp
#ifndef UTIL_VECTOR2D_HPP
#define UTIL_VECTOR2D_HPP

#include <SFML/System/Vector2.hpp>

class Vector2D {
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);
    Vector2D(const sf::Vector2f& vec);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(float scalar);
    Vector2D& operator/=(float scalar);

    float getX();
    float getY();
    void setLocation(Vector2D location);
    void setLocation(float x, float y);

    float length() const;
    Vector2D normalized() const;
    void setMagnitude(float mag);

    Vector2D add(const Vector2D& other) const;
    Vector2D subtract(const Vector2D& other) const;

    void addSelf(const Vector2D& other);
    void subtractSelf(const Vector2D& other);

    Vector2D scale(float s) const;
    void scaleSelf(float s);

    Vector2D divide(float s) const;
    void divideSelf(float s);

    Vector2D rotate(float radians) const;
    void rotateSelf(float radians);

    float dotProduct(const Vector2D& other) const;
    Vector2D orthogonal() const;
    Vector2D orthonormal() const;
    float cos(const Vector2D& other) const;

    float distance(const Vector2D& other) const;
    float distance2(const Vector2D& other) const;

    Vector2D clone() const;
    sf::Vector2f toSFML() const;
    bool isNan() const;

    static Vector2D fromSFML(const sf::Vector2f& vec);
    static Vector2D addRotate(const Vector2D& b, const Vector2D& a, float rad);
    static Vector2D rotateAdd(const Vector2D& b, const Vector2D& a, float rad);
    static Vector2D subtractRotate(const Vector2D& b, const Vector2D& a, float rad);
    static Vector2D rotateSubtract(const Vector2D& b, const Vector2D& a, float rad);
    static Vector2D interpol(const Vector2D& begin, const Vector2D& end, float t);
    static Vector2D intersection(const Vector2D& begin, const Vector2D& end, const Vector2D& vector, const Vector2D& base);
    static Vector2D intersection2(const Vector2D& begin, const Vector2D& end, const Vector2D& vector, const Vector2D& base);
    static Vector2D mean(const Vector2D& a, const Vector2D& b);
    static Vector2D ramdon();
    static Vector2D zero();
};

#endif // UTIL_VECTOR2D_HPP
