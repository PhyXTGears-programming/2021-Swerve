#include "subsystems/SwerveDrive.h"

#include <frc/smartdashboard/SmartDashboard.h>

SwerveDrive::SwerveDrive () {}

void SwerveDrive::Periodic () {

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
