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

namespace rbl {

class Pince {
public:
	Pince();

	void attraperCube(bool boutonPresse);
	void attraperCubeAuto(bool boutonPresse);
	void ejecterCube(bool boutonPresse);
	void pinceInit();
	void positionVerrin(bool boutonPresse);

	int getPosition();
	int getIncrementAspiration();
	int getIncrementEjection();

	void ajuster(int pov);
	void goToMilieu();
	void goToEchangeur(bool avant);
	void goToSwitch(bool avant);
	void goToScale(bool avant);
	void deplacer();
	void ejectionSwitch(bool boutonPresse);
	virtual ~Pince();
	void test(bool boutonPresse);

private:
	PWMVictorSPX* Roues;
	PWMVictorSPX* Pivot;
	Encoder* Encodeur;
	DoubleSolenoid* Verin;
	int incrementinter=0;
	bool verrinActif;
	bool boutonPrecedent;
	const int dureeAspiration = 25;
	const int dureeAspirationAuto = 35;
	const int dureeEjection = 25;

    int incrementationAspiration, incrementationEjection;

	double kP, kI, kD;
	double vitesse, consigne, positionBras, erreur, sommeErreurs, differenceErreurs, erreurPrecedente;
};

}

#endif /* SRC_PINCE_H_ */
