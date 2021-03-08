#pragma once

#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"

#ifdef TALON_SRX
#include <frc/PWMTalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#endif
#ifdef SPARK_MAX
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/sensors/CANCoder.h>
#endif

#include <swerve/vector2.h>
#include <swerve/swerve_module.h>

class SwerveWheel : public swervedrive::swerve_module<double, double, double> {
    public:
        SwerveWheel(constants::swerve::WheelConstants constants);

        void drive(double speed, double angle) override;

        double getAngle();

    private:
        void setAngle(double angle);
        void setSpeed (double speed) {
            driveMotor->Set(inverted ? -speed : speed);
        }

        #ifdef TALON_SRX
        int radToEncoder (double rad) { return (int)(rad * 651.8986469) + wheelSettings.tuning.zeroVal; }
        double encoderToRad (int encoder) { return (encoder - wheelSettings.tuning.zeroVal) / 651.8986469; }
        #endif

        constants::swerve::WheelConstants wheelSettings;

        #ifdef TALON_SRX
        frc::PWMTalonSRX* driveMotor;
        ctre::phoenix::motorcontrol::can::TalonSRX* turnMotor;
        #endif
        #ifdef SPARK_MAX
        rev::CANSparkMax *driveMotor, *turnMotor;
        ctre::phoenix::sensors::CANCoder* encoder;
        #endif

        bool inverted = false;
};
