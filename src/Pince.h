/*
 * Pince.h
 *
 *  Created on: 11 f�vr. 2018
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

namespace std {

class Pince {
public:
	Pince();

	void attraperCube(bool boutonPresse);
	void ejecterCube(bool boutonPresse);
    void descendreDebutMatch();
    void afficherSwitch();
    void ajuster(int pov);
	void desactiverServo();
	void activerServo();

	virtual ~Pince();

private:
	PWMVictorSPX* Bras;
	PWMVictorSPX* Bag;
	Servo* AntiRetour;
	DigitalInput* Switch;

	const double vitesseAspiration = -0.45;
	const double vitesseEjection = 0.6;

	const int dureeAspiration = 30;
	const int dureeEjection = 10;

	bool antiRetourEngage;
    int incrementationAspiration, incrementationEjection;
};

}

#endif /* SRC_PINCE_H_ */
