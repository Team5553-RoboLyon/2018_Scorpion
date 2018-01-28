#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <VictorSP.h>
#include <Joystick.h>
#include <CameraServer.h>
#include "WPILib.h"
#include <thread>

class Robot : public frc:: IterativeRobot {

public:
	void RobotInit()
	{
		Joystick1 = new Joystick(0);
		CimDroit1 = new VictorSP(0);
		CimDroit2 = new VictorSP(1);
		CimGauche1 = new VictorSP(2);
		CimGauche2 = new VictorSP(3);


		CimGauche1->Set(0);
		CimGauche2->Set(0);
		CimDroit1->Set(0);
		CimDroit2->Set(0);

		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->SetSize(0);
	}

	void DisabledInit() {}

	void DisabledPeriodic()
	{
	}

	void AutonomousInit()
	{
	}

	void AutonomousPeriodic()
	{
		toursGauche = EncodeurGauche.Get();
				toursPrevusGauche = 350;
				std::cout << toursGauche << std::endl;


				if(toursGauche > toursPrevusGauche || toursGauche < -toursPrevusGauche)
				{
					RampeGarice(0.5);
				}
				else
				{
					CimGauche1->Set(0);
					CimGauche2->Set(0);
					CimDroit1->Set(0);
					CimDroit2->Set(0);
				}
				vitesseEncodeurGauche = EncodeurGauche.GetDistancePerPulse ();

				toursDroit = EncodeurDroit.Get();
						toursPrevusDroit = -350;
						std::cout << toursDroit << std::endl;


						if(toursDroit < toursPrevusDroit || toursDroit > -toursPrevusDroit)
						{
							RampeGarice(0.2);
						}
						else
						{
							CimGauche1->Set(0);
							CimGauche2->Set(0);
							CimDroit1->Set(0);
							CimDroit2->Set(0);
						}
						vitesseEncodeurDroit = EncodeurDroit.GetDistancePerPulse();
	}

	void TeleopInit()

	{
	}

	void TeleopPeriodic()
	{
		double y = Joystick1->GetY();
		double z = Joystick1->GetZ();

		CimGauche1->Set(-y+0.5*z);
		CimGauche2->Set(-y+0.5*z);
		CimDroit1->Set(y+0.5*z);
		CimDroit2->Set(y+0.5*z);

	}
	void TestPeriodic()
	{
	}

	void RampeGarice(double vitesse)
	{
		static double consignePrecedente=0;
		double vitesseReele;
		if(vitesse>vitesseReele)
		{
			for (vitesseReele = consignePrecedente ; vitesseReele < vitesse ; vitesseReele += 0.000005)
					{
						CimGauche1->Set(vitesseReele);
						CimGauche2->Set(vitesseReele);
						CimDroit1->Set(-vitesseReele);
						CimDroit2->Set(-vitesseReele);
						consignePrecedente = vitesseReele;
					}
		}
		else
		{
			for (vitesseReele = consignePrecedente ; vitesseReele > vitesse ; vitesseReele -= 0.000005)
					{
						CimGauche1->Set(vitesseReele);
						CimGauche2->Set(vitesseReele);
						CimDroit1->Set(-vitesseReele);
						CimDroit2->Set(-vitesseReele);
						consignePrecedente = vitesseReele;
					}
		}
	}

private:
	Joystick* Joystick1 = 0;
	VictorSP* CimDroit1 = 0;
	VictorSP* CimDroit2 = 0;
	VictorSP* CimGauche1 = 0;
	VictorSP* CimGauche2 = 0;
	Encoder* Encodeur = 0;
	frc::Encoder EncodeurGauche{0,1, false, Encoder::EncodingType::k4X};
	frc::Encoder EncodeurDroit{2,3, false, Encoder::EncodingType::k4X};

	double toursPrevusGauche, toursGauche, toursDroit, toursPrevusDroit, vitesseEncodeurDroit, vitesseEncodeurGauche, vitesseReele, vitesse ;
};

START_ROBOT_CLASS(Robot)
