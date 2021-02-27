#pragma once

#include <frc/PWMTalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>

#include <swerve/vector2.h>
#include <swerve/swerve_module.h>

#include "Constants.h"

class SwerveWheel : public swervedrive::swerve_module<double, double, double> {
    public:
        SwerveWheel(constants::swerve::WheelConstants constants);

        void drive(swervedrive::vector2<double> speed);

    private:
        void setAngle(double angle);
        void setSpeed (double speed) { driveMotor->Set(inverted ? -speed : speed); }

        int radToEncoder (double rad) { return (int)(rad * 651.8986469) + wheelSettings.tuning.zeroVal; }
        double encoderToRad (int encoder) { return (encoder - wheelSettings.tuning.zeroVal) / 651.8986469; }

        constants::swerve::WheelConstants wheelSettings;

        frc::PWMTalonSRX* driveMotor;
        ctre::phoenix::motorcontrol::can::TalonSRX* turnMotor;

        bool inverted = false;
};
