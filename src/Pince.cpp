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
#include <Fenwick.h>

namespace std {

Pince::Pince()
{
	Bras = new VictorSP(7);
	Bras->Set(0);

	Bag = new VictorSP(8);
	Bag->Set(0);

	AntiRetour = new Servo(9);
	AntiRetour->Set(0.99);
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
		Bras->Set(-vitesseEjection);
		incrementationEjection = 0;
	}
	else if(incrementationEjection < dureeEjection)
	{
		Bras->Set(-vitesseEjection);
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

	while(Switch->Get() == false)
	{
		//Bag->Set(-0.2);
	}

	AntiRetour->SetAngle (90);
	Bag->Set (0);
}

void Pince::descendreFinMatch()
{
	AntiRetour->SetAngle (0);

	while(Switch->Get() == false)
	{
		Bag->Set(-0.2);
	}

	AntiRetour->SetAngle (90);
	Bag->Set (0);
}

void Pince::afficherSwitch()
{
	std::cout << "Switch : " << Switch->Get() << std::endl;
}

void Pince::ajuster(int pov)
{
	if(pov == 0)
	{
		if(antiRetourEngage)
		{
			for(int i = 0; i<100; i++)
			{
				Bag->Set(-0.2);
			}
			AntiRetour->Set(0);
			antiRetourEngage = false;
		}
		Bag->Set(-0.2);
	}
	else if(pov == 180)
	{
		if(antiRetourEngage)
		{
			for(int i = 0; i<100; i++)
			{
				Bag->Set(-0.2);
			}
			AntiRetour->Set(0);
			antiRetourEngage = false;
		}
		Bag->Set(0.2);
	}
	else
	{
		AntiRetour->Set(0.99);
		antiRetourEngage = true;
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
