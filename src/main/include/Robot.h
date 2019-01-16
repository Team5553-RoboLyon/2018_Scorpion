#pragma once

#include <iostream>
#include <string>
#include <frc/WPILib.h>
#include <frc/LiveWindow/LiveWindow.h>

#include "Robot.h"
#include "Pince.h"
#include "BaseRoulante.h"
#include "Grappin.h"
#include "Autonome.h"
#include "Definitions.h"

using namespace frc;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

private:
    LiveWindow& m_lw = *LiveWindow::GetInstance();
    SendableChooser<std::string> chooser;
    char position;

    Joystick* Joystick1;
    AnalogInput* ai;

    BaseRoulante base;
    Pince pince;
    Autonome autonome;
};