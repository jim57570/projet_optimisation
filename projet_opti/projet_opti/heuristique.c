#include "heuristique.h"
//heuristique 1: on prend les t�ches par ordre de deadline et on les ajoute sur la premi�re machine libre
/*
void heuristique1(s_liste_taches * liste_taches, int nb) {
	int tachesRetard = 0;
	int datePremiereMachineDispo;

	s_machine * tabMachine[3];

	s_exemple * exemple = creer_exemple(liste_taches);

	for(int i=0; i<nb; i++) {
		printf("T�che %d:\n", i);
		


		//on regarde d'abord quelle est la premi�re machine libre
		if ((exemple->m1->disponibilite <= exemple->m2->disponibilite) && (exemple->m1->disponibilite <= exemple->m3->disponibilite)) {
			tabMachine[0] = exemple->m1;
			if (exemple->m2->disponibilite <= exemple->m3->disponibilite) {
				tabMachine[1] = exemple->m2;
				tabMachine[2] = exemple->m3;
			}
			else {
				tabMachine[1] = exemple->m3;
				tabMachine[2] = exemple->m2;
			}
		}
		else if()



		//on regarde d'abord quelle est la premi�re machine libre
		if ((exemple->m1->disponibilite <= exemple->m2->disponibilite) && (exemple->m2->disponibilite <= exemple->m3->disponibilite)) {
			//puis on v�rifie si la t�che peut �tre r�alis� avant la p�riode d'indisponibilit� et si elle peut �tre effectu� avant la deadline
			if ((exemple->m1->dateDeb[i] - exemple->m1->disponibilite) >= exemple->liste_taches->taches[0]->duree && exemple->liste_taches->taches[i]->deadline <= (exemple->m1->disponibilite + exemple->liste_taches->taches[i]->duree)) {

			}
		}
	}
}*/

//on place les t�ches dans la premi�re machine disponible
//en respectant les contraintes d'indisponibilit�s de chaque machine
void heuristique1(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int dateDispo[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la p�riode d'indisponibilit�
		for (int j = 0; j < 3; j++) {
			dateDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
		}

		//ensuite on regarde si on peut placer les t�ches sur les machines avant la p�riode d'indisponibilit�
		for (int j = 0; j < 3; j++) {
			if ((o.dureesTaches[i] <= dateDispo[j]) && (o.deadlinesTaches[i] <= o.dateDebIndisponibilite[j])) {
				o.solutions[i] = j;
				o.dateDisponible[j] += o.dureesTaches[i];
				i++;
			}
		}
		//si on a pas pu placer la t�che avant les p�riodes d'indisponibilit�, on regarde pour les placer apr�s
		if (i == tacheEnCours) {
			for (int j = 0; j < 3; j++) {
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[j] + o.dureesTaches[i])) {
					o.solutions[i] = j;
					i++;
				}
			}
			//si on a toujours pas pu placer la t�che, alors on ne peut pas l'ex�cuter
			if (i == tacheEnCours) {
				o.solutions[i] = 4;
				i++;
			}
		}
		
		
	}
}

//on essaye de placer le maximum de t�ches sur une machine
//en respectant les p�riodes d'indisponibilit�s
void heuristique2(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int dateDispo[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la p�riode d'indisponibilit�
		for (int j = 0; j < 3; j++) {
			dateDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
		}
		//ensuite on regarde si on peut placer les t�ches sur les machines avant la p�riode d'indisponibilit�
		//d�s qu'on peut on sort de la boucle for pour recalculer le temps disponible
		for (int j = 0; j < 3; j++) {
			if ((o.dureesTaches[i] <= dateDispo[j]) && (o.deadlinesTaches[i] >= o.dateDisponible[j] + o.dureesTaches[i])) {
				o.solutions[i] = j;
				o.dateDisponible[j] += o.dureesTaches[i];
				i++;
				break;
			}
		}
		//si on a pas pu placer la t�che avant les p�riodes d'indisponibilit�, on regarde pour les placer apr�s
		if (i == tacheEnCours) {
			for (int j = 0; j < 3; j++) {
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[j] + o.dureesTaches[i])) {
					o.solutions[i] = j;
					i++;
					break;
				}
			}
			//si on a toujours pas pu placer la t�che, alors on ne peut pas l'ex�cuter
			if (i == tacheEnCours) {
				o.solutions[i] = 4;
				i++;
			}
		}
	}
}

void heuristique3(s_ordonnancement o) {

}

void heuristique4(s_ordonnancement o) {

}