/*
 * Fenwick.cpp
 *
 *  Created on: 10 févr. 2018
 *      Author: REBAUDET Thomas
 */

#include "Fenwick.h"
#include <VictorSP.h>
#include "WPILib.h"
#include <DigitalInput.h>
#include <Joystick.h>
#include <Encoder.h>
#include <Servo.h>
#include <math.h>
#include <iostream>

#define TOUR 13.6


namespace std {

Fenwick::Fenwick() {
	fenwick1 = new VictorSP(0);
	fenwick2 = new VictorSP(1);
	fenwick3 = new VictorSP(2);
	shifter = new DoubleSolenoid(2,3);

	//servo = new Servo(0);
	shifter->Set(frc::DoubleSolenoid::kForward);
	anCo2z = new Encoder(4, 5, false, Encoder::EncodingType::k4X);



	anCo2z->Reset();

	fenwick1->Set(0.0);
	fenwick2->Set(0.0);
	fenwick3->Set(0.0);
	//servo->Set(0.0);
	// TODO Auto-generated constructor stub

}
void Fenwick::positionFenwick(Encoder*encodeur1,Encoder*encodeur2, double position)
{
while((encodeur1->Get() + encodeur2->Get()) / 2 <= position)
{
	fenwick1->Set(0.0);
	fenwick2->Set(0.0);
	fenwick3->Set(0.0);
}


}
void Fenwick::ajustementFenwick(Joystick* Joystick1, Encoder* encodeur, Encoder* encodeur2)
{
double POV = Joystick1->GetPOV();
double distanceQuOnVeut/*en cm*/, distanceQuOnA/*en cm*/, distanceRestante;
 distanceQuOnA = ((encodeur->Get()+encodeur2->Get())/2)/7.5;
distanceRestante = (distanceQuOnVeut-distanceQuOnA)/distanceQuOnVeut;
if(distanceRestante<=0.2)
{	fenwick1->Set(0.4);
		fenwick2->Set(0.4);
		fenwick3->Set(0.4);
}
if(POV)
{

	fenwick1->Set(POV);
	fenwick2->Set(POV);
	fenwick3->Set(POV);
//pov = true;

//servo->SetAngle(-uneCertaineValeur);

/*if(servo->GetAngle()<0)
{
	servo->SetAngle(0);
}
*/
}



/*if(pov == false)
{
	servo->SetAngle(uneCertaineValeur);
}

	SmartDashboard::PutNumber("DB/Slider 2",POV);*/
}
void Fenwick::stabilisationFenwick(Encoder* encodeur1,Encoder*encodeur2, Joystick* joystick)
{
	//servo->SetAngle(-uneCertaineValeur);


	if(pov == false)
	{
		//servo->SetAngle(uneCertaineValeur);
	}

}

void Fenwick::shifting(Joystick* Joystick1)
{
	if(Joystick1->GetRawButton(11))
		shifter->Set(frc::DoubleSolenoid::kReverse);
	if(Joystick1->GetRawButton(12))
		shifter->Set(frc::DoubleSolenoid::kForward);


}
void Fenwick::monterDuRobot(Joystick* joystick1, Encoder* encodeur1, Encoder* encodeur2, Servo* servo)
{

	while(((encodeur1->Get()+encodeur2->Get())-2)<=200)
	{
		fenwick1->Set(0.0);
		fenwick2->Set(0.0);
		fenwick3->Set(0.0);
	}
	servo->SetAngle(45);



}
void Fenwick::deplacerFenwick(double consigne)
{



	position = -anCo2z->Get()* 13.6/360;
	erreur = consigne-position;
	sommeAllErreurs += erreur;
	differenceErreurs = erreurPrecedente - erreur;
	puissanceMoteur= (P * erreur/*+ I * sommeAllErreurs + D * differenceErreurs*/);
			fenwick1->Set(puissanceMoteur);
			fenwick2->Set(puissanceMoteur);
			fenwick3->Set(puissanceMoteur);
	erreurPrecedente = erreur;


}
void Fenwick::afficherPosition()
{
	std::cout<<"TIC ENCODEUR:"<<-anCo2z->Get()<<std::endl<<"DISTANCE PARCOURU:"<<-anCo2z->Get()* 13.6/360<<std::endl;

}
Fenwick::~Fenwick() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
