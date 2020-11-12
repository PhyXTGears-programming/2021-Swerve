#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#define DEADZONE(v) (v < 0.1 ? 0 : v)

void Robot::RobotInit () {}

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
    m_container.swerveDrive.setMotion(DEADZONE(x) * 0.4, DEADZONE(y) * 0.4, DEADZONE(r) * 0.4);
}

void Robot::TestPeriodic () {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
