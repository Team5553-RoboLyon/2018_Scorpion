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

	Encodeur = new Encoder(6, 7, false, Encoder::EncodingType::k4X);
	Encodeur->Reset();

	fenwick1->Set(0.0);
	fenwick2->Set(0.0);
	fenwick3->Set(0.0);

	consigne = 0;
	tolerance = 25;
}

void Fenwick::setConsigne(int consigneFenwick)
{
	consigne = consigneFenwick;

	if(consigne < 0)
	{
		consigne = 0;
	}
	else if(consigne > 1500/*Valeur a determiner = max */)
	{
		consigne = 1500;/*Valeur a determiner = max*/
	}

	sommeErreurs = 0;
}

void Fenwick::ajuster(int pov)
{
	if(pov == 0)
	{
		this->setConsigne(consigne + 10); /*Valeur a determiner = max*/
	}
	else if(pov == 180)
	{
		this->setConsigne(consigne - 10); /*Valeur a determiner = max*/
	}
}

void Fenwick::monteeFinaleFenwick(/*Pince* pince*/)
{
	//this->setConsigne(600);
	//this->deplacerFenwick();
	//pince->descendreFinMatch();

	this->setConsigne(1500);
	do
	{
	this->deplacerFenwick();
	} while(erreur > 0);
}

void Fenwick::monteeDuRobot()
{
	this->desactiverServo();

	while(Encodeur->Get() > 675)
	{
		std::cout << Encodeur->Get() << std::endl;
		fenwick1->Set(-0.2);
		fenwick2->Set(-0.2);
		fenwick3->Set(-0.2);
	}

	while(Encodeur->Get() > 360)
	{
		std::cout << Encodeur->Get() << std::endl;
		fenwick1->Set(-1);
		fenwick2->Set(-1);
		fenwick3->Set(-1);
	}

	servo->Set(0.6);
	fenwick1->Set(0);
	fenwick2->Set(0);
	fenwick3->Set(0);
}

void Fenwick::deplacerFenwick()
{
		position = Encodeur->Get();
		erreur = (consigne - position);
		if (erreur > tolerance)
		{
			this->desactiverServo();
			fenwick1->Set(0.5);
			fenwick2->Set(0.5);
			fenwick3->Set(0.5);
			std::cout << "Ca monte :  " << position << std::endl;
		}
		else if(erreur < -tolerance)
		{
			this->desactiverServo();
			fenwick1->Set(-0.2);
			fenwick2->Set(-0.2);
			fenwick3->Set(-0.2);
			std::cout << "Ca descend :  " << position << std::endl;
		}
		else
		{
			fenwick1->Set(0);
			fenwick2->Set(0);
			fenwick3->Set(0);
			this->activerServo();
			std::cout << "C'est gagné :  " << position << std::endl;
		}
}


void Fenwick::raz()
{
	this->desactiverServo();
	while(Encodeur->Get() > 10)
	{
		fenwick1->Set(-0.2);
		fenwick2->Set(-0.2);
		fenwick3->Set(-0.2);
	}
	this->activerServo();
}


void Fenwick::deplacerFenwickInfini()
{
	do
	{
		this->deplacerFenwick();
	} while(erreur > tolerance || erreur < -tolerance);
}

void Fenwick::activerServo()
{
	if(etatServo == false)
	{
		std::cout<<"Debut activation du servo"<<std::endl;
		fenwick1->Set(0);
		fenwick2->Set(0);
		fenwick3->Set(0);
		servo->Set(0.075);
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
		fenwick1->Set(0.2);
		fenwick2->Set(0.2);
		fenwick3->Set(0.2);
		}
		while(Encodeur->Get() < a+20);

		fenwick1->Set(0);
		fenwick2->Set(0);
		fenwick3->Set(0);

		servo->Set(0.35);
		etatServo = false;
	}
}

void Fenwick::afficherPosition()
{
	std::cout << "TIC ENCODEUR : " << Encodeur->Get() << std::endl << "DISTANCE PARCOURUE :" << -Encodeur->Get() * 13.6 / 360 << std::endl;
}
Fenwick::~Fenwick()
{
	delete fenwick1;
	delete fenwick2;
	delete fenwick3;
	delete Encodeur;
}

}
