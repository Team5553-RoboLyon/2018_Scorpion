/*
 * Definitions.h
 *
 *  Created on: 8 avr. 2018
 *      Author: Nathan
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define DEPART_GAUCHE

#define PWM_BASE_DROITE_1 0
#define PWM_BASE_DROITE_2 1
#define PWM_BASE_GAUCHE_1 2
#define PWM_BASE_GAUCHE_2 3

#define PWM_ROUES 4
#define PWM_PIVOT 5

#define PWM_TREUIL 6

#define DIO_ENCODEUR_DROIT_A 0
#define DIO_ENCODEUR_DROIT_B 1

#define DIO_ENCODEUR_GAUCHE_A 2
#define DIO_ENCODEUR_GAUCHE_B 3

#define DIO_ENCODEUR_PIVOT_A 4
#define DIO_ENCODEUR_PIVOT_B 5

#define PCM_BALLSHIFTER_A 0
#define PCM_BALLSHIFTER_B 1

#define PCM_VERIN_PINCE_A 2
#define PCM_VERIN_PINCE_B 3

#define PCM_VERIN_GRAPIN_BAS_A 4
#define PCM_VERIN_GRAPIN_BAS_B 5

#define PCM_VERIN_GRAPIN_HAUT_A 6
#define PCM_VERIN_GRAPIN_HAUT_B 7

#endif

/* TABLEAU DE CABLAGE du ROBORIO
 *
 * 	RS-232	->
 *
 * 	DIO-0	-> Encodeur Droit (chanel A)
 * 	DIO-1	-> Encodeur Droit (chanel B)
 * 	DIO-2	-> Encodeur Gauche (chanel A)
 * 	DIO-3	-> Encodeur Gauche (chanel B)
 * 	DIO-4	-> Encodeur Pivot (chanel A)
 * 	DIO-5	-> Encodeur Pivot (chanel B)
 * 	DIO-6	->
 * 	DIO-7	->
 * 	DIO-8	->
 * 	DIO-9	->
 *
 *  RELAY-0	->
 *  RELAY-1	->
 *  RELAY-2	->
 *  RELAY-3	->
 *
 *  ANALOG IN -0 	->
 *  ANALOG IN -1 	->
 *  ANALOG IN -2 	->
 *  ANALOG IN -3 	->
 *
 *
 * 	PWM-0	-> VictorSP Droit1
 * 	PWM-1	-> VictorSP Droit2
 * 	PWM-2	-> VictorSP Gauche1
 * 	PWM-3	-> VictorSP Gauche2
 * 	PWM-4	-> VictorSP Roues
 * 	PWM-5	-> VictorSP Pivot
 * 	PWM-6	-> VictorSP Treuil
 * 	PWM-7	->
 * 	PWM-8	->
 * 	PWM-9	->
 *
 */


/* TABLEAU DE CABLAGE du PCM (Pneumatic Control Module)
 *
 * PWM-0	-> Ballshifter (chanel A)
 * PWM-1	-> Ballshifter (chanel B)
 * PWM-2	-> Verin pince (chanel A)
 * PWM-3	-> Verin pince (chanel B)
 * PWM-4	-> Verin pivot bas (chanel A)
 * PWM-5	-> Verin pivot bas (chanel B)
 * PWM-6	-> Verin pivot haut (chanel A)
 * PWM-7	-> Verin pivot haut (chanel B)
 *
 */
