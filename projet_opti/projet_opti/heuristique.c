#include "heuristique.h"
//heuristique 1: on prend les tâches par ordre de deadline et on les ajoute sur la première machine libre
/*
void heuristique1(s_liste_taches * liste_taches, int nb) {
	int tachesRetard = 0;
	int datePremiereMachineDispo;

	s_machine * tabMachine[3];

	s_exemple * exemple = creer_exemple(liste_taches);

	for(int i=0; i<nb; i++) {
		printf("Tâche %d:\n", i);
		


		//on regarde d'abord quelle est la première machine libre
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



		//on regarde d'abord quelle est la première machine libre
		if ((exemple->m1->disponibilite <= exemple->m2->disponibilite) && (exemple->m2->disponibilite <= exemple->m3->disponibilite)) {
			//puis on vérifie si la tâche peut être réalisé avant la période d'indisponibilité et si elle peut être effectué avant la deadline
			if ((exemple->m1->dateDeb[i] - exemple->m1->disponibilite) >= exemple->liste_taches->taches[0]->duree && exemple->liste_taches->taches[i]->deadline <= (exemple->m1->disponibilite + exemple->liste_taches->taches[i]->duree)) {

			}
		}
	}
}*/

//on place les tâches dans la première machine disponible
//en respectant les contraintes d'indisponibilités de chaque machine
void heuristique1(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int dateDispo[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la période d'indisponibilité
		for (int j = 0; j < 3; j++) {
			dateDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
		}

		//ensuite on regarde si on peut placer les tâches sur les machines avant la période d'indisponibilité
		for (int j = 0; j < 3; j++) {
			if ((o.dureesTaches[i] <= dateDispo[j]) && (o.deadlinesTaches[i] <= o.dateDebIndisponibilite[j])) {
				o.solutions[i] = j;
				o.dateDisponible[j] += o.dureesTaches[i];
				i++;
			}
		}
		//si on a pas pu placer la tâche avant les périodes d'indisponibilité, on regarde pour les placer après
		if (i == tacheEnCours) {
			for (int j = 0; j < 3; j++) {
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[j] + o.dureesTaches[i])) {
					o.solutions[i] = j;
					i++;
				}
			}
			//si on a toujours pas pu placer la tâche, alors on ne peut pas l'exécuter
			if (i == tacheEnCours) {
				o.solutions[i] = 4;
				i++;
			}
		}
		
		
	}
}

//on essaye de placer le maximum de tâches sur une machine
//en respectant les périodes d'indisponibilités
void heuristique2(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int dateDispo[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la période d'indisponibilité
		for (int j = 0; j < 3; j++) {
			dateDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
		}
		//ensuite on regarde si on peut placer les tâches sur les machines avant la période d'indisponibilité
		//dès qu'on peut on sort de la boucle for pour recalculer le temps disponible
		for (int j = 0; j < 3; j++) {
			if ((o.dureesTaches[i] <= dateDispo[j]) && (o.deadlinesTaches[i] >= o.dateDisponible[j] + o.dureesTaches[i])) {
				o.solutions[i] = j;
				o.dateDisponible[j] += o.dureesTaches[i];
				i++;
				break;
			}
		}
		//si on a pas pu placer la tâche avant les périodes d'indisponibilité, on regarde pour les placer après
		if (i == tacheEnCours) {
			for (int j = 0; j < 3; j++) {
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[j] + o.dureesTaches[i])) {
					o.solutions[i] = j;
					i++;
					break;
				}
			}
			//si on a toujours pas pu placer la tâche, alors on ne peut pas l'exécuter
			if (i == tacheEnCours) {
				o.solutions[i] = 4;
				i++;
			}
		}
	}
}


//fonction pour trier le tableau des période disponible par machine
// et mettre à jour le tableau permettant de savoir la machine associé à la période
//tri à bulle
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

//on essaye de placer les tâches sur les machines les moins remplies
//en respectant les périodes d'indisponibilités
void heuristique3(s_ordonnancement o) {
	int i = 0;
	int tacheEnCours;
	int periodeDispo[3];
	int ordreMachine[3];
	while (i <= o.nbTaches) {
		tacheEnCours = i;
		//on calcule le temps disponible sur chaque machine avant la période d'indisponibilité
		for (int j = 0; j < 3; j++) {
			periodeDispo[j] = o.dateDebIndisponibilite[j] - o.dateDisponible[j];
			ordreMachine[j] = j;
		}
		//on regarde ensuite quelle machine possède la plus grande période de disponibilité
		tri_tab(periodeDispo, ordreMachine, 3);
		//ensuite on regarde si on peut placer les tâches sur les machines avant la période d'indisponibilité
		//dès qu'on peut on sort de la boucle for pour recalculer le temps disponible
		for (int j = 2; j >=0; j--) {
			int m = ordreMachine[j];
			if ((o.dureesTaches[i] <= periodeDispo[j]) && (o.deadlinesTaches[i] >= o.dateDisponible[m] + o.dureesTaches[i])) {
				o.solutions[i] = m;
				o.dateDisponible[m] += o.dureesTaches[i];
				i++;
				break;
			}
		}
		//si on a pas pu placer la tâche avant les périodes d'indisponibilité, on regarde pour les placer après
		if (i == tacheEnCours) {
			for (int j = 2; j >= 0; j--) {
				int m = ordreMachine[j];
				if (o.deadlinesTaches[i] >= (o.dateFinIndisponibilite[m] + o.dureesTaches[i])) {
					o.solutions[i] = m;
					i++;
					break;
				}
			}
			//si on a toujours pas pu placer la tâche, alors on ne peut pas l'exécuter
			if (i == tacheEnCours) {
				o.solutions[i] = 4;
				i++;
			}
		}
	}
}

void heuristique4(s_ordonnancement o) {

}