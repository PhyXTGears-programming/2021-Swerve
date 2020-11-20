#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>

#include <swerve/drive.h>

#include "Constants.h"
#include "subsystems/SwerveWheel.h"

class SwerveDrive : public frc2::SubsystemBase {
    public:
        SwerveDrive();

        void Periodic() override;

        void setMotion(double x, double y, double r);

    private:
        swervedrive::drive<double, double, double>* drive;
};
