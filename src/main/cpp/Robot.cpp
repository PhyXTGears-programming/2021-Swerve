#include "Robot.h"

#include <iostream>
#include <cmath>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#define DEADZONE(v) (std::abs(v) < 0.1 ? 0 : v)

void Robot::RobotInit () {
    std::cout << std::fixed;
}

void Robot::RobotPeriodic () {
    frc2::CommandScheduler::GetInstance().Run();

    frc::SmartDashboard::PutNumber("FL abs", m_container.swerveDrive.flWheel.encoder->GetAbsolutePosition());
    frc::SmartDashboard::PutNumber("FL rel", m_container.swerveDrive.flWheel.turnEncoder->GetPosition() * 180.0 / M_PI);

    frc::SmartDashboard::PutNumber("FR abs", m_container.swerveDrive.frWheel.encoder->GetAbsolutePosition());
    frc::SmartDashboard::PutNumber("FR rel", m_container.swerveDrive.frWheel.turnEncoder->GetPosition() * 180.0 / M_PI);

    frc::SmartDashboard::PutNumber("BL abs", m_container.swerveDrive.blWheel.encoder->GetAbsolutePosition());
    frc::SmartDashboard::PutNumber("BL rel", m_container.swerveDrive.blWheel.turnEncoder->GetPosition() * 180.0 / M_PI);
    
    frc::SmartDashboard::PutNumber("BR abs", m_container.swerveDrive.brWheel.encoder->GetAbsolutePosition());
    frc::SmartDashboard::PutNumber("BR rel", m_container.swerveDrive.brWheel.turnEncoder->GetPosition() * 180.0 / M_PI);
}

void Robot::DisabledInit () {}

void Robot::DisabledPeriodic () {}

void Robot::AutonomousInit () {}

void Robot::AutonomousPeriodic () {}

void Robot::TeleopInit () {}

void Robot::TeleopPeriodic () {
    double x = driver.GetLeftX();
    double y = -1 * driver.GetLeftY();
    double r = driver.GetRightX();
    x = DEADZONE(x) * 1.0;
    y = DEADZONE(y) * 1.0;
    r = DEADZONE(r);
    r = r*r*r * 0.5;
    std::cout << x << ", " << y << ", " << r << std::endl;
    m_container.swerveDrive.setMotion(x, y, r);
}

void Robot::TestPeriodic () {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
