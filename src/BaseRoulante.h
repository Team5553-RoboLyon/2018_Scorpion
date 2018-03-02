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

	void arreter();
	void deplacer(Joystick* joystick);
	void changerVitesse(bool etatGachette);

	void parcourir_distance(int distance_a_parcourir);
	void rotation(int angle_consigne);

	void afficherCodeuses();
	void afficherGyro();

	virtual ~BaseRoulante();

private:
	PWMVictorSPX* BaseDroite1;
	PWMVictorSPX* BaseDroite2;
	PWMVictorSPX* BaseGauche;

	Encoder* EncodeurDroit;
	Encoder* EncodeurGauche;

	ADXRS450_Gyro* Gyro;

	DoubleSolenoid* DoubleSolenoid1;

	Timer* timer;

	const double r = 8;

	double vitesseDroite, vitesseGauche, y, z;
	double distanceParcourueDroite, erreurDroite, erreurPrecedenteDroite, sommeErreursDroite, differenceErreursDroite;
	double distanceParcourueGauche, erreurGauche, erreurPrecedenteGauche, sommeErreursGauche, differenceErreursGauche;
	double erreurMoyenne, angleParcouru, erreur, erreurPrecedente, sommeErreurs, differenceErreurs;
	double tolerance, kP, kI, kD;
	bool vitesseBallShifter, etatPrecedentGachette;
};

}

#endif /* SRC_BASEROULANTE_H_ */
