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
#include <Timer.h>

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

	timer = new Timer();


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

void BaseRoulante::parcourir_distance(int distance_a_parcourir)
{
	/*timer->Reset();
	timer->Start();
	kP = 0.5;
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
		//distanceParcourueGauche = EncodeurGauche->Get() * r * 2 * M_PI / 360;

		std::cout << "Droite : " << distanceParcourueDroite << std::endl;
		//std::cout << "Gauche : " << distanceParcourueGauche << std::endl;

		erreurDroite = (distance_a_parcourir - distanceParcourueDroite) / abs(distance_a_parcourir);
		//erreurGauche = (distance_a_parcourir - distanceParcourueGauche) / abs(distance_a_parcourir);

		sommeErreursDroite += erreurDroite;
		//sommeErreursGauche += erreurGauche;

		differenceErreursDroite = erreurPrecedenteDroite - erreurDroite;
		//differenceErreursGauche = erreurPrecedenteGauche - erreurGauche;

		vitesseDroite = kP * erreurDroite + kI * sommeErreursDroite + kD * differenceErreursDroite;
		//vitesseGauche = kP * erreurGauche + kI * sommeErreursGauche + kD * differenceErreursGauche;

		BaseGauche->Set(-vitesseDroite);//-vitesseGauche);
		BaseDroite1->Set(vitesseDroite);
		BaseDroite2->Set(vitesseDroite);

		erreurPrecedenteDroite = erreurDroite;
		erreurPrecedenteGauche = erreurGauche;

		erreurMoyenne = erreurDroite * abs(distance_a_parcourir); //(erreurDroite + erreurGauche) * abs(distance_a_parcourir) / 2;
	} while (erreurMoyenne > tolerance || erreurMoyenne < -tolerance || timer->Get() < 4);

	BaseGauche->Set(0);
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);*/

	kP = 0.75;
	kI = 0;
	kD = 0;
	tolerance = 20;

	distanceParcourueDroite = EncodeurDroit->Get() * r * 2 * M_PI / 360;

	std::cout << "Droite : " << distanceParcourueDroite << std::endl;

	erreurDroite = (distance_a_parcourir - distanceParcourueDroite) / abs(distance_a_parcourir);
	sommeErreursDroite += erreurDroite;
	differenceErreursDroite = erreurPrecedenteDroite - erreurDroite;

	vitesseDroite = kP * erreurDroite + kI * sommeErreursDroite + kD * differenceErreursDroite;

	BaseGauche->Set(-vitesseDroite);//-vitesseGauche);
	BaseDroite1->Set(vitesseDroite);
	BaseDroite2->Set(vitesseDroite);

	erreurPrecedenteDroite = erreurDroite;
}

void BaseRoulante::rotation(int angle_consigne)
{
	timer->Reset();
	timer->Start();
	kP = 0.85;
	kI = 0.0001;
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
	} while (erreur*abs(angle_consigne) > tolerance || erreur*abs(angle_consigne) < -tolerance || timer->Get() < 3);

	BaseGauche->Set(0);
	BaseDroite1->Set(0);
	BaseDroite2->Set(0);
}

void BaseRoulante::resetPID()
{
	EncodeurDroit->Reset();
	EncodeurGauche->Reset();

	erreurPrecedenteDroite = distance_a_parcourir;
	erreurPrecedenteGauche = distance_a_parcourir;
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
	delete BaseGauche;
	delete EncodeurDroit;
	delete EncodeurGauche;
	delete Gyro;
}

}
