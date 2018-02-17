/*
 * Pince.cpp
 *
 *  Created on: 11 févr. 2018
 *      Author: REBAUDET Thomas
 */

#include <iostream>
#include <Pince.h>
#include <VictorSP.h>
#include <PWMVictorSPX.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>

namespace std {

Pince::Pince()
{
	Bras = new PWMVictorSPX(7);
	Bras->Set(0);

	Bag = new PWMVictorSPX(8);
	Bag->Set(0);

	AntiRetour = new Servo(9);
	Switch = new DigitalInput(9);
}

void Pince::attraperCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		Bras->Set(-vitesseAspiration);
		incrementationAspiration = 0;
	}
	else if(incrementationAspiration < dureeAspiration)
	{
		Bras->Set(-vitesseAspiration);
	}
	else if (incrementationAspiration == dureeAspiration)
	{
		Bras->Set(0);
	}
	incrementationAspiration += 1;
}

void Pince::ejecterCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		Bras->Set(vitesseEjection);
		incrementationEjection = 0;
	}
	else if(incrementationEjection < dureeEjection)
	{
		Bras->Set(vitesseEjection);
	}
	else if (incrementationEjection == dureeEjection)
	{
		Bras->Set(0);
	}

	incrementationEjection += 1;
}

void Pince::lever()
{

}

void Pince::descendreDebutMatch()
{
	AntiRetour->SetAngle (0);

	while(Switch->Get()==false)
	{
		Bag->Set(-0.2);
	}

	AntiRetour->SetAngle (90);
	Bag->Set (0);
}

void Pince::descendreFinMatch()
{

}

Pince::~Pince()
{
	delete Bras;
	delete Bag;
	delete AntiRetour;
	delete Switch;
}

}
