#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <VictorSP.h>
#include <Joystick.h>
#include <CameraServer.h>
#include <Encoder.h>
#include "WPILib.h"
#include <thread>

#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"

class Robot : public frc:: IterativeRobot {

public:
	void RobotInit()
	{
		CimDroit1 = new VictorSP(0);
		CimDroit2 = new VictorSP(1);
		CimGauche1 = new VictorSP(2);
		CimGauche2 = new VictorSP(3);

		CimGauche1->Set(0);
		CimGauche2->Set(0);
		CimDroit1->Set(0);
		CimDroit2->Set(0);

		EncodeurDroit = new Encoder (0,1, false, Encoder::EncodingType::k4X);
		EncodeurDroit->Reset();
		EncodeurDroit->SetReverseDirection(false);

		EncodeurGauche = new Encoder (2,3, false, Encoder::EncodingType::k4X);
		EncodeurGauche->Reset();
		EncodeurGauche->SetReverseDirection(true);

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);
	}

	void DisabledInit()
	{

	}

	void DisabledPeriodic()
	{

	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		pulsesParTours = 360;
		distanceParTour = 48;
		distance_a_parcourir = 0;
		integrale = 0;
		/*iMin = ?;
		iMax = ?;*/

		kP = 2;
		kI = 0;
		kD = 0;
	}

	void TeleopPeriodic()
	{
		distance_parcourue = ((EncodeurDroit->Get() + EncodeurGauche->Get()) /2) /7.5;
		erreur = (distance_a_parcourir - distance_parcourue) / distance_a_parcourir;

		proportionelle = kP * erreur;

		integrale += erreur;
		/*if(integrale > iMax)
		{
			integrale = iMax;
		}
		else if(integrale < iMin)
		{
			integrale = iMin;
		}*/
		integrale = kI * integrale;

		derivee = kD * (erreur - erreurPrecedente);
		erreurPrecedente = erreur;

		vitesse = proportionelle + integrale + derivee;

		CimGauche1->Set(-vitesse);
		CimGauche2->Set(-vitesse);
		CimDroit1->Set(vitesse);
		CimDroit2->Set(vitesse);

		std::cout << distance_parcourue << std::endl;
	}
	void TestPeriodic()
	{

	}


private:
	VictorSP* CimDroit1 = 0;
	VictorSP* CimDroit2 = 0;
	VictorSP* CimGauche1 = 0;
	VictorSP* CimGauche2 = 0;

	Encoder* EncodeurDroit;
	Encoder* EncodeurGauche;

	double pulsesParTours, distanceParTour;
	double distance_a_parcourir, distance_parcourue, erreur, erreurPrecedente, vitesse;
	double proportionelle, kP;
	double integrale, iMin, iMax, kI;
	double derivee, kD;
};

START_ROBOT_CLASS(Robot)
