#include "heuristique.h"

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


//fonction pour trier le tableau des p�riode disponible par machine
// et mettre � jour le tableau permettant de savoir la machine associ� � la p�riode
//tri � bulle
void tri_tab(int periodeDispo[], int ordreMachine[], int taille) {
	int tabNonTrie = 1;
	while (tabNonTrie) {
		tabNonTrie = 0;
		for (int i = 0; i < taille - 1; i++) {
			if (periodeDispo[i] > periodeDispo[i + 1]) {

				int tmp = periodeDispo[i + 1];
				periodeDispo[i + 1] = periodeDispo[i];
				periodeDispo[i] = tmp;

				int tmpMachine = ordreMachine[i + 1];
				ordreMachine[i + 1] = ordreMachine[i];
				ordreMachine[i] = tmpMachine;


				tabNonTrie = 1;
			}
		}
	}
}

//on essaye de placer les t�ches sur les machines les moins remplies
//en respectant les p�riodes d'indisponibilit�s
void heuristique3(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int periodeDispo[3];
	int ordreMachine[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la p�riode d'indisponibilit�
		for (int j = 0; j < 3; j++) {
			periodeDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
			ordreMachine[j] = j;
		}
		//on regarde ensuite quelle machine poss�de la plus grande p�riode de disponibilit�
		tri_tab(periodeDispo, ordreMachine, 3);
		//ensuite on regarde si on peut placer les t�ches sur les machines avant la p�riode d'indisponibilit�
		//d�s qu'on peut on sort de la boucle for pour recalculer le temps disponible
		for (int j = 2; j >=0; j--) {
			int m = ordreMachine[j];
			if ((o.dureesTaches[i] <= periodeDispo[j]) && (o.deadlinesTaches[i] >= o.dateDisponible[m] + o.dureesTaches[i])) {
				o.solutions[i] = m;
				o.dateDisponible[m] += o.dureesTaches[i];
				i++;
				break;
			}
		}
		//si on a pas pu placer la t�che avant les p�riodes d'indisponibilit�, on regarde pour les placer apr�s
		if (i == tacheEnCours) {
			for (int j = 2; j >= 0; j--) {
				int m = ordreMachine[j];
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[m] + o.dureesTaches[i])) {
					o.solutions[i] = m;
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

//on essaye de placer les t�ches sur les machines les plus remplies
//en respectant les p�riodes d'indisponibilit�s
void heuristique4(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int periodeDispo[3];
	int ordreMachine[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la p�riode d'indisponibilit�
		for (int j = 0; j < 3; j++) {
			periodeDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
			ordreMachine[j] = j;
		}
		//on regarde ensuite quelle machine poss�de la plus grande p�riode de disponibilit�
		tri_tab(periodeDispo, ordreMachine, 3);
		//ensuite on regarde si on peut placer les t�ches sur les machines avant la p�riode d'indisponibilit�
		//d�s qu'on peut on sort de la boucle for pour recalculer le temps disponible
		for (int j = 0; j < 3; j++) {
			int m = ordreMachine[j];
			if ((o.dureesTaches[i] <= periodeDispo[j]) && (o.deadlinesTaches[i] >= o.dateDisponible[m] + o.dureesTaches[i])) {
				o.solutions[i] = m;
				o.dateDisponible[m] += o.dureesTaches[i];
				i++;
				break;
			}
		}
		//si on a pas pu placer la t�che avant les p�riodes d'indisponibilit�, on regarde pour les placer apr�s
		if (i == tacheEnCours) {
			for (int j = 0; j < 3; j++) {
				int m = ordreMachine[j];
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[m] + o.dureesTaches[i])) {
					o.solutions[i] = m;
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