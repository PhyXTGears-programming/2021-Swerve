// Copyright 2020 Robby Sammelson

#pragma once

#include <cmath>
#include <functional>

#include "vector2.h"
#include "types.h"

namespace swervedrive {

template<class D, class S, class A>
class swerve_module {
    public:
        swerve_module (vector2<D> position, std::function<void(vector2<S>)> driveFunc) {
            pos = position;
            drive = driveFunc;
        }

        void set_motion (motion_function<D, S> mF) { drive(mF(pos)); }

    private:
        vector2<D> pos;
        std::function<void(vector2<S>)> drive;
};

}
