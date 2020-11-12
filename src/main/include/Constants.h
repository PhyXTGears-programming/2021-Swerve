/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

namespace constants {
    struct Vector {
        double x, y;
    };

    struct PIDTuning {
        double P, I, D;
    };

    namespace swerve {
        struct WheelSpinTuning {
            PIDTuning pid;
            int zeroVal; // value encoder reads when pointing foreward
        };

        struct WheelConstants {
            std::string name;
            int drivePin; // PWM
            int turnPin; // CAN
            Vector position;
            WheelSpinTuning tuning;
        };

        const WheelConstants frontLeft  = {"Front Left",  0, 1, {-1.09,  0.87}, {{1.4,   0.001, 0.001}, 1091}};
        const WheelConstants frontRight = {"Front Right", 1, 2, { 1.09,  0.87}, {{1.1,   0,     0},     2361}}; // P: 1
        const WheelConstants backLeft   = {"Back Left",   2, 3, {-1.09, -0.87}, {{0.012, 0,     0},     1037}};
        const WheelConstants backRight  = {"Back Right",  3, 4, { 1.09, -0.87}, {{0.7,   0,     0.8},   1248}};
    }
}
