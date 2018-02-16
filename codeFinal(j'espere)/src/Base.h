/*
 * Base.h
 *
 *  Created on: 15 févr. 2018
 *      Author: Nathan
 */

#ifndef SRC_BASE_H_
#define SRC_BASE_H_
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

#endif /* SRC_BASE_H_ */
