#include "subsystems/SwerveWheel.h"

#include <cmath>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "swerve/rotation.h"

SwerveWheel::SwerveWheel (constants::swerve::WheelConstants constants)
    : swervedrive::swerve_module<double, double, double>(
        swervedrive::vector2<double>{constants.position.x, constants.position.y}
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
    turnEncoder.emplace(turnMotor->GetEncoder());
    turnPid.emplace(turnMotor->GetPIDController());
    
    driveMotor->SetInverted(false);
    turnMotor->SetInverted(true);

    encoder = new ctre::phoenix::sensors::CANCoder(wheelSettings.encoderID);
    encoder->ConfigAbsoluteSensorRange(ctre::phoenix::sensors::AbsoluteSensorRange::Signed_PlusMinus180);

    constexpr double conversionFactor = 2 * M_PI * 0.01816051; // motor rotations to module rad
    turnEncoder->SetPositionConversionFactor(conversionFactor);
    turnEncoder->SetVelocityConversionFactor(conversionFactor / 60.0); // RPM to rad/s

    double currentAngle = encoder->GetAbsolutePosition() * (M_PI / 180.0); // [-180, 180) to [-pi, pi)
    turnEncoder->SetPosition(currentAngle - wheelSettings.tuning.zeroVal);

    turnPid->SetP(wheelSettings.tuning.pid.P);
    turnPid->SetI(wheelSettings.tuning.pid.I);
    turnPid->SetD(wheelSettings.tuning.pid.D);
    #endif
}

void SwerveWheel::drive (double speed, double angle) {
    if (std::fabs(speed) > 0.01) {
        setAngle(angle);
    }
    setSpeed(speed);
}

double SwerveWheel::getAngle () {
    #ifdef TALON_SRX
    return encoderToRad(turnMotor->GetSelectedSensorPosition());
    #endif
    #ifdef SPARK_MAX
    return turnEncoder->GetPosition();
    #endif
}

void SwerveWheel::setAngle (double rad) {
    #ifdef TALON_SRX
    double correction = 0;
    #endif
    #ifdef SPARK_MAX
    double correction = std::copysign(0.04, turnEncoder->GetVelocity()); // add correction to account for lag and momentum
    #endif

    std::cout << "target heading  " << rad << " , " << "current heading " << getAngle() << std::endl;
    std::pair<double, bool> result = swervedrive::module_rotation::calculate_rotation_target(rad, getAngle() + correction);
    inverted = result.second;

    #ifdef TALON_SRX
    turnMotor->Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::Position, radToEncoder(result.first));
    #endif
    #ifdef SPARK_MAX
    turnPid->SetReference(result.first, rev::CANSparkMax::ControlType::kPosition);
    #endif
}
