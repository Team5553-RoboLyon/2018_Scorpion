/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <frc/WPILib.h>

#include "Robot.h"
#include "Pince.h"
#include "BaseRoulante.h"
#include "Grappin.h"
#include "Autonome.h"
#include "Definitions.h"

using namespace frc;


void Robot::RobotInit()
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

void Robot::AutonomousInit()
{
	position = chooser.GetSelected()[0];
	std::cout << "Auto selected: " << position << std::endl;

	std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	autonome.autonomeInit(gameData[0], &pince);
}

void Robot::AutonomousPeriodic()
{
	//base.parcourir_distance(100);
	//base.rotation(30);

	//kPRotation = 0.050 pour cot�s et 0.075 pour milieu ######## PARDONNEZ MOI SVP ########
	if (position == 'm')
	{
		base.kPRotation = 0.075;
		autonome.departMilieu(&base, &pince);
	}
	else if (position == 'g')
	{
		base.kPRotation = 0.05;
		autonome.departGauche(&base, &pince);
	}
	else if(position == 'd')
	{
		base.kPRotation = 0.05;
		autonome.departDroite(&base, &pince);
	}
}

void Robot::TeleopInit()
{
	base.baseInit();
}

void Robot::TeleopPeriodic()
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


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
