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
#include <Fenwick.h>

namespace std {

Pince::Pince()
{
    incrementationAspiration = dureeAspiration;
    incrementationEjection = dureeEjection;

	Bras = new PWMVictorSPX(7);
	Bras->Set(0);

	Bag = new PWMVictorSPX(8);
	Bag->Set(0);

	AntiRetour = new Servo(9);
	antiRetourEngage = false;
	this->activerServo();

	Switch = new DigitalInput(9);
}

void Pince::attraperCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		Bras->Set(vitesseAspiration);
		incrementationAspiration = 0;
	}
	else if(incrementationAspiration < dureeAspiration)
	{
		Bras->Set(vitesseAspiration);
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

void Pince::descendreDebutMatch()
{
	this->desactiverServo();

	while(Switch->Get() == false)
	{
		Bag->Set(0.2);
	}

	this->activerServo();
}

void Pince::afficherSwitch()
{
	std::cout << "Switch : " << Switch->Get() << std::endl;
}

void Pince::ajuster(int pov)
{
	if(pov == 0)
	{
		this->desactiverServo();
		Bag->Set(-0.6);
	}
	else if(pov == 180 && Switch->Get() == false)
	{
		this->desactiverServo();
		Bag->Set(0.35);
	}
	else
	{
		this->activerServo();
	}
}

void Pince::activerServo()
{
	if(antiRetourEngage == false)
	{
		Bag->Set(0);
		AntiRetour->Set(1);
		antiRetourEngage = true;
	}
}

void Pince::desactiverServo()
{
	if(antiRetourEngage)
	{
		for(int i = 0; i<10000; i++)
		{
			Bag->Set(-0.75);
		}
		AntiRetour->Set(0.6);
		antiRetourEngage = false;
	}
}

Pince::~Pince()
{
	delete Bras;
	delete Bag;
	delete AntiRetour;
	delete Switch;
}

}
