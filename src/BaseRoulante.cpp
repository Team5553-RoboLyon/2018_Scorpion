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
	BaseDroite1 = new VictorSP(3);
	BaseDroite2 = new VictorSP(4);
	BaseGauche = new VictorSP(5);

	BaseGauche->Set(0);
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);

	Gyro = new ADXRS450_Gyro();
	Gyro->Calibrate();
	Gyro->Reset();

	EncodeurDroit = new Encoder(2, 3,false, Encoder::EncodingType::k4X);
	EncodeurDroit->Reset();

	EncodeurGauche = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	EncodeurGauche->Reset();

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

void BaseRoulante::afficherGyro()
{
	std::cout << "Angle : " << Gyro->GetAngle() << std::endl;
}

void BaseRoulante::parcourir_distance(int distance_a_parcourir)
{
	r = 7.62;
	kP = 0.75;
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

		erreurDroite = (distance_a_parcourir - distanceParcourueDroite) / abs(distance_a_parcourir);
		erreurGauche = (distance_a_parcourir - distanceParcourueGauche) / abs(distance_a_parcourir);

		sommeErreursDroite += erreurDroite;
		sommeErreursGauche += erreurGauche;

		differenceErreursDroite = erreurPrecedenteDroite - erreurDroite;
		differenceErreursGauche = erreurPrecedenteGauche - erreurGauche;

		vitesseDroite = kP * erreurDroite + kI * sommeErreursDroite + kD * differenceErreursDroite;
		vitesseGauche = kP * erreurGauche + kI * sommeErreursGauche + kD * differenceErreursGauche;

		BaseGauche->Set(-vitesseGauche);
		BaseDroite1->Set(vitesseDroite);
		BaseDroite2->Set(vitesseDroite);

		erreurPrecedenteDroite = erreurDroite;
		erreurPrecedenteGauche = erreurGauche;

	} while (erreurDroite*abs(distance_a_parcourir) > tolerance || erreurDroite*abs(distance_a_parcourir) < -tolerance);
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
	kP = 0.5;
	kI = 0;
	kD = 0;
	tolerance = 20;

	erreurPrecedente = angle_consigne;
	sommeErreurs = 0;

	Gyro->Reset();

	do
	{
		angleParcouru = Gyro->GetAngle();

		std::cout << "angleParcouru : " << angleParcouru << std::endl;

		erreur = (angle_consigne - angleParcouru) / abs(angle_consigne);

		sommeErreurs += erreur;

		differenceErreurs = erreur - erreurPrecedente;

		vitesseDroite = kP * erreur + kI * sommeErreurs + kD * differenceErreurs;
		vitesseGauche = kP * erreur + kI * sommeErreurs + kD * differenceErreurs;

		BaseGauche->Set(-vitesseGauche);
		BaseDroite1->Set(-vitesseDroite);
		BaseDroite2->Set(-vitesseDroite);

		erreurPrecedente = erreur;
	} while (erreur*abs(angle_consigne) > tolerance || erreur*abs(angle_consigne) < -tolerance);
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
