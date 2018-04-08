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
#include <Fenwick.h>

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
	Roues->Set(0);

	Pivot = new PWMVictorSPX(PWM_PIVOT);
	Pivot->Set(0);

	Encodeur = new Encoder(DIO_ENCODEUR_PIVOT_A, DIO_ENCODEUR_PIVOT_B,false, Encoder::EncodingType::k4X);
	Encodeur->Reset();

	Verin = new DoubleSolenoid(PCM_VERIN_PINCE_A, PCM_VERIN_PINCE_B);
	Verin->Set(frc::DoubleSolenoid::Value::kForward);
}

void Pince::attraperCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		incrementationAspiration = 0;
	}
	else if(incrementationAspiration < dureeAspiration)
	{
		Roues->Set(0.5);
	}
	else if (incrementationAspiration == dureeAspiration)
	{
		Roues->Set(0);
		Verin->Set(frc::DoubleSolenoid::Value::kReverse);
	}
	incrementationAspiration += 1;
}

void Pince::ejecterCube(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		incrementationEjection = 0;
	}
	else if(incrementationEjection < dureeEjection)
	{
		Roues->Set(0.5);
	}
	else if (incrementationEjection == dureeEjection)
	{
		Roues->Set(0);
		Verin->Set(frc::DoubleSolenoid::Value::kForward);

	}
	incrementationEjection += 1;
}

void Pince::deplacer()
{
	kP = 0;
	kI = 0;
	kD = 0;
	positionBras = Encodeur->Get();

	std::cout << "Bras : " << positionBras << std::endl;

	erreur = consigne - positionBras;
	sommeErreurs += erreur;
	differenceErreurs = erreurPrecedente - erreur;

	vitesse = kP * erreur + kI * sommeErreurs + kD * differenceErreurs;

	Pivot->Set(vitesse);

	erreurPrecedente = erreur;
}

void Pince::goToZero(bool avant)
{
	consigne = 0;
	if (!avant)
	{
		consigne = -consigne;
	}
}

void Pince::goToSwitch(bool avant)
{
	consigne = 0;
	if (!avant)
	{
		consigne = -consigne;
	}
}

void Pince::goToScale(bool avant)
{
	consigne = 0;
	if (!avant)
	{
		consigne = -consigne;
	}
}

void Pince::ajuster(int pov)
{
	if(pov == 0)
	{
		consigne += 0;
	}
	else if(pov == 180)
	{
		consigne -= 0;
	}
}

Pince::~Pince()
{
	delete Roues;
	delete Pivot;
	delete Encodeur;
	delete Verin;
}

}
