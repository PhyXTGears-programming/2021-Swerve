#pragma once

#include <string>

// #define TALON_SRX
#define SPARK_MAX

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
            #ifdef TALON_SRX
            int zeroVal; // value encoder reads when pointing forward
            #endif
            #ifdef SPARK_MAX
            double zeroVal; // value encoder reads when pointing forward (rad)
            #endif
        };

        struct WheelConstants {
            std::string name;
            int drivePin; // PWM (talon) / CAN (spark max)
            int turnPin; // CAN
            Vector position;
            WheelSpinTuning tuning;
            #ifdef SPARK_MAX
            int encoderID;
            bool invertEncoder;
            #endif
        };

        #ifdef TALON_SRX
        const WheelConstants frontLeft  = {"Front Left",  0, 1, {-1.09,  0.87}, {{1.4,   0.001, 0.001}, 1091}};
        const WheelConstants frontRight = {"Front Right", 1, 2, { 1.09,  0.87}, {{1.1,   0,     0},     2361}};
        const WheelConstants backLeft   = {"Back Left",   2, 3, {-1.09, -0.87}, {{0.012, 0,     0},     1037}};
        const WheelConstants backRight  = {"Back Right",  3, 4, { 1.09, -0.87}, {{0.7,   0,     0.8},   1248}};
        #endif
        #ifdef SPARK_MAX
        const WheelConstants frontLeft  = {"Front Left",  4, 8, {-1.014,  1.014}, {{0.5, 0, 0},  2.942625}, 13, true};
        const WheelConstants frontRight = {"Front Right", 1, 5, { 1.014,  1.014}, {{0.5, 0, 0}, -2.555162}, 10, false};
        const WheelConstants backLeft   = {"Back Left",   3, 7, {-1.014, -1.014}, {{0.5, 0, 0}, -0.978606}, 12, true};
        const WheelConstants backRight  = {"Back Right",  2, 6, { 1.014, -1.014}, {{0.5, 0, 0},  3.026575}, 11, false};
        #endif
    }
}
