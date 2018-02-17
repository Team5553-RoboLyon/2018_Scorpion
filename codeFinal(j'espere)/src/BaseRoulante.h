/*
 * BaseRoulante.h
 *
 *  Created on: 16 févr. 2018
 *      Author: Nathan
 */

#ifndef SRC_BASEROULANTE_H_
#define SRC_BASEROULANTE_H_
#include "WPILib.h"
#include <Joystick.h>
#include <PWMVictorSPX.h>
#include <Encoder.h>
#include <iostream>

namespace std
{

class BaseRoulante
{
public:
	BaseRoulante();

	void deplacer(Joystick* joystick);
	void afficherCodeuses();
	void changerVitesse();
	void afficherPosition();
	void parcourir_distance(int distance_a_parcourir);
	void rotation(int angle_consigne);

	virtual ~BaseRoulante();

private:
	PWMVictorSPX* BaseDroite1;
	PWMVictorSPX* BaseDroite2;
	PWMVictorSPX* BaseGauche;

	Encoder* EncodeurDroit;
	Encoder* EncodeurGauche;

	ADXRS450_Gyro* Gyro;

	DoubleSolenoid* DoubleSolenoid1;

	double vitesseDroite, vitesseGauche, y, z, r;
	double distanceParcourueDroite, erreurDroite, erreurPrecedenteDroite, sommeErreursDroite, diferenceErreursDroite;
	double distanceParcourueGauche, erreurGauche, erreurPrecedenteGauche, sommeErreursGauche, diferenceErreursGauche;
	double angleParcouru, erreur, erreurPrecedente, sommeErreurs, diferenceErreurs;
	double tolerance, kP, kI, kD;
	bool vitesseBallShifter;
};

}

#endif /* SRC_BASEROULANTE_H_ */
