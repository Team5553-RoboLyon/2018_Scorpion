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
	this->setConsigne(600);
	this->deplacerFenwick();

	//pince->descendreFinMatch();

	this->setConsigne(1500);
	this->deplacerFenwick();
}

void Fenwick::monteeDuRobot()
{
	while(Encodeur->Get() > 600)
	{
		fenwick1->Set(-0.5);
		fenwick2->Set(-0.5);
		fenwick3->Set(-0.5);
	}

	servo->Set(0.6);
	fenwick1->Set(0);
	fenwick2->Set(0);
	fenwick3->Set(0);
}

void Fenwick::deplacerFenwick()
{
//	this->desactiverServo();
//
//	do
//	{
//	position = Encodeur->Get();
//	erreur = (consigne - position) / consigne;
//	sommeErreurs += erreur;
//	differenceErreurs = erreurPrecedente - erreur;
//
//	puissanceMoteur = (kP * erreur);/*+ kI * sommeAllErreurs + kD * differenceErreurs);*/
//	fenwick1->Set(puissanceMoteur);
//	fenwick2->Set(puissanceMoteur);
//	fenwick3->Set(puissanceMoteur);
//	erreurPrecedente = erreur;
//
//	std::cout << "Puissance : " << puissanceMoteur << std::endl;
//	std::cout << "Position : " << position << std::endl;
//	}
//	while(erreur > 0);
//
//	this->activerServo();
	position = Encodeur->Get();
	erreur = (consigne - position);
	if (erreur > tolerance)
	{
		this->desactiverServo();
		fenwick1->Set(0.85);
		fenwick2->Set(0.85);
		fenwick3->Set(0.85);
		std::cout << "Ca monte :  " << position << std::endl;
	}
	else if(erreur < -tolerance )
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

void Fenwick::activerServo()
{
	fenwick1->Set(0);
	fenwick2->Set(0);
	fenwick3->Set(0);
	servo->Set(0.075);
}

void Fenwick::desactiverServo()
{
	int a = Encodeur->Get();
	std::cout<<"Debut desactivation du servo"<<std::endl;
	do
	{
	fenwick1->Set(0.3);
	fenwick2->Set(0.3);
	fenwick3->Set(0.3);

	}
	while(Encodeur->Get() < a+20);

	fenwick1->Set(0);
	fenwick2->Set(0);
	fenwick3->Set(0);

	servo->Set(0.35);
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
