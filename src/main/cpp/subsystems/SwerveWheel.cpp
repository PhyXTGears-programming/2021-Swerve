#include "subsystems/SwerveWheel.h"

#include <cmath>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#define PI 3.141592653589

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
    int currentPos = encoderToRad(turnMotor->GetSelectedSensorPosition());
    
    frc::SmartDashboard::PutNumber("Swerve Wheel Rotation (" + wheelSettings.name + ")", currentPos);
    // frc::SmartDashboard::PutNumber("Swerve Wheel Velocity (" + wheelSettings.name + ")", turnMotor->GetSelectedSensorVelocity());
    // frc::SmartDashboard::PutNumber("Swerve Wheel Current (" + wheelSettings.name + ")", turnMotor->GetOutputCurrent());

    int halfRots = std::round((rad - currentPos) / M_PI);

    if (halfRots % 2 == 1) {
        inverted = !inverted;
    }

    rad -= halfRots * M_PI;

    // std::cout << wheelSettings.name << ": " << rad - currentPos << std::endl;

    turnMotor->Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::Position, radToEncoder(rad));
}
