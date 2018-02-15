/*
 * Pince.h
 *
 *  Created on: 11 févr. 2018
 *      Author: REBAUDET Thomas
 */

#ifndef SRC_PINCE_H_
#define SRC_PINCE_H_
#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>
namespace std {

class Pince {
public:
	PWMVictorSPX* bras;
	PWMVictorSPX* pelleteuse;
	Servo* servo;
	Joystick* Joystick1;
	void attraperCube();
	void lacherCube();
	void leverPince(Joystick* , Servo*, DigitalInput*);
    void descendrePince(Joystick* , Servo*, DigitalInput*);
    int incrementation = 0;

	Pince();
	virtual ~Pince();
};

} /* namespace std */

#endif /* SRC_PINCE_H_ */
