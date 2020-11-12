#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>

#include "Constants.h"
#include "subsystems/SwerveWheel.h"
#include "swerve/drive.h"

class SwerveDrive : public frc2::SubsystemBase {
    public:
        SwerveDrive();

        void Periodic() override;

        void setMotion(double x, double y, double r);

    private:
        SwerveWheel turnFL {constants::swerve::frontLeft};
        SwerveWheel turnFR {constants::swerve::frontRight};
        SwerveWheel turnBL {constants::swerve::backLeft};
        SwerveWheel turnBR {constants::swerve::backRight};

        swervedrive::Drive<double, double, double> drive {};
};
