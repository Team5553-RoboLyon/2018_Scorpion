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
public:
	Joystick* Joystick1;
	//std::Fenwick fenwick;
	std::Pince pince;
	std::BaseRoulante Base;
	AnalogInput* ai;


	void RobotInit()
	{
		Joystick1 = new Joystick(0);
		ai = new AnalogInput(0);

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);
	}

	void AutonomousInit() override
	{
		Base.parcourir_distance(100);

		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		std::string L = "L";

		if(gameData[0] == L[0]) //Coté gauche
		{
			Base.rotation(-90);
			Base.parcourir_distance(100);
			Base.rotation(90);
		}
		else //Coté droit
		{
			Base.rotation(90);
			Base.parcourir_distance(100);
			Base.rotation(-90);
		}

		Base.parcourir_distance(100);

		Base.arreter();
	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//std::cout<<ai->GetVoltage()<<std::endl;
		Base.deplacer(Joystick1);

		Base.changerVitesse(Joystick1->GetRawButton(1));

		//pince.attraperCube(Joystick1->GetRawButton(2));

		//pince.ejecterCube(Joystick1->GetRawButton(4));

		//pince.afficherSwitch();

		pince.ajuster(Joystick1->GetPOV());

		// CODE POUR MONTER LE FENWICK
//		if(Joystick1->GetRawButton(12))
//		{
//			Base.arreter();
//			fenwick.goToZero();
//		}
//		else if(Joystick1->GetRawButton(10))
//		{
//			Base.arreter();
//			fenwick.goToSwitch();
//		}
//		else if(Joystick1->GetRawButton(8))
//		{
//			Base.arreter();
//			fenwick.goToScale);
//		}

		// CODE POUR MONTER LE ROBOT
//		if (Joystick1->GetRawButton(11))
//		{
//			Base.arreter();
//			fenwick.monteeFinaleFenwick();
//
//			while(Joystick1->GetRawButton(11) == false)
//			{
//				Base.deplacer(Joystick1);
//				Base.changerVitesse(Joystick1->GetRawButton(1));
//				pince.ajuster(Joystick1->GetPOV());
//			}
//
//			Base.arreter();
//			fenwick.monteeDuRobot();
//		}
	}

	void TestPeriodic()
	{

	}

};

START_ROBOT_CLASS(Robot)
