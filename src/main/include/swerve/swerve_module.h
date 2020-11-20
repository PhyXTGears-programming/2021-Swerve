#pragma once

#include <cmath>
#include <functional>

#include "vector2.h"
#include "types.h"

namespace swervedrive {

template<class D, class S, class A>
class swerve_module {
    public:
        swerve_module (vector2 position, std::function<void(S, A)> driveFunc) {
            pos = position;
            drive = driveFunc;
        }
        
        void set_motion (motion_function<D, S> mF) { drive(mF(pos)); }

    private:
        vector2 pos;
        std::function<void(S, A)> drive;
};

}
