#include "Robot.h"

#include <cmath>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#define DEADZONE(v) (std::abs(v) < 0.04 ? 0 : v)

void Robot::RobotInit () {
    std::cout << std::fixed;
}

void Robot::RobotPeriodic () {
    frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit () {}

void Robot::DisabledPeriodic () {}

void Robot::AutonomousInit () {}

void Robot::AutonomousPeriodic () {}

void Robot::TeleopInit () {}

void Robot::TeleopPeriodic () {
    double x = driver.GetX(frc::GenericHID::kLeftHand);
    double y = -1 * driver.GetY(frc::GenericHID::kLeftHand);
    double r = driver.GetX(frc::GenericHID::kRightHand);
    x = DEADZONE(x) * 1.0;
    y = DEADZONE(y) * 1.0;
    r = DEADZONE(r);
    r = r*r*r * 0.5;
    // std::cout << x << ", " << y << ", " << r << std::endl;
    m_container.swerveDrive.setMotion(x, y, r);
}

void Robot::TestPeriodic () {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
