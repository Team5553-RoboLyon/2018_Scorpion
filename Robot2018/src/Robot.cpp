
#include <iostream>
#include <string>

#include <Joystick.h>
#include <VictorSP.h>
#include <PWMVictorSPX.h>
#include <Encoder.h>
#include <DriverStation.h>
#include <CameraServer.h>
#include <DoubleSolenoid.h>
#include "WPILib.h"

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot : public frc::IterativeRobot
{
public:
	void RobotInit()
	{
		Joystick1 = new Joystick(0);

		CimDroit1 = new VictorSP(0);
		CimDroit2 = new VictorSP(1);
		CimGauche1 = new VictorSP(2);
		CimGauche2 = new VictorSP(3);

		EncodeurDroit = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
		EncodeurGauche = new Encoder(2, 3, false, Encoder::EncodingType::k4X);

		DoubleSolenoid1 = new DoubleSolenoid(0, 1);
		DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);
		std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;
		vitesseBallShifter = false;

		CimGauche1->Set(0);
		CimGauche2->Set(0);
		CimDroit1->Set(0);
		CimDroit2->Set(0);

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);
	}


	void AutonomousInit() override
	{
		/*std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		std::string L ="L";

		if(gameData[0] == L[0])
		{
			//Code gauche
		}
		else
		{
			//Code droit
		}*/


	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//############ Contrôle du moteur ############
		y = Joystick1->GetY();
		z = Joystick1->GetZ();

		if(y < 0.2 && y > -0.2)
		{
			y = 0;
		}
		if(z < 0.2 && z > -0.2)
		{
			z = 0;
		}

		vitesseDroite = -y - 0.5 * z;
		vitesseGauche = y - 0.5 * z;

		CimDroit1->Set(vitesseDroite);
		CimDroit2->Set(vitesseDroite);
		CimGauche1->Set(vitesseGauche);
		CimGauche2->Set(vitesseGauche);

		//############ Changement de vitesse ############
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

		//############ Valeurs encodeurs ############
		//std::cout << "Encodeur droit : " << EncodeurDroit->Get() << std::endl;
		//std::cout << "Encodeur gauche : " << EncodeurGauche->Get() << std::endl;
	}

	void TestPeriodic()
	{
	}

private:
	Joystick* Joystick1 = 0;

	VictorSP* CimDroit1 = 0;
	VictorSP* CimDroit2 = 0;
	VictorSP* CimGauche1 = 0;
	VictorSP* CimGauche2 = 0;

	Encoder* EncodeurDroit = 0;
	Encoder* EncodeurGauche = 0;

	DoubleSolenoid* DoubleSolenoid1 = 0;

	bool vitesseBallShifter;

	double x, y, z;
	double vitesseDroite, vitesseGauche;
};

START_ROBOT_CLASS(Robot)
