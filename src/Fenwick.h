/*
 * Fenwick.h
 *
 *  Created on: 10 févr. 2018
 *      Author: REBAUDET Thomas
 */

#ifndef FENWICK_H_
#define FENWICK_H_
#include <VictorSP.h>
#include "WPILib.h"
#include <Joystick.h>
#include <GenericHID.h>
#include <Encoder.h>
#include <Servo.h>


namespace std {

class Fenwick {
public:
	Fenwick();
	bool deplacer();
	void goToZero();
	void goToSwitch();
	void goToScale();

	void monteeDuRobot();
	void monteeFinaleFenwick();
	void desactiverServo();
	void activerServo();
	void afficherPosition();

	void monter();

	void descendre();

	void stop();

	virtual ~Fenwick();

private:
	VictorSP* fenwick1;
	VictorSP* fenwick2;
	VictorSP* fenwick3;
	Servo* servo;
	Encoder* Encodeur;

	double consigne, position, erreur, tolerance;
	double sommeErreurs = 0;
	double differenceErreurs = 0;
	double puissanceMoteur = 0;
	double erreurPrecedente;
	bool etatServo;
};

}

#endif /* FENWICK_H_ */
