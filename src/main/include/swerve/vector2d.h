// Copyright 2020 Robby Sammelson

#pragma once

namespace swervedrive {

template <class T>
class Vector2D {
    public:
        Vector2D (T xVal, T yVal) : x(xVal), y(yVal) {}

        T getX () const { return x; }
        T getY () const { return y; }

        Vector2D<T> operator+ (const Vector2D<T> b) const {
            return Vector2D<T> {getX() + b.getX(), getY() + b.getY()};
        }

        T operator* (const Vector2D<T> b) const {
            return getX() * b.getX() + getY() * b.getY();
        }
        
        template<class O>
        auto operator* (const O b) const {
            return Vector2D {getX() * b, + getY() * b};
        }
    
    private:
        T x, y;
};

}
