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

namespace std {

class Pince {
public:
	Pince();

	void attraperCube(bool boutonPresse);
	void ejecterCube(bool boutonPresse);
	void lever();
    void descendreDebutMatch();
    void descendreFinMatch();
    void afficherSwitch();

	virtual ~Pince();

private:
	PWMVictorSPX* Bras;
	PWMVictorSPX* Bag;
	Servo* AntiRetour;
	DigitalInput* Switch;

	const double vitesseAspiration = 0.45;
	const double vitesseEjection = 0.3;
	const int dureeAspiration = 30;
	const int dureeEjection = 10;

    int incrementationAspiration = dureeAspiration;
    int incrementationEjection = dureeEjection;
};

}

#endif /* SRC_PINCE_H_ */
