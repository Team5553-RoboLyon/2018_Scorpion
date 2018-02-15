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
	VictorSP* fenwick1;
	VictorSP* fenwick2;
	VictorSP* fenwick3;
	//Servo* servo;
	Encoder* anCo2z;
	DoubleSolenoid* shifter;

	bool pov=false;
	bool etatFenwick = true;
	int uneCertaineValeur = 0;
	void ajustementFenwick(Joystick*, Encoder*,Encoder*);
	void deplacerFenwick(double consigne);
	void positionFenwick(Encoder*,Encoder*,double);
	void stabilisationFenwick(Encoder* ,Encoder*, Joystick*);
	void monterDuRobot(Joystick*, Encoder*,Encoder*,Servo*);
	void shifting(Joystick*);
	void afficherPosition();
	double sommeAllErreurs = 0;
	Fenwick();
	virtual ~Fenwick();

private:
	double consigne/*en cm*/, position/*en cm*/, erreur;
	double P = 0.023;
	double I = 0;
	double D = 0;

	double differenceErreurs = 0;
	double puissanceMoteur = 0;
	double erreurPrecedente;



};

} /* namespace std */

#endif /* FENWICK_H_ */
