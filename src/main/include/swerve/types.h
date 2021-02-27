// Copyright 2020 Robby Sammelson

#pragma once

#include <functional>

#include "vector2.h"

namespace swervedrive {

template<class D, class S>
using motion_function = std::function<vector2<S>(vector2<D>)>;

}
