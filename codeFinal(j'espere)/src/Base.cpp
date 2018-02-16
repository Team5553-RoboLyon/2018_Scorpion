/*
 * Base.cpp
 *
<<<<<<< HEAD
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
=======
 *  Created on: 16 févr. 2018
 *      Author: REBAUDET Thomas
 */

#include "Base.h"
#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>
#include <math.h>
#include <iostream>

namespace std {

Base::Base() {
	problemePsychoMoteurDroit1 = new VictorSP(3);
	problemePsychoMoteurDroit2 = new VictorSP(4);
	problemePsychoMoteurGauche1 = new VictorSP(5);
	anCo2z1 = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	anCo2z2 = new Encoder(2, 3, false, Encoder::EncodingType::k4X);

	anCo2z1->Reset();
	anCo2z2->Reset();

	problemePsychoMoteurDroit1->Set(0.0);
	problemePsychoMoteurDroit2->Set(0.0);
	problemePsychoMoteurGauche1->Set(0.0);

}

void Base::Deplacer(Joystick* joystick){

	y = joystick->GetY();
			z = joystick->GetZ();

			if (y<=0.2 && y>=-0.2)
				y=0;

			if (z<=0.05 && z>=-0.05 )
				z=0;

			vitesseDroite = -y - 0.5 * z;
			vitesseGauche = y - 0.5 * z;

			problemePsychoMoteurDroit1->Set(vitesseDroite);
			problemePsychoMoteurDroit2->Set(vitesseDroite);
			problemePsychoMoteurGauche1->Set(vitesseGauche);

}

void Base::AfficherCodeuses(){
	std::cout << "Encodeur droit : " << anCo2z1->Get() << std::endl;
	std::cout << "Encodeur gauche : " << anCo2z2->Get() << std::endl;
}

void Base::AvancerDistance (double consigne){

	positionDroite = -(anCo2z1->Get()* r* 2*M_PI/360);
	positionGauche = anCo2z2->Get()* r* 2*M_PI/360;
	erreurDroite = consigne-positionDroite;
	erreurGauche = consigne - positionGauche;
	sommeAllErreursDroite += erreurDroite;
	sommeAllErreursGauche += erreurGauche;
	differenceErreursDroite = erreurPrecedenteDroite - erreurDroite;
	differenceErreursGauche = erreurPrecedenteGauche - erreurGauche;
	puissanceMoteurDroite= -(P * erreurDroite/*+ I * sommeAllErreursDroite + D * differenceErreursDroite*/);
	puissanceMoteurGauche= (P * erreurGauche/*+ I * sommeAllErreursGauche + D * differenceErreursGauche*/);
	problemePsychoMoteurDroit1->Set(-puissanceMoteurDroite);
	problemePsychoMoteurDroit2->Set(-puissanceMoteurDroite);
	problemePsychoMoteurGauche1->Set(-puissanceMoteurGauche);
	erreurPrecedenteDroite = erreurDroite;
	erreurPrecedenteGauche = erreurGauche;
}
Base::~Base() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
>>>>>>> 9e54e3a4a256accd3241fad6e7ce5c9936fba988
