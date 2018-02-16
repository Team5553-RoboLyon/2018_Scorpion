/*
 * Base.h
 *
 *  Created on: 16 févr. 2018
 *      Author: REBAUDET Thomas
 */

#ifndef SRC_BASE_H_
#define SRC_BASE_H_
#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>
#include <math.h>
#include <iostream>


namespace std {

class Base {
public:
	Base();
	void Deplacer(Joystick* joystick);
	void AfficherCodeuses();
	void AvancerDistance(double consigne);
virtual ~Base();
private:
	VictorSP* problemePsychoMoteurDroit1;
	VictorSP* problemePsychoMoteurDroit2;
	VictorSP* problemePsychoMoteurGauche1;
	Encoder* anCo2z1;
	Encoder* anCo2z2;
	double y,z,vitesseDroite, vitesseGauche;

	double consigne/*en cm*/, positionDroite, positionGauche/*en cm*/, erreurDroite, erreurGauche;
	double r = 7.62; //rayon en cm
	double P = 0.020;
	double I = 0;
	double D = 0;

	double differenceErreursDroite = 0;
	double differenceErreursGauche = 0;
	double puissanceMoteurDroite = 0;
	double puissanceMoteurGauche = 0;
	double erreurPrecedenteDroite, erreurPrecedenteGauche;
	double sommeAllErreursDroite = 0;
	double sommeAllErreursGauche = 0;
};

} /* namespace std */

#endif /* SRC_BASE_H_ */
