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

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot: public frc::IterativeRobot
{
public:
	Joystick* Joystick1;
	PWMVictorSPX* TankDroit1;
	PWMVictorSPX* TankDroit2;
	PWMVictorSPX* TankGauche1;
	Encoder* anCo2z1;
	Encoder* anCo2z2;
	Servo* servoFenwick;
	std::Fenwick fenwick;
	std::Pince pince;
	std::BaseRoulante Base;
	bool vitesseBallShifter;
	bool sheet = false;
	bool etatFenwick;
	double TicQuonVeut = 0;
	double x, y, z;
	double vitesseDroite, vitesseGauche;
	double ticQuonVeut = 0;
	double distanceQuOnVeut;
	double degre;
	double ticQuOnA;
	double toursQuOnA;
	double position;
	double consigne = 0.0;

	void RobotInit()
	{
		Joystick1 = new Joystick(0);
		servoFenwick = new Servo(6);

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);
	}

	void AutonomousInit() override
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		Base.deplacer(Joystick1);

		Base.changerVitesse(Joystick1->GetRawButton(1));

		pince.attraperCube(Joystick1->GetRawButton(2));

		pince.ejecterCube(Joystick1->GetRawButton(4));

		pince.afficherSwitch();

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
