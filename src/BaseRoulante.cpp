/*
 * BaseRoulante.cpp
 *
 *  Created on: 16 févr. 2018
 *      Author: Nathan
 */

#include <BaseRoulante.h>
#include "WPILib.h"
#include <Joystick.h>
#include <PWMVictorSPX.h>
#include <Encoder.h>
#include <iostream>

namespace std
{

BaseRoulante::BaseRoulante()
{
	BaseDroite1 = new PWMVictorSPX(3);
	BaseDroite2 = new PWMVictorSPX(4);
	BaseGauche = new PWMVictorSPX(5);

	BaseGauche->Set(0);
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);

	Gyro = new ADXRS450_Gyro();
	Gyro->Calibrate();
	Gyro->Reset();

	EncodeurDroit = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	EncodeurDroit->Reset();
	EncodeurDroit->SetReverseDirection(false);

	EncodeurGauche = new Encoder(2, 3, false, Encoder::EncodingType::k4X);
	EncodeurGauche->Reset();
	EncodeurGauche->SetReverseDirection(true);

	DoubleSolenoid1 = new DoubleSolenoid(2, 3);
	DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);

	vitesseBallShifter = false;
	std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;
	etatPrecedentGachette = false;
}

void BaseRoulante::arreter()
{
	BaseGauche->Set(0);
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);
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

	BaseGauche->Set(vitesseGauche);
	BaseDroite1->Set(vitesseDroite);
	BaseDroite2->Set(vitesseDroite);
}

void BaseRoulante::afficherCodeuses()
{
	std::cout << "Droit : " << EncodeurDroit->Get() << std::endl;
	std::cout << "Gauche : " << EncodeurGauche->Get() << std::endl;
}

void BaseRoulante::parcourir_distance(int distance_a_parcourir)
{
	r = 7.62;
	kP = 1;
	kI = 0;
	kD = 0;
	tolerance = 20;

	EncodeurGauche->Reset();
	EncodeurDroit->Reset();

	erreurPrecedenteDroite = distance_a_parcourir;
	erreurPrecedenteGauche = distance_a_parcourir;
	sommeErreursDroite = 0;
	sommeErreursGauche = 0;

	do
	{
		distanceParcourueDroite = EncodeurDroit->Get() * r * 2 * M_PI / 360;
		distanceParcourueGauche = EncodeurGauche->Get() * r * 2 * M_PI / 360;

		std::cout << "Droite : " << distanceParcourueDroite << std::endl;
		std::cout << "Gauche : " << distanceParcourueGauche << std::endl;

		erreurDroite = (distance_a_parcourir - distanceParcourueDroite) / distance_a_parcourir;
		erreurGauche = (distance_a_parcourir - distanceParcourueGauche) / distance_a_parcourir;

		sommeErreursDroite += erreurDroite;
		sommeErreursGauche += erreurGauche;

		diferenceErreursDroite = erreurPrecedenteDroite - erreurDroite;
		diferenceErreursGauche = erreurPrecedenteGauche - erreurGauche;

		vitesseDroite = kP * erreurDroite + kI * sommeErreursDroite + kD * diferenceErreursDroite;
		vitesseGauche = kP * erreurGauche + kI * sommeErreursGauche + kD * diferenceErreursGauche;

		BaseGauche->Set(-vitesseGauche);
		BaseDroite1->Set(vitesseDroite);
		BaseDroite2->Set(vitesseDroite);

		erreurPrecedenteDroite = erreurDroite;
		erreurPrecedenteGauche = erreurGauche;
	} while (true);
}

void BaseRoulante::changerVitesse(bool etatGachette)
{
	if(etatGachette && !etatPrecedentGachette) //Si la gachette est appuyée et qu'elle ne l'etait pas avant
	{
		if (vitesseBallShifter)
		{
			DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);
			std::cout << "*************** VITESSE 1 ACTIVEE ***************" << std::endl;
			vitesseBallShifter = false;
		}
		else
		{
			DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kReverse);
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

void BaseRoulante::rotation(int angle_consigne)
{
	kP = 1;
	kI = 0;
	kD = 0;
	tolerance = 20;

	erreurPrecedente = angle_consigne;
	sommeErreurs = 0;

	Gyro->Reset();

	do
	{
		angleParcouru = Gyro->GetAngle();

		erreur = (angle_consigne - angleParcouru) / angle_consigne;

		sommeErreurs += erreur;

		diferenceErreurs = erreur - erreurPrecedente;

		vitesseDroite = kP * erreur + kI * sommeErreurs + kD * diferenceErreurs;
		vitesseGauche = kP * erreur + kI * sommeErreurs + kD * diferenceErreurs;

		BaseGauche->Set(vitesseGauche);
		BaseDroite1->Set(vitesseDroite);
		BaseDroite2->Set(vitesseDroite);

		erreurPrecedente = erreur;
	} while (true);
}

BaseRoulante::~BaseRoulante()
{
	delete BaseDroite1;
	delete BaseDroite2;
	delete BaseGauche;
	delete EncodeurDroit;
	delete EncodeurGauche;
	delete Gyro;
}

}
