#include "subsystems/SwerveDrive.h"

#include <frc/smartdashboard/SmartDashboard.h>

SwerveDrive::SwerveDrive () {
    // frc::SmartDashboard::PutNumber("Setpoint (FL)", 0.0);
    // frc::SmartDashboard::PutNumber("Setpoint (FR)", 0.0);
    // frc::SmartDashboard::PutNumber("Setpoint (BL)", 0.0);
    // frc::SmartDashboard::PutNumber("Setpoint (BR)", 0.0);
}

void SwerveDrive::Periodic () {
    // turnFL.setAngle(frc::SmartDashboard::GetNumber("Setpoint (FL)", 0.0));
    // turnFR.setAngle(frc::SmartDashboard::GetNumber("Setpoint (FR)", 0.0));
    // turnBL.setAngle(frc::SmartDashboard::GetNumber("Setpoint (BL)", 0.0));
    // turnBR.setAngle(frc::SmartDashboard::GetNumber("Setpoint (BR)", 0.0));

    std::function<swervedrive::vector2<double>(constants::Vector)> getSpeedFunction = [&](constants::Vector location) -> swervedrive::vector2<double> {
        return drive.sample_motion({location.x, location.y});
    };

    turnFL.drive(getSpeedFunction);
    turnFR.drive(getSpeedFunction);
    turnBL.drive(getSpeedFunction);
    turnBR.drive(getSpeedFunction);
}

void SwerveDrive::setMotion (double x, double y, double r) {
    drive.set_motion({x, y}, r);
}
