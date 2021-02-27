#include "subsystems/SwerveDrive.h"

#include <frc/smartdashboard/SmartDashboard.h>

SwerveDrive::SwerveDrive () {
    drive = new swervedrive::drive<double, double, double, double>({flWheel, frWheel, blWheel, brWheel});
}

void SwerveDrive::Periodic () {}

void SwerveDrive::setMotion (double x, double y, double r) {
    drive->set_motion({x, y}, r);
}
