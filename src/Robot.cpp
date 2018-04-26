/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>

#include <iostream>
#include <string>
#include <ADXRS450_Gyro.h>
#include <Joystick.h>
#include <VictorSP.h>
#include <PWMVictorSPX.h>
#include <Encoder.h>
#include <DriverStation.h>
#include <CameraServer.h>
#include <DoubleSolenoid.h>
#include "WPILib.h"
#include <PWMVictorSPX.h>
#include <DigitalInput.h>
#include <AnalogInput.h>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <Pince.h>
#include <BaseRoulante.h>
#include "Grappin.h"
#include "Autonome.h"
#include "Definitions.h"

class Robot: public frc::IterativeRobot
{
	void RobotInit()
	{
		chooser.AddDefault("Depart milieu", "m");
		chooser.AddObject("Depart gauche", "g");
		chooser.AddObject("Depart droite", "d");
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		Joystick1 = new Joystick(0);
		ai = new AnalogInput(0);
		pince.pinceInit();
		base.baseInit();
		//grappin.initBras();

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);

		CameraServer::GetInstance()->StartAutomaticCapture(1);
		CameraServer::GetInstance()->SetSize(0);
	}

	void AutonomousInit() override
	{
		position = chooser.GetSelected()[0];
		std::cout << "Auto selected: " << position << std::endl;

		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		autonome.autonomeInit(gameData[0], &pince);
	}

	void AutonomousPeriodic()
	{
		//base.parcourir_distance(100);
		//base.rotation(30);

		if (position == 'm')
		{
			autonome.departMilieu(&base, &pince);
		}
		else if (position == 'g')
		{
			autonome.departGauche(&base, &pince);
		}
		else if(position == 'd')
		{
			autonome.departDroite(&base, &pince);
		}
	}

	void TeleopInit()
	{
		base.baseInit();
	}

	void TeleopPeriodic()
	{
		//std::cout<<ai->GetVoltage()<<std::endl;

		base.deplacer(Joystick1);
		base.changerVitesse(Joystick1->GetRawButton(1));
		base.afficherCodeuses();
		base.afficherGyro();

		pince.attraperCube(Joystick1->GetRawButton(2));
		pince.ejecterCube(Joystick1->GetRawButton(3));
		pince.positionVerrin(Joystick1->GetRawButton(4));
		pince.ejectionSwitch(Joystick1->GetRawButton(5));
		pince.ajuster(Joystick1->GetPOV());
		pince.deplacer();

		if(Joystick1->GetRawButton(11))
		{
			pince.goToEchangeur(true);
		}
		else if(Joystick1->GetRawButton(9))
		{
			pince.goToSwitch(true);
		}
		else if(Joystick1->GetRawButton(12))
		{
			pince.goToEchangeur(false);
		}
		else if(Joystick1->GetRawButton(10))
		{
			pince.goToSwitch(false);
		}
		else if(Joystick1->GetRawButton(8))
		{
			pince.goToMilieu();
		}
	}

	void TestPeriodic()
	{

	}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	char position;

	Joystick* Joystick1;
	AnalogInput* ai;

	rbl::BaseRoulante base;
	rbl::Pince pince;
	rbl::Autonome autonome;
};

START_ROBOT_CLASS(Robot)
