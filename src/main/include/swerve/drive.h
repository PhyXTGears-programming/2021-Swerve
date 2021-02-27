// Copyright 2020 Robby Sammelson

#pragma once

#include <functional>
#include <initializer_list>
#include <vector>

#include "swerve_module.h"
#include "vector2.h"
#include "types.h"

namespace swervedrive {

template<class D, class S, class R, class A>
class drive {
    public:
        drive (std::initializer_list<swerve_module<D, S, A>> modules) {
            drive_modules = new std::vector<swerve_module<D, S, A>>(modules);
        }

        void set_motion (vector2<S> velocity, R angular_velocity) {
            auto motionFunc = calc_motion(velocity, angular_velocity);
            for (auto module : *drive_modules) {
                module.set_motion(motionFunc);
            }
        }

    private:
        motion_function<D, S> calc_motion (vector2<S> velocity, R angular_velocity) {
            return [=](vector2<D> pos) {
                vector2<D> tangent {-1 * pos.getY(), pos.getX()};
                return velocity + (tangent * angular_velocity);
            };
        };

        std::vector<swerve_module<D, S, A>> *drive_modules;
};

}
