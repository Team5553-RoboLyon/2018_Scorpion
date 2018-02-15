/*
 * Pince.cpp
 *
 *  Created on: 11 févr. 2018
 *      Author: REBAUDET Thomas
 */

#include <Pince.h>
#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>

namespace std {

Pince::Pince() {
	bras = new PWMVictorSPX(7);
	pelleteuse = new PWMVictorSPX(8);
	servo = new Servo(10);
	Joystick1 = new Joystick(0);
	bras->Set(0.0);
	pelleteuse->Set(0.0);

	// TODO Auto-generated constructor stub

}
void Pince::attraperCube()
{
	if(incrementation >= 1 && incrementation<=500 )
			{
			bras->Set(0.5);
			incrementation += 1;
			}
	if (incrementation == 500)
			{
			incrementation = 0;
			}
}
void Pince::lacherCube()
{
	if(incrementation <= 500)
			{
			bras->Set(-0.2);
			incrementation += 1;

			}
	if (incrementation == 2)
		{
		incrementation = 0;
		}
}
void Pince::leverPince(Joystick* Joystick1, Servo* servo, DigitalInput* limitSwitch)
{

}
void Pince::descendrePince(Joystick* Joystick1, Servo* servo, DigitalInput* limitSwitch)
{
	servo -> SetAngle (45);

	while(limitSwitch->Get()==false)
	{
		pelleteuse->Set(-0.2);
	}

	servo -> SetAngle (0);
	pelleteuse -> Set (0.0);

}

Pince::~Pince() {
	// TODO Auto-generated destructor stub
}

} /* namespace std t'es moche*/
