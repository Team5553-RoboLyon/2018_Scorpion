/*
 * Pince.cpp
 *
 *  Created on: 11 févr. 2018
 *      Author: REBAUDET Thomas
 */

#include <iostream>
#include <Pince.h>
#include <Definitions.h>

#include <VictorSP.h>
#include <PWMVictorSPX.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>
#include <DoubleSolenoid.h>

namespace rbl {

Pince::Pince()
{
    incrementationAspiration = dureeAspiration;
    incrementationEjection = dureeEjection;

	consigne = 0;
	sommeErreurs = 0;
	differenceErreurs = 0;
	erreurPrecedente = 0;

	Roues = new PWMVictorSPX(PWM_ROUES);

	Pivot = new PWMVictorSPX(PWM_PIVOT);

	Encodeur = new Encoder(DIO_ENCODEUR_PIVOT_A, DIO_ENCODEUR_PIVOT_B,false, Encoder::EncodingType::k4X);

	Verin = new DoubleSolenoid(PCM_VERIN_PINCE_A, PCM_VERIN_PINCE_B);
}

void Pince::pinceInit()
{
	Verin->Set(frc::DoubleSolenoid::Value::kForward);
	Encodeur->Reset();
}

void Pince::attraperCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		incrementationAspiration = 0;
		Roues->Set(0.5);
	}


	 if (incrementationAspiration == 40)
	{
std::cout<<"gilou Ier"<<std::endl;
		Verin->Set(frc::DoubleSolenoid::Value::kForward);

	}
	if(incrementationAspiration == dureeAspiration)
	{
		Roues->Set(0);
	}
	incrementationAspiration += 1;
}

void Pince::ejecterCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		incrementationEjection = 0;
		Roues->Set(-1);
	}
	else if(incrementationEjection < dureeEjection)
	{
		Roues->Set(-1);
	}
	else if (incrementationEjection == dureeEjection)
	{
		Roues->Set(0);
		incrementinter=0;
		//Verin->Set(frc::DoubleSolenoid::Value::kReverse);

	}
	incrementationEjection += 1;
}

void Pince::pinceIntermediaire()
{
	if(incrementinter ==0)
		Verin->Set(frc::DoubleSolenoid::Value::kReverse);
	else if(incrementinter==2)
		Verin->Set(frc::DoubleSolenoid::Value::kOff);
	incrementinter++;

}

void Pince::afficherPosition()
{
	positionBras = Encodeur->Get();
	std::cout << "Pivot : " << positionBras << std::endl;
}

void Pince::deplacer()
{
	kP = 0.003;
	kI = 0.00000001;
	kD = 0.000001;
	positionBras = Encodeur->Get();

	std::cout << "Bras : " << positionBras << std::endl;

	erreur = consigne - positionBras;
	sommeErreurs += erreur;
	differenceErreurs = erreurPrecedente - erreur;

	vitesse = kP * erreur + kI * sommeErreurs + kD * differenceErreurs;

	Pivot->Set(vitesse);

	erreurPrecedente = erreur;
}

void Pince::goToMilieu()
{
	consigne = 0;
}

void Pince::goToEchangeur(bool avant)
{
	consigne = 650;
	if (!avant)
	{
		consigne = -consigne;
	}
}

void Pince::goToSwitch(bool avant)
{
	consigne = 300;
	if (!avant)
	{
		consigne = -consigne;
	}
}

void Pince::goToScale(bool avant)
{
	consigne = 100;
	if (!avant)
	{
		consigne = -consigne;
	}
}

void Pince::ajuster(int pov)
{
	if(pov == 0)
	{
		consigne += 5;
	}
	else if(pov == 180)
	{
		consigne -= 5;
	}
	std::cout<< consigne <<std::endl;
}

Pince::~Pince()
{
	delete Roues;
	delete Pivot;
	delete Encodeur;
	delete Verin;
}

}
