#include "subsystems/SwerveWheel.h"

#include <cmath>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

SwerveWheel::SwerveWheel (constants::swerve::WheelConstants constants)
    : swervedrive::swerve_module<double, double, double>(
        swervedrive::vector2<double>{constants.position.x, constants.position.y},
        [&](swervedrive::vector2<double> speed) { drive(speed); }
    ) {
    wheelSettings = constants;

    driveMotor = new frc::PWMTalonSRX(wheelSettings.drivePin);

    turnMotor = new ctre::phoenix::motorcontrol::can::TalonSRX(wheelSettings.turnPin);
    ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration PIDconfig {ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute};
    turnMotor->ConfigurePID(PIDconfig);
    turnMotor->Config_kP(0, wheelSettings.tuning.pid.P);
    turnMotor->Config_kI(0, wheelSettings.tuning.pid.I);
    turnMotor->Config_kD(0, wheelSettings.tuning.pid.D);
}

void SwerveWheel::drive (swervedrive::vector2<double> speed) {
    setAngle(std::atan2(speed.getY(), speed.getX()));
    setSpeed(std::sqrt(std::pow(speed.getX(), 2) + std::pow(speed.getY(), 2)));
}

void SwerveWheel::setAngle (double rad) {
    double currentPos = encoderToRad(turnMotor->GetSelectedSensorPosition());

    double correction = 2*M_PI * std::floor(currentPos / (2*M_PI) + 0.5);
    double correctedPosition = currentPos - correction;

    double error = std::abs(rad - correctedPosition);
    inverted = M_PI/2 < error && error < 3*M_PI/2;

    if (inverted) {
        if (rad < 0) {
            rad += M_PI;
        } else {
            rad -= M_PI;
        }
    }

    turnMotor->Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::Position, radToEncoder(rad + correction));
}
