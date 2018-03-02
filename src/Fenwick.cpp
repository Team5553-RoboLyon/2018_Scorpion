/*
 * Fenwick.cpp
 *
 *  Created on: 10 février 2018
 *      Author: REBAUDET Thomas
 */

#include "Fenwick.h"
#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>
#include <math.h>
#include <iostream>
#include <Pince.h>

#define TOUR 13.6

namespace std
{

Fenwick::Fenwick()
{
	fenwick1 = new VictorSP(0);
	fenwick2 = new VictorSP(1);
	fenwick3 = new VictorSP(2);

	servo = new Servo(6);
	servo->Set(0.35);
	etatServo = false;

	Encodeur = new Encoder(6, 7, false, Encoder::EncodingType::k4X);
	Encodeur->Reset();

	fenwick1->Set(0.0);
	fenwick2->Set(0.0);
	fenwick3->Set(0.0);

	consigne = 0;
	tolerance = 25;
}

void Fenwick::goToZero()
{
	consigne = 0;
	this->deplacer();
}

void Fenwick::goToSwitch()
{
	consigne = 450;
	this->deplacer();
}

void Fenwick::goToScale()
{
	consigne = 1450;
	this->deplacer();
}

void Fenwick::monteeFinaleFenwick()
{
	consigne = 1470;
	this->deplacer();
}

void Fenwick::deplacer()
{
	do
	{
		position = Encodeur->Get();
		erreur = (consigne - position);
		if (erreur > tolerance)
		{
			this->desactiverServo();
			fenwick1->Set(0.65);
			fenwick2->Set(0.65);
			fenwick3->Set(0.65);
			std::cout << "Ca monte :  " << position << std::endl;
		}
		else if(erreur < -tolerance)
		{
			this->desactiverServo();
			fenwick1->Set(-0.3);
			fenwick2->Set(-0.3);
			fenwick3->Set(-0.3);
			std::cout << "Ca descend :  " << position << std::endl;
		}
		else
		{
			this->activerServo();
			std::cout << "C'est gagné :  " << position << std::endl;
		}
	} while(erreur > tolerance || erreur < -tolerance);
}

void Fenwick::monteeDuRobot()
{
	this->desactiverServo();

	while(Encodeur->Get() > 675)
	{
		fenwick1->Set(-0.2);
		fenwick2->Set(-0.2);
		fenwick3->Set(-0.2);
	}

	while(Encodeur->Get() > 360)
	{
		fenwick1->Set(-1);
		fenwick2->Set(-1);
		fenwick3->Set(-1);
	}

	servo->Set(0.73);
	fenwick1->Set(0);
	fenwick2->Set(0);
	fenwick3->Set(0);
}

void Fenwick::activerServo()
{
	if(etatServo == false)
	{
		std::cout<<"Debut activation du servo"<<std::endl;
		fenwick1->Set(0);
		fenwick2->Set(0);
		fenwick3->Set(0);
		servo->Set(0);
		etatServo = true;
	}
}

void Fenwick::desactiverServo()
{
	if(etatServo == true)
	{
		int a = Encodeur->Get();
		std::cout<<"Debut desactivation du servo"<<std::endl;
		do
		{
		fenwick1->Set(0.4);
		fenwick2->Set(0.4);
		fenwick3->Set(0.4);
		}
		while(Encodeur->Get() < a+25);

		fenwick1->Set(0);
		fenwick2->Set(0);
		fenwick3->Set(0);

		servo->Set(0.35);
		etatServo = false;

		std::cout<<"Fin desactivation du servo"<<std::endl;
	}
}

void Fenwick::afficherPosition()
{
	std::cout << "Tic encodeur fenwick : " << Encodeur->Get() << std::endl;
}

Fenwick::~Fenwick()
{
	delete fenwick1;
	delete fenwick2;
	delete fenwick3;
	delete Encodeur;
}

}
