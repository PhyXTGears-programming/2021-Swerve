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

    #ifdef TALON_SRX
    driveMotor = new frc::PWMTalonSRX(wheelSettings.drivePin);

    turnMotor = new ctre::phoenix::motorcontrol::can::TalonSRX(wheelSettings.turnPin);
    ctre::phoenix::motorcontrol::can::TalonSRXPIDSetConfiguration PIDconfig {ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute};
    turnMotor->ConfigurePID(PIDconfig);
    turnMotor->Config_kP(0, wheelSettings.tuning.pid.P);
    turnMotor->Config_kI(0, wheelSettings.tuning.pid.I);
    turnMotor->Config_kD(0, wheelSettings.tuning.pid.D);
    #endif
    #ifdef SPARK_MAX
    driveMotor = new rev::CANSparkMax(wheelSettings.drivePin, rev::CANSparkMax::MotorType::kBrushless);
    turnMotor = new rev::CANSparkMax(wheelSettings.turnPin, rev::CANSparkMax::MotorType::kBrushless);

    encoder = new ctre::phoenix::sensors::CANCoder(wheelSettings.encoderID);
    encoder->ConfigAbsoluteSensorRange(ctre::phoenix::sensors::AbsoluteSensorRange::Signed_PlusMinus180);

    constexpr double conversionFactor = 2 * M_PI * 0.1816051; // motor rotations to module rad
    turnMotor->GetEncoder().SetPositionConversionFactor(conversionFactor);
    turnMotor->GetEncoder().SetVelocityConversionFactor(conversionFactor / 60.0); // RPM to rad/s

    double currentAngle = encoder->GetAbsolutePosition() * (M_PI / 180.0); // [-180, 180) to [-pi, pi)
    turnMotor->GetEncoder().SetPosition(currentAngle - wheelSettings.tuning.zeroVal);

    turnMotor->GetPIDController().SetP(wheelSettings.tuning.pid.P);
    turnMotor->GetPIDController().SetI(wheelSettings.tuning.pid.I);
    turnMotor->GetPIDController().SetD(wheelSettings.tuning.pid.D);
    #endif
}

void SwerveWheel::drive (swervedrive::vector2<double> speed) {
    setAngle(std::atan2(speed.getY(), speed.getX()));
    setSpeed(std::sqrt(std::pow(speed.getX(), 2) + std::pow(speed.getY(), 2)));
}

void SwerveWheel::setAngle (double rad) {
    #ifdef TALON_SRX
    double currentPos = encoderToRad(turnMotor->GetSelectedSensorPosition());
    #endif
    #ifdef SPARK_MAX
    double currentPos = turnMotor->GetEncoder().GetPosition();
    #endif

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

    #ifdef TALON_SRX
    turnMotor->Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::Position, radToEncoder(rad + correction));
    #endif
    #ifdef SPARK_MAX
    turnMotor->GetPIDController().SetReference(rad, rev::ControlType::kPosition);
    #endif
}
