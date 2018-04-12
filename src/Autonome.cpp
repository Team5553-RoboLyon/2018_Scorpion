/*
 * Autonome.cpp
 *
 *  Created on: 10 avr. 2018
 *      Author: Nathan
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

}

void Autonome::autonomeInit(char coteSwitch, Pince* pince)
{
	if (coteSwitch == 'L')
	{
		switchDroit = false;
		rotation1 = -90;
		rotation2 = 80;
	}
	else
	{
		switchDroit = true;
		rotation1 = 90;
		rotation2 = -80;
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
		erreur = base->rotation(-30);
		break;

	//Avancer
	case 3:
		erreur = base->parcourir_distance(220);
		break;

	//Tourner
	case 4:
		erreur = base->rotation(30);
		break;

	//Avancer
	case 5:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	// TODO Descendre pince
	case 6:
		erreur = base->parcourir_distance(25);
		break;

	//Ejecter cube
	case 7:
		pince->ejecterCube(true); //On simule un bouton appuyé et on passe au suivant
		etat++;
		break;

	case 8:
		erreur = base->parcourir_distance(-30);
		break;

	case 9:
		erreur = base->rotation(50);
		break;

	case 10:
		pince->goToEchangeur(true);
		break;

	case 11:
		erreur = base->parcourir_distance(90);
		break;

	case 12:
		std::cout<<"attrapage"<<std::endl;
		break;

	case 13:
		etat++;
		break;
	case 14:
		erreur = base->parcourir_distance(-60);
		break;

	case 15:
		pince->goToSwitch(true);
		break;

	case 16:
		erreur = base->rotation(-50);
		break;
	case 17:
		erreur = base->parcourir_distance(80);
		break;

	case 18:
		pince->ejecterCube(true);
		etat++;
		break;

	case 19:
			erreur = base->parcourir_distance(-20);
			break;

		case 20:
			erreur = base->rotation(50);
			break;

		case 21:
			pince->goToEchangeur(true);
			break;

		case 22:
			erreur = base->parcourir_distance(100);
			break;

		case 23:
			std::cout<<"attrapage"<<std::endl;
			break;

		case 24:
			etat++;
			break;
		case 25:
			erreur = base->parcourir_distance(-80);
			break;

		case 26:
			pince->goToSwitch(true);
			break;

		case 27:
			erreur = base->rotation(-50);
			break;
		case 28:
			erreur = base->parcourir_distance(80);
			break;

		case 29:
			pince->ejecterCube(true);
			etat++;
			break;

	default:
		 //On re-appelle ejecter cube en simulant un bouton relaché pour que la pince s'arrete
		break;
	}

	pince->ejecterCube(false);
	pince->attraperCubeAuto(false);

	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1 || etat == 3 || etat == 6 || etat == 8 || etat == 11 || etat == 13 || etat == 14 || etat == 17 || etat == 19 || etat == 22 || etat == 24 || etat == 25 || etat == 28)
	{
		if(erreur < toleranceAvancer && erreur > -toleranceAvancer)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat == 2 || etat == 4 || etat == 9 || etat == 16 || etat == 20 || etat == 27)
	{
		if(erreur < toleranceRotation && erreur > -toleranceRotation)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat==5 || etat==15 || etat == 26)
	{
		if(pince->getPosition() > 300)
		{
			etat++;
		}
	}

	else if (etat==21|| etat == 10)
	{
		if(pince->getPosition() > 600)
			etat++;
	}

	else if (etat==12|| etat == 23)
	{
		if(pince->getIncrementAspiration()>40)
		{
			pince->attraperCubeAuto(true);
		}
		else if(pince->getIncrementAspiration()==40)
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
		this->memeCote(base, pince);
	}
	else
	{
		rotationCoteOppose1 = -87;
		rotationCoteOppose2 = -80;
		this->coteOppose(base, pince);
	}
}

void Autonome::departGauche(BaseRoulante* base, Pince* pince)
{
	if (switchDroit == false)
	{
		rotationMemeCote1 = 90;
		this->memeCote(base, pince);
	}
	else
	{
		rotationCoteOppose1 = 87;
		rotationCoteOppose2 = 80;
		this->coteOppose(base, pince);
	}
}

void Autonome::memeCote(BaseRoulante* base, Pince* pince)
{
	switch(etat)
	{
	//Avancer
	case 1:
		erreur = base->parcourir_distance(350);
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
		pince->ejecterCube(true); //On simule un bouton appuyé et on passe au suivant
		etat++;
		break;

	//Fin
	default:
		std::cout<< "####### FIN #######" << std::endl;
		break;
	}

	pince->ejecterCube(false); //On appelle ejecter cube en simulant un bouton relaché pour que la pince s'arrete
	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1)
	{
		if(erreur < toleranceAvancer && erreur > -toleranceAvancer)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat == 2)
	{
		if(erreur < toleranceRotation && erreur > -toleranceRotation)
		{
			etat++;
			base->arreter();
			base->resetPID();
		}
	}
	else if(etat==3)
	{
		if(pince->getPosition() > 300)
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
		erreur = base->parcourir_distance(485);
		break;

	//Tourner
	case 2:
		erreur = base->rotation(rotationCoteOppose1);
		break;

	//Avancer
	case 3:
		erreur = base->parcourir_distance(350);
		break;

	//Tourner
	case 4:
		erreur = base->rotation(rotationCoteOppose2);
		break;

	//Baisser pince
	case 5:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	//Ejecter cube
	case 6:
		pince->ejecterCube(true); //On simule un bouton appuyé et on passe au suivant
		etat++;
		break;

	//Fin
	default :
		std::cout<< "####### FIN #######" << std::endl;
		break;
	}

	pince->attraperCube(false);
	pince->ejecterCube(false);
	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1 || etat == 3 || etat==7 || etat == 11)
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
	else if(etat==5 || etat==10)
	{
		if(pince->getPosition() > 300)
		{
			etat++;
		}
	}
	else if(etat==8)
	{
		if(pince->getPosition() > 600)
		{
			etat++;
		}
	}
	else if(etat==9)
	{
		if(incrementation > 70)
		{
			etat++;
		}
	}
}

Autonome::~Autonome()
{

}

}
