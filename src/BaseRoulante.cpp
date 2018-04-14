/*
 * BaseRoulante.cpp
 *
 *  Created on: 16 févr. 2018
 *      Author: Nathan
 */

#include <BaseRoulante.h>
#include <Definitions.h>
#include "WPILib.h"
#include <Joystick.h>
#include <PWMVictorSPX.h>
#include <Encoder.h>
#include <iostream>

namespace rbl
{

BaseRoulante::BaseRoulante()
{
	BaseDroite1 = new VictorSP(PWM_BASE_DROITE_1);
	BaseDroite2 = new VictorSP(PWM_BASE_DROITE_2);
	BaseGauche1 = new VictorSP(PWM_BASE_GAUCHE_1);
	BaseGauche2 = new VictorSP(PWM_BASE_GAUCHE_2);


	Gyro = new ADXRS450_Gyro();

	Gyro->Calibrate();
	Gyro->Reset();

	EncodeurDroit = new Encoder(DIO_ENCODEUR_DROIT_A, DIO_ENCODEUR_DROIT_B,false, Encoder::EncodingType::k4X);
	EncodeurGauche = new Encoder(DIO_ENCODEUR_GAUCHE_A, DIO_ENCODEUR_GAUCHE_B, false, Encoder::EncodingType::k4X);

	EncodeurDroit->Reset();
	EncodeurGauche->Reset();

	DoubleSolenoid1 = new DoubleSolenoid(PCM_BALLSHIFTER_A, PCM_BALLSHIFTER_B);

}

void BaseRoulante::baseInit()
{
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);
	BaseGauche1->Set(0);
	BaseGauche2->Set(0);

	DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kReverse);

	vitesseBallShifter = false;
	std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;
	etatPrecedentGachette = false;
}

void BaseRoulante::arreter()
{
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);
	BaseGauche1->Set(0);
	BaseGauche2->Set(0);
}

void BaseRoulante::deplacer(Joystick* joystick)
{
	y = joystick->GetY();
	z = joystick->GetZ();

	if (y < 0.2 && y > -0.2)
	{
		y = 0;
	}
	if (z < 0.2 && z > -0.2)
	{
		z = 0;
	}

	vitesseGauche = y - 0.5 * z;
	vitesseDroite = -y - 0.5 * z;

	BaseDroite1->Set(vitesseDroite);
	BaseDroite2->Set(vitesseDroite);
	BaseGauche1->Set(vitesseGauche);
	BaseGauche2->Set(vitesseGauche);
}

void BaseRoulante::changerVitesse(bool etatGachette)
{
	if(etatGachette && !etatPrecedentGachette) //Si la gachette est appuyée et qu'elle ne l'etait pas avant
	{
		if (vitesseBallShifter)
		{
			DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kReverse);
			std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;
			vitesseBallShifter = false;
		}
		else
		{
			DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);
			std::cout << "*************** VITESSE 2 ACTIVEE ***************" << std::endl;
			vitesseBallShifter = true;
		}

		etatPrecedentGachette = true;
	}
	else if (!etatGachette) //Si la gachette n'est pas appuyée
	{
		etatPrecedentGachette = false;
	}
}

double BaseRoulante::parcourir_distance(int distance_a_parcourir)
{
	kP = 0.01;
	kI = 0.0000003;
	kD = 0.0000035;
	distanceParcourueDroite = EncodeurDroit->Get() * r * 2 * M_PI / 360;

	std::cout << "Droite : " << distanceParcourueDroite << std::endl;

	erreurDroite = distance_a_parcourir - distanceParcourueDroite;
	sommeErreursDroite += erreurDroite;
	differenceErreursDroite = erreurPrecedenteDroite - erreurDroite;

	vitesseDroite = kP * erreurDroite + kI * sommeErreursDroite + kD * differenceErreursDroite;

	BaseGauche1->Set(-vitesseDroite);//-vitesseGauche);
	BaseGauche2->Set(-vitesseDroite);//-vitesseGauche);
	BaseDroite1->Set(vitesseDroite);
	BaseDroite2->Set(vitesseDroite);

	erreurPrecedenteDroite = erreurDroite;

	return erreurPrecedenteDroite; // Erreur en cm
}

double BaseRoulante::rotation(const int angle_consigne)
{
	kP = 0.065;
	kI = 0.000093;
	kD = 0.3;

	angleParcouru = Gyro->GetAngle();

	std::cout << "angleParcouru : " << angleParcouru << std::endl;

	erreur = angle_consigne - angleParcouru;

	sommeErreurs += erreur;

	differenceErreurs = erreur - erreurPrecedente;

	vitesseDroite = kP * erreur + kI * sommeErreurs + kD * differenceErreurs;
	vitesseGauche = kP * erreur + kI * sommeErreurs + kD * differenceErreurs;

	BaseGauche1->Set(-vitesseGauche);
	BaseGauche2->Set(-vitesseGauche);
	BaseDroite1->Set(-vitesseDroite);
	BaseDroite2->Set(-vitesseDroite);

	erreurPrecedente = erreur;

	return erreur; // Erreur en degrés
}

void BaseRoulante::resetPID()
{
	EncodeurDroit->Reset();
	EncodeurGauche->Reset();

	Gyro->Reset();

	erreurPrecedente = 0;
	sommeErreurs = 0;

	erreurPrecedenteDroite = 0;
	erreurPrecedenteGauche = 0;
	sommeErreursDroite = 0;
	sommeErreursGauche = 0;
}

void BaseRoulante::afficherCodeuses()
{
	std::cout << "Droit :  en tic-> " << EncodeurDroit->Get() << "      en cm-> " << EncodeurDroit->Get()* r * 2 * M_PI / 360 << std::endl;
	std::cout << "Gauche :  en tic-> " << EncodeurGauche->Get() << "      en cm-> " << EncodeurGauche->Get()* r * 2 * M_PI / 360 << std::endl;
}

void BaseRoulante::afficherGyro()
{
	std::cout << "Angle : " << Gyro->GetAngle() << std::endl;
}


BaseRoulante::~BaseRoulante()
{
	delete BaseDroite1;
	delete BaseDroite2;
	delete BaseGauche1;
	delete BaseGauche2;
	delete EncodeurDroit;
	delete EncodeurGauche;
	delete Gyro;
}

}
