#pragma once

#define SMART_MAX

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/PWMTalonSRX.h>

#include "RobotContainer.h"

class Robot : public frc::TimedRobot {
    public:
        void RobotInit() override;
        void RobotPeriodic() override;
        void DisabledInit() override;
        void DisabledPeriodic() override;
        void AutonomousInit() override;
        void AutonomousPeriodic() override;
        void TeleopInit() override;
        void TeleopPeriodic() override;
        void TestPeriodic() override;

    private:
        RobotContainer m_container;

        frc::XboxController driver {0};
};
