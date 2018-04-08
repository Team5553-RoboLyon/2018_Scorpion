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

	void deployerEtage1();
	void deployerEtage2();
	void treuilMonter(bool boutonPresse);
	virtual ~Grappin();

private:
	VictorSP* Treuil;
	DoubleSolenoid* VerinBas;
	DoubleSolenoid* VerinHaut;
	Joystick* Joystick1;

	bool boutonPresse;
};
}

#endif /* GRAPPIN_H_ */
