// Copyright 2020 Robby Sammelson

#pragma once

#include <functional>

#include "vector2.h"

namespace swervedrive {

template<class D, class S, class R>
class Drive {
    public:
        Drive () {};

        void set_motion (vector2<S> velocity, R angular_velocity) {
            calc_sample = [=](vector2<D> pos) {
                vector2<D> tangent {-1 * pos.getY(), pos.getX()};
                return velocity + (tangent * angular_velocity);
            };
        };

        vector2<S> sample_motion (vector2<D> wheel) { return calc_sample(wheel); };

    private:
        std::function<vector2<S>(vector2<D>)> calc_sample = [] (vector2<D> _) { return vector2<S> {S(), S()}; };
};

}
