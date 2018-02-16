/*
 * Base.cpp
 *
 *  Created on: 15 févr. 2018
 *      Author: Nathan
 */

#include <Base.h>
#include "WPILib.h"
#include <PWMVictorSPX.h>
#include <VictorSP.h>
#include <Encoder.h>

namespace std
{

Base::Base()
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

	EncodeurDroit = new Encoder (0,1, false, Encoder::EncodingType::k4X);
	EncodeurDroit->Reset();
	EncodeurDroit->SetReverseDirection(false);

	EncodeurGauche = new Encoder (2,3, false, Encoder::EncodingType::k4X);
	EncodeurGauche->Reset();
	EncodeurGauche->SetReverseDirection(true);
}

Base::~Base()
{
	BaseDroite1 delete;
	BaseDroite2 delete;
	BaseGauche delete;
	EncodeurDroit delete;
	EncodeurGauche delete;
	Gyro delete;
}

void Base::parcourir_distance(int distance_a_parcourir) //distance_a_parcourir en cm
{
	kP = 2;
	kI = 0;
	kD = 0;
	tolerance = 20;

	erreurPrecedente = distance_a_parcourir;
	integrale = 0;

	EncodeurGauche->Reset();
	EncodeurDroit->Reset();

	do
	{
		distance_parcourue = ((EncodeurDroit->Get() + EncodeurGauche->Get()) /2) /7.5;
		erreur = (distance_a_parcourir - distance_parcourue) / distance_a_parcourir;

		proportionelle = kP * erreur;

		integrale += erreur;
		integrale = kI * integrale;

		derivee = kD * (erreur - erreurPrecedente);
		erreurPrecedente = erreur;

		vitesse = proportionelle + integrale + derivee;

		BaseGauche->Set(-vitesse);
		BaseDroite1->Set(vitesse);
		BaseDroite2->Set(vitesse);
	}
	while(erreur > tolerance || erreur < -tolerance);
}


void Base::rotation(int angle_consigne) //angle degres
{
	kP = 1;
	kI = 0;
	kD = 0;
	tolerance = 20;

	erreurPrecedente = angle_consigne;
	integrale = 0;

	Gyro->Reset();

	do
	{
	angle_parcouru = Gyro->GetAngle();
	erreur = (angle_consigne - angle_parcouru) / angle_consigne;

	proportionelle = kP * erreur;

	integrale += erreur;
	integrale = kI * integrale;

	derivee = kD * (erreur - erreurPrecedente);
	erreurPrecedente = erreur;

	vitesse = proportionelle + integrale + derivee;

	BaseGauche->Set(-vitesse);
	BaseDroite1->Set(-vitesse);
	BaseDroite2->Set(-vitesse);
	}
	while(true);//(erreur > tolerance || erreur < -tolerance);
}

}
