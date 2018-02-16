/*
 * Base.h
 *
<<<<<<< HEAD
 *  Created on: 15 févr. 2018
 *      Author: Nathan
=======
 *  Created on: 16 févr. 2018
 *      Author: REBAUDET Thomas
>>>>>>> 9e54e3a4a256accd3241fad6e7ce5c9936fba988
 */

#ifndef SRC_BASE_H_
#define SRC_BASE_H_
<<<<<<< HEAD
#include "WPILib.h"
#include <PWMVictorSPX.h>
#include <VictorSP.h>
#include <Encoder.h>

namespace std
{

class Base
{
public:
	Base();
	virtual ~Base();

	void rouler(double vitesseDroite, double vitesseGauche);
	void parcourir_distance(int distance_a_parcourir);
	void rotation(int angle_consigne);

private:
	PWMVictorSPX* BaseDroite1;
	PWMVictorSPX* BaseDroite2;
	PWMVictorSPX* BaseGauche;

	Encoder* EncodeurDroit;
	Encoder* EncodeurGauche;

	ADXRS450_Gyro* Gyro;

	double distance_parcourue, angle_parcouru, erreur, erreurPrecedente, vitesse;
	double proportionelle, integrale, derivee;
	double tolerance, kP, kI, KD;

};

}
=======
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
>>>>>>> 9e54e3a4a256accd3241fad6e7ce5c9936fba988

#endif /* SRC_BASE_H_ */
