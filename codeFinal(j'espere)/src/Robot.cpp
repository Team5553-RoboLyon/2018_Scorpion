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

#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"

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
#include <DigitalInput.h>
#include "Base.h"

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot : public frc::IterativeRobot
{
	public:
	Joystick* Joystick1;

	ADXRS450_Gyro* gyro;
	DoubleSolenoid* DoubleSolenoid1;
	DigitalInput* limitSwitch;
	Servo* servoFenwick;
	Servo* servoPince;
	std::Base base;
	std::Fenwick fenwick;
	std::Pince pince;
	PowerDistributionPanel* pdp = new PowerDistributionPanel();
	bool vitesseBallShifter;
	bool sheet = false;
	bool etatFenwick;
	double TicQuonVeut=0;
	double x, y, z;
	double vitesseDroite, vitesseGauche;
	double ticQuonVeut=0;
	double distanceQuOnVeut;
	double degre;
	double ticQuOnA;
	double toursQuOnA;
	double position;
	double consigne = 0;
    int incrementation = 0;




	void RobotInit()
	{
		Joystick1 = new Joystick(0);

		DoubleSolenoid1 = new DoubleSolenoid(0, 1);
		limitSwitch = new DigitalInput(9);
		servoFenwick = new Servo(6);
		servoPince = new Servo(9);
		DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);

		//double distanceQuOnVeut = ((anCo2z1->Get() + anCo2z2->Get())/2)/7.5; //en cm
		//gyro = new ADXRS450_Gyro();
		//double degre = gyro->GetAngle();
		vitesseBallShifter = false;
		//gyro->Calibrate();
		std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);





	}


	void AutonomousInit() override
	{
		//pince.descendrePince (Joystick1, servoPince, limitSwitch);

	}

	void AutonomousPeriodic()
	{

		base.AvancerDistance(50);
		base.AfficherCodeuses();

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//############ Contrôle du moteur ############

		//fenwick.deplacerFenwick(40);
		std::cout<<pdp->GetCurrent(13)<<std::endl;
		fenwick.afficherPosition();
		base.AfficherCodeuses();

		base.Deplacer(Joystick1);

		if(Joystick1->GetTriggerPressed())
		{
			if(vitesseBallShifter)
			{
				DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);
				std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;
				vitesseBallShifter = false;
			}
			else
			{
				DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kReverse);
				std::cout << "*************** VITESSE 2 ACTIVEE ***************" << std::endl;
				vitesseBallShifter = true;
			}
		}

		if(Joystick1->GetRawButton(2))
			{
			pince.descendrePince(Joystick1,servoPince,limitSwitch);
			}
		if(Joystick1->GetRawButton(3))
			{
			consigne = 180;
			fenwick.sommeAllErreurs = 0;
			}
		if(Joystick1->GetRawButton(4))
			{
			pince.lacherCube();
			}
		if(Joystick1->GetRawButton(5))
			{
			consigne = 0;
			fenwick.sommeAllErreurs = 0;



			}
		if(Joystick1->GetRawButton(6))
			{
			consigne = 152;

			fenwick.sommeAllErreurs = 0;

			}
		if(Joystick1->GetRawButton(7))
			{
			consigne = 40;

			fenwick.sommeAllErreurs = 0;

			}
		if(Joystick1->GetRawButton(8))
			{
			position = 0;

			fenwick.sommeAllErreurs = 0;

			}
		if(Joystick1->GetRawButton(9))
		{
			if(etatFenwick==true)
			{
				pince.descendrePince(Joystick1,servoPince,limitSwitch);
				//fenwick.monterDuRobot(Joystick1,servoFenwick);
			}
		}
		if(limitSwitch->Get()==false)
				std::cout<<limitSwitch->Get();
		if(limitSwitch->Get()==true)
			std::cout<<limitSwitch->Get();

		//############ Valeurs encodeurs ############


			/*while(anCo2z1->Get()<TicQuonVeut)
								{
									problemePsychoMoteurDroit1->Set(0.2);
									problemePsychoMoteurDroit1->Set(-0.2);
									problemePsychoMoteurDroit2->Set(-0.2);
									problemePsychoMoteurGauche2->Set(0.2);

									std::printf("%d",anCo2z1->Get());
									if(anCo2z1->Get()>=720)
										sheet=true;


								}
								if(sheet==true)
								{
									problemePsychoMoteurDroit1->Set(0.0);
									problemePsychoMoteurDroit1->Set(-0.0);
									problemePsychoMoteurDroit2->Set(-0.0);
									problemePsychoMoteurGauche2->Set(0.0);
								}

								while(anCo2z2->Get()<TicQuonVeut)
								{
									problemePsychoMoteurDroit1->Set(0.2);
									problemePsychoMoteurDroit1->Set(-0.2);
									problemePsychoMoteurDroit2->Set(-0.2);
									problemePsychoMoteurGauche2->Set(0.2);

									std::printf("%d",anCo2z2->Get());
									if(anCo2z2->Get()>=2450)
										sheet=true;


								}
								if(sheet==true)
								{
									problemePsychoMoteurDroit1->Set(0.0);
									problemePsychoMoteurDroit1->Set(-0.0);
									problemePsychoMoteurDroit2->Set(-0.0);
									problemePsychoMoteurGauche2->Set(0.0);
								}
*/

/*fenwick.positionFenwick(anCo2z1,anCo2z2,position);
fenwick.shifting(Joystick1);*/



	}


	void TestPeriodic()
	{
	}



private:

};

START_ROBOT_CLASS(Robot)
