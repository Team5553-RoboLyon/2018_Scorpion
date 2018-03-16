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
#include <Fenwick.h>
#include <Pince.h>
#include <BaseRoulante.h>
#include <DigitalInput.h>
#include <AnalogInput.h>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot: public frc::IterativeRobot
{
	void RobotInit()
	{
		Joystick1 = new Joystick(0);
		ai = new AnalogInput(0);
	}

	void AutonomousInit() override
	{
		Base.resetPID();
	}

	void AutonomousPeriodic()
	{
		Base.parcourir_distance(300);
		/*if(pinceEnBas == false)
		{
			pince.descendreDebutMatch();
			pinceEnBas = true;
		}

		if (fenwick.goToSwitch() == true)
		{
			if (Base.parcourir_distance(300) < 25)
			{
				pince.ejecterCube(true);
			}
		}*/

		/*static bool autoFinie = false;

		if(autoFinie == false)
		{
			Base.parcourir_distance(90);

			std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
			std::string L = "L";

			if(gameData[0] == L[0]) //Coté gauche
			{
				Base.rotation(-90);
				Base.parcourir_distance(110);
				Base.rotation(90);
			}
			else //Coté droit
			{
				Base.rotation(90);
				Base.parcourir_distance(110);
				Base.rotation(-90);
			}

			fenwick.goToSwitch();

			Base.parcourir_distance(100);

			pince.ejecterCube(true);

			Base.arreter();

			autoFinie = true;
		}

		pince.ejecterCube(false);*/
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//fenwick.deplacer();
		//std::cout<<ai->GetVoltage()<<std::endl;
		Base.deplacer(Joystick1);

		Base.changerVitesse(Joystick1->GetRawButton(1));

		pince.attraperCube(Joystick1->GetRawButton(2));

		pince.ejecterCube(Joystick1->GetRawButton(5));

		pince.ajuster(Joystick1->GetPOV());

		// CODE POUR MONTER LE FENWICK
		/*if(Joystick1->GetRawButton(3))
		{
			Base.arreter();
			fenwick.goToZero();

		}
		else if(Joystick1->GetRawButton(9))
		{
			Base.arreter();
			fenwick.goToSwitch();
		}
		else if(Joystick1->GetRawButton(4))
		{
			Base.arreter();
			fenwick.goToScale();
		}

		// CODE POUR MONTER LE ROBOT
		if (Joystick1->GetRawButton(7))
		{
			Base.arreter();
			fenwick.monteeFinaleFenwick();

			while(Joystick1->GetRawButton(8) == false)
			{
				fenwick.deplacer();
				Base.deplacer(Joystick1);
				Base.changerVitesse(Joystick1->GetRawButton(1));
				pince.ajuster(Joystick1->GetPOV());
			}

			Base.arreter();
			fenwick.monteeDuRobot();
		}

		if (Joystick1->GetRawButton(11))
		{
			fenwick.monter();
		}
		else if (Joystick1->GetRawButton(12))
		{
			fenwick.descendre();
		}
		else
		{
			fenwick.stop();
		}*/
	}

	void TestPeriodic()
	{

	}

private:
	Joystick* Joystick1;
	AnalogInput* ai;

	std::Fenwick fenwick;
	std::Pince pince;
	std::BaseRoulante Base;

	bool pinceEnBas = false;

};

START_ROBOT_CLASS(Robot)
