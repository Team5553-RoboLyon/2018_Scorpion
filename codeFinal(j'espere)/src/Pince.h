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

namespace std {

class Pince {
public:
	Pince();
	virtual ~Pince();

	void attraperCube(bool boutonPresse);
	void ejecterCube(bool boutonPresse);
	void leverPince();
    void descendrePinceDebutMatch();
    void descendrePinceFinMatch();

private:
	PWMVictorSPX* Bras;
	PWMVictorSPX* Bag;
	Servo* AntiRetour;
	DigitalInput* Switch;

	const double vitesserotation = 0.5;
	const int dureeAspiration = 30;
	const int dureeEjection = 10;

    int incrementationAspiration = dureeAspiration;
    int incrementationEjection = dureeEjection;
};

}

#endif /* SRC_PINCE_H_ */
