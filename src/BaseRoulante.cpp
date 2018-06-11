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

	kPAvancer = 0.02;
	kIAvancer = 0.0000045;
	kDAvancer = 0.05;

	kPRotation = 0.075; //0.050 pour cotés et 0.075 pour milieu
	kIRotation = 0.00003;
	kDRotation = 0.28;
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
			//SmartDashboard::PutNumber("Vitesse", 1);
			vitesseBallShifter = false;
		}
		else
		{
			DoubleSolenoid1->Set(frc::DoubleSolenoid::Value::kForward);
			std::cout << "*************** VITESSE 2 ACTIVEE ***************" << std::endl;
			//SmartDashboard::PutNumber("Vitesse", 2);
			vitesseBallShifter = true;
		}

		etatPrecedentGachette = true;
	}
	else if (!etatGachette) //Si la gachette n'est pas appuyées
	{
		etatPrecedentGachette = false;
	}
}

double BaseRoulante::parcourir_distance(int distance_a_parcourir)
{
	distanceParcourueDroite = -(EncodeurDroit->Get() * r * 2 * M_PI / 263); //360 ou 22

	std::cout << "Droite : " << distanceParcourueDroite << std::endl;

	erreurDroite = distance_a_parcourir - distanceParcourueDroite;
	sommeErreursDroite += erreurDroite;
	differenceErreursDroite = erreurDroite - erreurPrecedenteDroite;

	vitesseDroite = kPAvancer * erreurDroite + kIAvancer * sommeErreursDroite + kDAvancer * differenceErreursDroite;

	std::cout << kPAvancer * erreurDroite << "     " << kIAvancer * sommeErreursDroite << "     " << kDAvancer * differenceErreursDroite << std::endl;

	int angle = Gyro->GetAngle() /10;

	BaseGauche1->Set(-vitesseDroite);// + angle);//-vitesseGauche);
	BaseGauche2->Set(-vitesseDroite);// + angle);//-vitesseGauche);
	BaseDroite1->Set(vitesseDroite);// - angle);
	BaseDroite2->Set(vitesseDroite);// - angle);

	erreurPrecedenteDroite = erreurDroite;

	return erreurPrecedenteDroite; // Erreur en cm
}

double BaseRoulante::rotation(const int angle_consigne)
{
	angleParcouru = Gyro->GetAngle();

	std::cout << "angleParcouru : " << angleParcouru << std::endl;

	erreur = angle_consigne - angleParcouru;

	sommeErreurs += erreur;

	differenceErreurs = erreur - erreurPrecedente;

	vitesseDroite = kPRotation * erreur + kIRotation * sommeErreurs + kDRotation * differenceErreurs;
	vitesseGauche = kPRotation * erreur + kIRotation * sommeErreurs + kDRotation * differenceErreurs;

	std::cout << kPRotation * erreur << "     " << kIRotation * sommeErreurs << "     " << kDRotation * differenceErreurs << std::endl;

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
	std::cout << "Droit :  en tic-> " << EncodeurDroit->Get() << "      en cm-> " << EncodeurDroit->Get()* r * 2 * M_PI / 263 << std::endl;
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
