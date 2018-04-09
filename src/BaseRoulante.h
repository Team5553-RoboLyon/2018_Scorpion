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
#include <VictorSP.h>
#include <Encoder.h>
#include <iostream>

namespace rbl
{

class BaseRoulante
{
public:
	BaseRoulante();

	void baseInit();

	void arreter();
	void deplacer(Joystick* joystick);
	void changerVitesse(bool etatGachette);

	//Fonctions periode auto qui retournent l'erreur du PID en cm et en degrés
	double parcourir_distance(int distance_a_parcourir);
	double rotation(const int angle_consigne);

	void resetPID();

	void afficherCodeuses();
	void afficherGyro();

	virtual ~BaseRoulante();

private:
	VictorSP* BaseDroite1;
	VictorSP* BaseDroite2;
	VictorSP* BaseGauche1;
	VictorSP* BaseGauche2;

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
	double kP, kI, kD;
	bool vitesseBallShifter, etatPrecedentGachette;
};

}

#endif /* SRC_BASEROULANTE_H_ */
