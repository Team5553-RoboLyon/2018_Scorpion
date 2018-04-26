/*
 * Autonome.cpp
 *
 *  Created on: 10 avr. 2018
 *      Author: Julien Bertrant "All rights reserved"
 */
#include <iostream>
#include "BaseRoulante.h"
#include "Pince.h"

#include "Autonome.h"

namespace rbl
{

/*
 * PIDs remarques :
 * Les fonctions actualisent les vitesses et renvoient l'erreur
 * Pour eviter des repetitions, on met la commande de changement d'etat a la fin du switch
 */

Autonome::Autonome()
{
	etat = 1;
}

void Autonome::autonomeInit(char coteSwitch, Pince* pince)
{
	if (coteSwitch == 'L')
	{
		switchDroit = false;
		rotationMilieu1et8 = -35;
		rotationMilieu2et7 = 35;
		rotationMilieu3et5 = 90;
		rotationMilieu4et6 = -90;
	}
	else
	{
		switchDroit = true;
		rotationMilieu1et8 = 35;
		rotationMilieu2et7 = -35;
		rotationMilieu3et5 = -90;
		rotationMilieu4et6 = 90;
	}

	etat = 1;
	incrementation = 0;
}

void Autonome::departMilieu(BaseRoulante* base, Pince* pince)
{
	erreur = 1000;
	switch(etat)
	{
	//Avancer
	case 1:
		erreur = base->parcourir_distance(30);
		break;

	//Tourner
	case 2:
		erreur = base->rotation(rotationMilieu1et8);
		break;

	//Avancer
	case 3:
		erreur = base->parcourir_distance(195);
		break;

	//Tourner
	case 4:
		erreur = base->rotation(rotationMilieu2et7);
		break;

	//Avancer
	case 5:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	//Descendre pince
	case 6:
		erreur = base->parcourir_distance(65);
		break;

	//Ejecter cube
	case 7:
		std::cout<<"ejection"<<std::endl;
		break;

	case 8:
		erreur = base->parcourir_distance(-150);
		break;

	case 9:
		erreur = base->rotation(rotationMilieu3et5);
		break;

	case 10:
		erreur = base->parcourir_distance(120);
		break;

	case 11:
		erreur = base->rotation(rotationMilieu4et6);
		break;

	case 12:
		pince->goToEchangeur(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	case 13:
		pince->attraperCube(true);
		etat++;
		break;

	case 14:
		erreur = base->parcourir_distance(50);
		break;

	case 15:
		erreur = base->parcourir_distance(-50);
		break;

	case 16:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	case 17:
		erreur = base->rotation(rotationMilieu3et5);
		break;

	case 18:
		erreur = base->parcourir_distance(-120);
		break;

	case 19:
		erreur = base->rotation(rotationMilieu4et6);
		break;

	case 20:
		erreur = base->parcourir_distance(150);
		break;

	case 21:
		std::cout<<"ejection"<<std::endl;
		break;

	case 22:
		erreur = base->parcourir_distance(-150);
		break;

	case 23:
		erreur = base->rotation(rotationMilieu2et7);
		break;

	case 24:
		pince->goToEchangeur(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	case 25:
		erreur = base->parcourir_distance(100);
		break;

	case 26:
		pince->attraperCube(true);
		etat++;
		break;

	case 27:
		erreur = base->parcourir_distance(35);
		break;

	case 28:
		erreur = base->parcourir_distance(-35);
		break;

	case 29:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	case 30:
		erreur = base->parcourir_distance(-100);
		break;

	case 31:
		erreur = base->rotation(rotationMilieu1et8);
		break;

	case 32:
		erreur = base->parcourir_distance(150);
		break;

	case 33:
		std::cout<<"ejection"<<std::endl;
		break;

	default:
		 //On re-appelle ejecter cube en simulant un bouton relaché pour que la pince s'arrete
		break;
	}

	pince->ejecterCube(false);
	pince->attraperCube(false);

	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1 || etat == 3 || etat == 6 || etat == 8 || etat == 10 || etat == 14 || etat == 15 || etat == 18 || etat == 20 || etat == 22 || etat == 25 || etat == 27 || etat == 28 || etat == 30 || etat == 32)
	{
		if(erreur < toleranceAvancer && erreur > -toleranceAvancer)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat == 2 || etat == 4 || etat == 9 || etat == 11 || etat == 17 || etat == 19 || etat == 23 || etat == 31)
	{
		if(erreur < toleranceRotation && erreur > -toleranceRotation)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat==5 || etat==16 || etat == 29)
	{
		if(pince->getPosition() > 300 || pince->getPosition() < 400)
		{
			etat++;
		}
	}

	else if (etat==12|| etat == 24)
	{
		if(pince->getPosition() > 600)
		{
			etat++;
		}
	}

	else if (etat==7 || etat==21 || etat==33)
	{
		if(pince->getIncrementEjection()>26)
		{
			pince->ejecterCube(true);
		}
		else if (pince->getIncrementEjection()==26)
		{
			etat++;
		}
	}
}

void Autonome::departDroite(BaseRoulante* base, Pince* pince)
{
	if (switchDroit == true)
	{
		rotationMemeCote1 = -90;
		rotationMemeCote2 = 90;
		rotationMemeCote3 = 45;
		this->memeCote(base, pince);
	}
	else
	{
		rotationCoteOppose1 = -90;
		rotationCoteOppose2 = 90;


		this->coteOppose(base, pince);
	}
}

void Autonome::departGauche(BaseRoulante* base, Pince* pince)
{
	if (switchDroit == false)
	{
		rotationMemeCote1 = 90;
		rotationMemeCote2 = -90;
		rotationMemeCote3 = -45;
		this->memeCote(base, pince);
	}
	else
	{
		rotationCoteOppose1 = 90;
		rotationCoteOppose2 = -90;
		this->coteOppose(base, pince);
	}
}

void Autonome::memeCote(BaseRoulante* base, Pince* pince)
{
	switch(etat)
	{
	//Avancer
	case 1:
		erreur = base->parcourir_distance(380);
		break;

	//Tourner
	case 2:
		erreur = base->rotation(rotationMemeCote1);
		break;

	//Baisser pince
	case 3:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	//Ejecter cube
	case 4:
		erreur = base->parcourir_distance(10);
		break;

	//Avancer jusqu'au switch
	case 5:
		std::cout <<"ejection"<<std::endl;
		break;

	case 6:
		erreur = base->parcourir_distance(-10);
		break;

	case 7:
		erreur = base->rotation(rotationMemeCote2);
		break;

	case 8:
		erreur = base->parcourir_distance(190);
		break;

	case 9:
		erreur=base->rotation(rotationMemeCote3);
		break;

	case 10:
		pince->goToEchangeur(false);
		break;

	case 11:
		erreur=base->parcourir_distance(-50);
		break;

	case 12:
		std::cout <<"aspiration"<<std::endl;
		etat++;
		break;

	case 13:
		base->parcourir_distance(-20);
		break;

	case 14:
		base->parcourir_distance(20);
		break;

	case 15:
		pince->goToSwitch(false);
		break;

	case 16:
		base->parcourir_distance(-20);
		break;

	case 17:
		std::cout <<"ejection"<<std::endl;
		break;

	//Fin
	default:
		break;
	}

	pince->ejecterCube(false); //On appelle ejecter cube en simulant un bouton relaché pour que la pince s'arrete
	pince->attraperCubeAuto(false);
	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1 || etat==4 || etat==6 || etat==8 || etat==11 || etat==13 || etat==14 || etat==16)
	{
		if(erreur < toleranceAvancer && erreur > -toleranceAvancer)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat == 2 || etat==7 || etat==9)
	{
		if(erreur < toleranceRotation && erreur > -toleranceRotation)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat==3 )
	{
		if(pince->getPosition() > 300)
		{
			etat++;
		}
	}
	else if(etat==10 )
	{
		if(pince->getPosition() <-600)
		{
			etat++;
		}
	}
	else if(etat==15 )
	{
		if(pince->getPosition() >-300)
		{
			etat++;
		}
	}
	else if (etat==5 || etat==17)
	{
		if(pince->getIncrementEjection()>26)
		{
			pince->ejecterCube(true);
		}
		else if (pince->getIncrementEjection()==26)
		{
			etat++;
		}
	}
}

void Autonome::coteOppose(BaseRoulante* base, Pince* pince)
{
	switch(etat)
	{
	//Avancer
	case 1:
		erreur = base->parcourir_distance(550);
		break;

	//Tourner
	case 2:
		erreur = base->rotation(rotationCoteOppose1);
		break;

	//Avancer
	case 3:
		erreur = base->parcourir_distance(480);
		break;

	//Tourner
	case 4:
		erreur = base->rotation(rotationCoteOppose2);
		break;

	//Baisser pince
	case 5:
		pince->goToEchangeur(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	//Ejecter cube
	case 6:
		pince->positionVerrin(true); //On simule un bouton appuyé et on passe au suivant
		etat++;
		break;

	case 7:
		pince->goToEchangeur(false); //On simule un bouton appuyé et on passe au suivant
		break;

	case 8:
		pince->attraperCube(true);
		etat ++;
		break;

	case 9:
		base->parcourir_distance(-30);
		break;

	case 10:
		pince->goToSwitch(false);
		break;

	case 11:
		std::cout<< "ejection" << std::endl;
		break;

	case 12:
		pince->goToEchangeur(true);
		break;

	case 13:
		pince->attraperCube(true);
		etat ++;
		break;

	case 14:
		base->parcourir_distance(30);
		break;

	case 15:
		pince->goToSwitch(false);
		break;

	case 16:
		base->parcourir_distance(-30);
		break;

	case 17:
		pince->ejecterCube(true);
		break;

	//Fin
	default :
		std::cout<< "####### FIN #######" << std::endl;
		break;
	}

	pince->positionVerrin(false);
	pince->attraperCube(false);
	pince->ejecterCube(false);
	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1 || etat == 3 || etat == 9 || etat == 14 || etat == 16)
	{
		if(erreur < toleranceAvancer && erreur > -toleranceAvancer)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat == 2 || etat == 4)
	{
		if(erreur < toleranceRotation && erreur > -toleranceRotation)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat==5 || etat==7 || etat == 12 || etat == 15)
	{
		if(pince->getPosition() > 600 || pince->getPosition() < -600)
		{
			etat++;
		}
	}
	else if(etat==10)
	{
		if(pince->getPosition() > -350)
		{
			etat++;
		}
	}
	else if (etat==11)
	{
		if(pince->getIncrementEjection()>26)
		{
			pince->ejecterCube(true);
		}
		else if (pince->getIncrementEjection()==26)
		{
			etat++;
		}
	}
}

Autonome::~Autonome()
{

}

}
