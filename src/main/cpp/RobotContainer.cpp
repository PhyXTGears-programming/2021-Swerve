#include "RobotContainer.h"

RobotContainer::RobotContainer() {
    ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {}

frc2::Command* RobotContainer::GetAutonomousCommand() {
    return nullptr;
}
