/*
 * Pince.h
 *
 *  Created on: 11 févr. 2018
 *      Author: REBAUDET Thomas
 */

#ifndef SRC_PINCE_H_
#define SRC_PINCE_H_
#include <VictorSP.h>
#include <PWMVictorSPX.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Encoder.h>
#include <Servo.h>
#include <Fenwick.h>

namespace rbl {

class Pince {
public:
	Pince();

	void attraperCube(bool boutonPresse);
	void ejecterCube(bool boutonPresse);

    void ajuster(int pov);
	void goToZero(bool avant);
	void goToSwitch(bool avant);
	void goToScale(bool avant);
	void deplacer();

	virtual ~Pince();

private:
	PWMVictorSPX* Roues;
	PWMVictorSPX* Pivot;
	Encoder* Encodeur;
	DoubleSolenoid* Verin;

	const int dureeAspiration = 30;
	const int dureeEjection = 10;

    int incrementationAspiration, incrementationEjection;

	double kP, kI, kD;
	double vitesse, consigne, positionBras, erreur, sommeErreurs, differenceErreurs, erreurPrecedente;
};

}

#endif /* SRC_PINCE_H_ */
