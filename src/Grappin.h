/*
 * Grappin.h
 *
 *  Created on: 8 avr. 2018
 *      Author: Nathan
 */

#ifndef GRAPPIN_H_
#define GRAPPIN_H_

#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>

namespace rbl
{

class Grappin
{
public:
	Grappin();

	void initBras();
	void deployerBras(bool boutonPresse);
	void deployerMousqueton(bool boutonPresse2);
	void treuilMonter(double power);
	virtual ~Grappin();

private:
	VictorSP* Treuil;
	DoubleSolenoid* VerinBas;
	DoubleSolenoid* VerinHaut;
	Joystick* Joystick1;
	bool boutonPrecedent;
	bool verrinActif;

	bool boutonPrecedent2;
	bool verrinActif2;
};
}

#endif /* GRAPPIN_H_ */
