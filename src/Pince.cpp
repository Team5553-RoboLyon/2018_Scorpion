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
    incrementationAspiration = dureeAspiration+10;
    incrementationEjection = dureeEjection+10;

	consigne = 0;
	sommeErreurs = 0;
	differenceErreurs = 0;
	erreurPrecedente = 0;

	Roues = new PWMVictorSPX(PWM_ROUES);

	Pivot = new PWMVictorSPX(PWM_PIVOT);

	Encodeur = new Encoder(DIO_ENCODEUR_PIVOT_A, DIO_ENCODEUR_PIVOT_B,false, Encoder::EncodingType::k4X);

	Verin = new DoubleSolenoid(PCM_VERIN_PINCE_A, PCM_VERIN_PINCE_B);

}

int Pince::getIncrementAspiration()
{
	return incrementationAspiration;
}

int Pince::getIncrementEjection()
{
	return incrementationEjection;
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
	else if (incrementationAspiration == 15)
	{
		Verin->Set(frc::DoubleSolenoid::Value::kForward);

	}
	else if(incrementationAspiration == dureeAspiration)
	{
		Roues->Set(0);
		verrinActif = true;
	}
	incrementationAspiration += 1;

}

void Pince::attraperCubeAuto(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		incrementationAspiration = 0;
		Roues->Set(0.5);
	}


	 if (incrementationAspiration == 17)
	{
		Verin->Set(frc::DoubleSolenoid::Value::kForward);

	}
	if(incrementationAspiration == dureeAspirationAuto)
	{
		Roues->Set(0);
		verrinActif = true;

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

	else if (incrementationEjection == dureeEjection)
	{
		Roues->Set(0);
		Verin->Set(frc::DoubleSolenoid::Value::kReverse);
	}
	else if(incrementationEjection == (dureeEjection+1))
	{
		//Verin->Set(frc::DoubleSolenoid::Value::kOff);
		verrinActif = false;
	}
		incrementationEjection += 1;
}
void Pince::ejectionSwitch(bool boutonPresse)
{
	if(boutonPresse == true)
		{
			incrementationEjection = 0;
			Roues->Set(-0.65);
		}

		else if (incrementationEjection == dureeEjection)
		{
			Roues->Set(0);
			Verin->Set(frc::DoubleSolenoid::Value::kReverse);
		}
		else if(incrementationEjection == (dureeEjection+1))
		{
			//Verin->Set(frc::DoubleSolenoid::Value::kOff);
			verrinActif = false;
		}
			incrementationEjection += 1;
}

void Pince::positionVerrin(bool boutonPresse)
{
	if(boutonPresse == true && boutonPrecedent == false)
	{
		if(verrinActif == true)
		{
			Verin->Set(frc::DoubleSolenoid::Value::kReverse);
			verrinActif = false;

		}
		else if(verrinActif == false)
		{
			Verin->Set(frc::DoubleSolenoid::Value::kForward);
			verrinActif = true;
		}

	boutonPrecedent = true;
	}
	else if (boutonPresse == false)
	{
		boutonPrecedent = false;
	}
}

int Pince::getPosition()
{
	return Encodeur->Get();
}

void Pince::deplacer()
{
	kP = 0.003;
	kI = 0.00000001;
	kD = 0.000001;
	positionBras = Encodeur->Get();

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
void Pince::test(bool boutonPresse)
{
	if(boutonPresse == true)
	{
		Roues->Set(0.5);
	}
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
		consigne += 12;
	}
	else if(pov == 180)
	{
		consigne -= 12;
	}

	if(consigne > 700)
	{
		consigne = 700;
	}
	else if(consigne < -700)
	{
		consigne = -700;
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
