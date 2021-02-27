// Copyright 2020 Robby Sammelson
// Used with permission

#pragma once

#include <ostream>

namespace swervedrive {

template <class T>
class vector2 {
    public:
        vector2 () : x(T()), y(T()) {}
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

template <class T>
std::ostream& operator<< (std::ostream& os, const swervedrive::vector2<T>& vector) {
      os << "(" << vector.getX() << ", " << vector.getY() << ")";
      return os;
}
