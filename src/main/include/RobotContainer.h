#pragma once

#include <frc2/command/Command.h>

#include "subsystems/SwerveDrive.h"

class RobotContainer {
    public:
        RobotContainer();

        frc2::Command* GetAutonomousCommand();

        SwerveDrive swerveDrive {true};

    private:
        void ConfigureButtonBindings();
};
