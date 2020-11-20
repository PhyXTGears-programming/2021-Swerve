// Copyright 2020 Robby Sammelson

#pragma once

namespace swervedrive {

template <class T>
class vector2 {
    public:
        vector2 (T xVal, T yVal) : x(xVal), y(yVal) {}

        T getX () const { return x; }
        T getY () const { return y; }

        vector2<T> operator+ (const vector2<T> b) const {
            return vector2<T> {getX() + b.getX(), getY() + b.getY()};
        }

        T operator* (const vector2<T> b) const {
            return getX() * b.getX() + getY() * b.getY();
        }
        
        template<class O>
        auto operator* (const O b) const {
            return vector2 {getX() * b, + getY() * b};
        }
    
    private:
        T x, y;
};

}