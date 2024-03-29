#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <adi/ADIS16470_IMU.h>

#include <swerve/drive.h>

#include "Constants.h"
#include "subsystems/SwerveWheel.h"

class SwerveDrive : public frc2::SubsystemBase {
    public:
        SwerveDrive(bool fieldOriented = false);

        void Periodic() override;

        void setMotion(double x, double y, double r);

    private:
        swervedrive::drive<double, double, double>* drive;

        SwerveWheel flWheel {constants::swerve::frontLeft};
        SwerveWheel frWheel {constants::swerve::frontRight};
        SwerveWheel blWheel {constants::swerve::backLeft};
        SwerveWheel brWheel {constants::swerve::backRight};

        frc::ADIS16470_IMU gyro {};

        bool fieldOriented;
};
