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
#include "Definitions.h"

class Robot: public frc::IterativeRobot
{


	void RobotInit()
	{
		Joystick1 = new Joystick(0);
		ai = new AnalogInput(0);
		pince.pinceInit();
		base.baseInit();

		//CameraServer::GetInstance()->StartAutomaticCapture(0);
		//CameraServer::GetInstance()->SetSize(0);
	}

	void AutonomousInit() override
	{
		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

		if (gameData[0] == 'L')
		{
			rotation1 = -90;
			rotation2 = 90;
		}
		else
		{
			rotation1 = 90;
			rotation2 = -90;
		}
		base.resetPID();
	}

	void AutonomousPeriodic()
	{
		/*
		 * PIDs remarques :
		 * Les fonctions actualisent les vitesses et renvoient l'erreur
		 * Pour eviter des repetitions, on met la commande de changement d'etat a la fin du switch
		 */

		static unsigned int etat = 1;
		static const double toleranceAvancer = 5; // TODO  TOLERANCE A DETERMINER
		static const double toleranceRotation = 5; // TODO  TOLERANCE A DETERMINER
		double erreur = 1000;

		switch(etat)
		{
		//Avancer
		case 1:
			erreur = base.parcourir_distance(100);
			break;

		//Tourner
		case 2:
			erreur = base.rotation(rotation1);
			break;

		//Avancer
		case 3:
			erreur = base.parcourir_distance(100);
			break;


		//Tourner
		case 4:
			erreur = base.rotation(rotation2);
			break;

		//Avancer
		case 5:
			erreur = base.parcourir_distance(100);
			break;

		// TODO Descendre pince
		case 6:
			etat++;
			break;

		//Ejecter cube
		case 7:
			pince.ejecterCube(true); //On simule un bouton appuyé et on passe au suivant
			etat++;
			break;

		//Fin
		default:
			pince.ejecterCube(false); //On re-appelle ejecter cube en simulant un bouton relaché pour que la pince s'arrete
			break;
		}

		//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
		if(etat == 1 || etat == 3 || etat == 5)
		{
			if(erreur < toleranceAvancer && erreur > -toleranceAvancer)
			{
				etat++;
				base.arreter();
				base.resetPID();
			}
		}
		else if(etat == 2 || etat == 4)
		{
			if(erreur < toleranceRotation && erreur > -toleranceRotation)
			{
				etat++;
				base.arreter();
				base.resetPID();
			}
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//std::cout<<ai->GetVoltage()<<std::endl;

		base.deplacer(Joystick1);
		base.changerVitesse(Joystick1->GetRawButton(1));
		//base.afficherCodeuses();
		//base.afficherGyro();

		pince.attraperCube(Joystick1->GetRawButton(2));
		pince.ejecterCube(Joystick1->GetRawButton(3));

		pince.afficherPosition();

		pince.ajuster(Joystick1->GetPOV());
		pince.pinceIntermediaire();

		if(Joystick1->GetRawButton(11))
		{
			pince.goToEchangeur(true);
		}
		else if(Joystick1->GetRawButton(9))
		{
			pince.goToSwitch(true);
		}
		else if(Joystick1->GetRawButton(7))
		{
			pince.goToScale(true);
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
		pince.deplacer();

		//grappin.treuilMonter(Joystick1->GetRawButton(6));
	}

	void TestPeriodic()
	{

	}

private:

	int rotation1, rotation2;

	Joystick* Joystick1;
	AnalogInput* ai;

	rbl::BaseRoulante base;
	rbl::Pince pince;
	rbl::Grappin grappin;
};

START_ROBOT_CLASS(Robot)
