/*
 * Grappin.cpp
 *
 *  Created on: 8 avr. 2018
 *      Author: Nathan
 */

#include "Grappin.h"
#include "Definitions.h"
#include <VictorSP.h>
#include "WPILib.h"
#include <Joystick.h>

namespace rbl
{

Grappin::Grappin()
{
	// TODO Auto-generated constructor stub
	Treuil = new VictorSP(PWM_TREUIL);
	Treuil-> Set(0);

	VerinBas = new DoubleSolenoid(PCM_VERIN_GRAPIN_BAS_A, PCM_VERIN_GRAPIN_BAS_B);
	VerinHaut = new DoubleSolenoid(PCM_VERIN_GRAPIN_HAUT_A, PCM_VERIN_GRAPIN_HAUT_B);

	Joystick1 = new Joystick(0);
	boutonPresse = false;

}

void Grappin::deployerEtage1()
{

}

void Grappin::deployerEtage2()
{

}

void Grappin::treuilMonter(bool boutonPresse)
{
	if (boutonPresse == true)
	{
		Treuil -> Set(0.5);
	}
	else
	{
		Treuil -> Set(0);
	}
}

Grappin::~Grappin()
{
	delete VerinHaut;
	delete VerinBas;
	delete Treuil;
}

} /* namespace rbl */
