/*
 * Grappin.cpp
 *
 *  Created on: 8 avr. 2018
 *      Author: Nathan
 */

#include <iostream>
#include <frc/WPILib.h>

#include "Grappin.h"
#include "Definitions.h"

using namespace frc;


Grappin::Grappin()
{
	// TODO Auto-generated constructor stub
	Treuil = new VictorSP(PWM_TREUIL);
	Treuil-> Set(0);

	VerinBas = new DoubleSolenoid(PCM_VERIN_GRAPIN_BAS_A, PCM_VERIN_GRAPIN_BAS_B);
	VerinHaut = new DoubleSolenoid(PCM_VERIN_GRAPIN_HAUT_A, PCM_VERIN_GRAPIN_HAUT_B);

	Joystick1 = new Joystick(0);

}

void Grappin::initBras()
{


	VerinBas->Set(frc::DoubleSolenoid::Value::kForward);
	VerinHaut->Set(frc::DoubleSolenoid::Value::kForward);
	verrinActif = false;
	verrinActif2 = false;


}



void Grappin::deployerBras(bool boutonPresse)
{
	if(boutonPresse == true && boutonPrecedent == false)
	{
		if(verrinActif == true)
		{
			VerinBas->Set(frc::DoubleSolenoid::Value::kReverse);
			verrinActif = false;

		}
		else if(verrinActif == false)
		{
			VerinBas->Set(frc::DoubleSolenoid::Value::kForward);
			verrinActif = true;
		}

	boutonPrecedent = true;
	}
	else if (boutonPresse == false)
	{
		boutonPrecedent = false;
	}

}

void Grappin::deployerMousqueton(bool boutonPresse2)
{
	if(boutonPresse2 == true && boutonPrecedent2 == false)
	{
		if(verrinActif2 == true)
		{
			VerinHaut->Set(frc::DoubleSolenoid::Value::kReverse);
			verrinActif2 = false;

		}
		else if(verrinActif2 == false)
		{
			VerinHaut->Set(frc::DoubleSolenoid::Value::kForward);
			verrinActif2 = true;
		}

	boutonPrecedent2 = true;
	}
	else if (boutonPresse2 == false)
	{
		boutonPrecedent2 = false;
	}
}

void Grappin::treuilMonter(double power)
{
	Treuil->Set(power-1);
}

Grappin::~Grappin()
{
	delete VerinHaut;
	delete VerinBas;
	delete Treuil;
}
