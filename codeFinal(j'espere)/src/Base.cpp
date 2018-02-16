/*
 * Base.cpp
 *
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
