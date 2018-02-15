/*
 * Pince.cpp
 *
 *  Created on: 11 f�vr. 2018
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

	AntiRetour = new Servo(10);
	Switch = new DigitalInput(9);
}

void Pince::attraperCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		Bras->Set(-vitesserotation);
		incrementationAspiration = 0;
	}
	else if(incrementationAspiration < dureeAspiration)
	{
		Bras->Set(-vitesserotation);
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
		Bras->Set(vitesserotation);
		incrementationEjection = 0;
	}
	else if(incrementationEjection < dureeEjection)
	{
		Bras->Set(vitesserotation);
	}
	else if (incrementationEjection == dureeEjection)
	{
		Bras->Set(0);
	}

	incrementationEjection += 1;
}

void Pince::leverPince()
{

}

void Pince::descendrePinceDebutMatch()
{
	AntiRetour->SetAngle (0);

	while(Switch->Get()==false)
	{
		Bag->Set(-0.2);
	}

	AntiRetour->SetAngle (90);
	Bag->Set (0);
}

void Pince::descendrePinceFinMatch()
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
