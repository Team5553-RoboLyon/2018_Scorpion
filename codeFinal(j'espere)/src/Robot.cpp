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

		/*fenwick.deplacerFenwick(40);
		fenwick.afficherPosition();*/

		if (Joystick1 -> GetRawButton(1))
		{
			Base.changerVitesse();
		}

		pince.attraperCube(Joystick1->GetRawButton(2));

		pince.ejecterCube(Joystick1->GetRawButton(4));

		//pince.descendreDebutMatch(); -> Pour la periode auto

		if (Joystick1->GetRawButton(3))
		{
			consigne = 20;
			fenwick.deplacerFenwick(consigne);
			fenwick.sommeAllErreurs = 0;
		}

		if (Joystick1->GetRawButton(5))
		{
			consigne = 0;
			fenwick.sommeAllErreurs = 0;

		}
		if (Joystick1->GetRawButton(6))
		{
			consigne = 152;

			fenwick.sommeAllErreurs = 0;

		}
		if (Joystick1->GetRawButton(7))
		{
			consigne = 40;

			fenwick.sommeAllErreurs = 0;

		}
		if (Joystick1->GetRawButton(8))
		{
			position = 0;

			fenwick.sommeAllErreurs = 0;

		}
		if (Joystick1->GetRawButton(9))
		{
			if (etatFenwick == true)
			{
				pince.descendreDebutMatch();
				fenwick.monterDuRobot(Joystick1, anCo2z1, anCo2z2, servoFenwick);
			}
		}

		//############ Valeurs encodeurs ############
		//std::cout << "Encodeur droit : " << anCo2z1->Get() << std::endl;
		//std::cout << "Encodeur gauche : " << anCo2z2->Get() << std::endl;

		/*while(anCo2z1->Get()<TicQuonVeut)
		 {
		 TankDroit1->Set(0.2);
		 TankDroit1->Set(-0.2);
		 TankDroit2->Set(-0.2);
		 TankGauche2->Set(0.2);

		 std::printf("%d",anCo2z1->Get());
		 if(anCo2z1->Get()>=720)
		 sheet=true;


		 }
		 if(sheet==true)
		 {
		 TankDroit1->Set(0.0);
		 TankDroit1->Set(-0.0);
		 TankDroit2->Set(-0.0);
		 TankGauche2->Set(0.0);
		 }

		 while(anCo2z2->Get()<TicQuonVeut)
		 {
		 TankDroit1->Set(0.2);
		 TankDroit1->Set(-0.2);
		 TankDroit2->Set(-0.2);
		 TankGauche2->Set(0.2);

		 std::printf("%d",anCo2z2->Get());
		 if(anCo2z2->Get()>=2450)
		 sheet=true;


		 }
		 if(sheet==true)
		 {
		 TankDroit1->Set(0.0);
		 TankDroit1->Set(-0.0);
		 TankDroit2->Set(-0.0);
		 TankGauche2->Set(0.0);
		 }
		 */

		//fenwick.positionFenwick(anCo2z1,anCo2z2,position);
		//fenwick.shifting(Joystick1);

	}

	void TestPeriodic()
	{

	}

private:

};

START_ROBOT_CLASS(Robot)
