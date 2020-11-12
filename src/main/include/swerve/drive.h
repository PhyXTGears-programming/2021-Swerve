// Copyright 2020 Robby Sammelson

#pragma once

#include <functional>

#include "vector2d.h"

namespace swervedrive {

template<class D, class S, class R>
class Drive {
    public:
        Drive () {};

        void set_motion (Vector2D<S> velocity, R angular_velocity) {
            calc_sample = [=](Vector2D<D> pos) {
                Vector2D<D> tangent {-1 * pos.getY(), pos.getX()};
                return velocity + (tangent * angular_velocity);
            };
        };

        Vector2D<S> sample_motion (Vector2D<D> wheel) { return calc_sample(wheel); };

    private:
        std::function<Vector2D<S>(Vector2D<D>)> calc_sample = [] (Vector2D<D> _) { return Vector2D<S> {S(), S()}; };
};

}
