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

void Autonome::autonomeInit(char coteSwitch)
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
		erreur = base->parcourir_distance(100);
		break;

	//Tourner
	case 2:
		erreur = base->rotation(rotation1);
		break;

	//Avancer
	case 3:
		erreur = base->parcourir_distance(100);
		break;

	//Tourner
	case 4:
		erreur = base->rotation(rotation2);
		break;

	//Avancer
	case 5:
		erreur = base->parcourir_distance(100);
		break;

	// TODO Descendre pince
	case 6:
		pince->goToSwitch(true);
		std::cout<< "Pivot : " << pince->getPosition() << std::endl;
		break;

	//Ejecter cube
	case 7:
		pince->ejecterCube(true); //On simule un bouton appuyé et on passe au suivant
		etat++;
		break;

	//Fin
	default:
		pince->ejecterCube(false); //On re-appelle ejecter cube en simulant un bouton relaché pour que la pince s'arrete
		break;
	}

	pince->deplacer();

	//Si un PID est consideré comme fini alors on passe à l'etat suivant et on reset capteurs et variables
	if(etat == 1 || etat == 3 || etat == 5)
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
	else if(etat==6)
	{
		if(pince->getPosition() > 300)
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
