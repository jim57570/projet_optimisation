#include <stdio.h>
#include "structures.h"
#include "heuristique.h"

int main() {

	printf("Hello World !\n");

	char exit[20] = { 0 };

	//création du problème avec affectation des différentes données
	int durees[5] = { 1, 2, 3, 2, 3 };
	int deadlines[5] = { 2, 3, 4, 4, 5 };
	int debIndispo[3] = { 4, 3, 5 };
	int finIndispo[3] = { 5, 5, 6 };
	int dispo[3] = { 0, 0, 0 };
	int solution[5] = { 4, 4, 4, 4, 4 };
	s_ordonnancement probleme;
	probleme.nbMachines = 3;
	probleme.nbTaches = 5;
	probleme.dateDebIndisponibilite = debIndispo;
	probleme.dateFinIndisponibilite = finIndispo;
	probleme.dureesTaches = durees;
	probleme.deadlinesTaches = deadlines;
	probleme.dateDisponible = dispo;
	probleme.solutions = solution;

	heuristique1(probleme);

	for (int i = 0; i < 5; i++) {
		printf("Tache %d sur la machine %d\n", i, probleme.solutions[i]);
	}
	printf("\n\n");
	//on réinitialise les dates de disponibilités des machines et la solution
	int oui[3] = { 0, 0, 0 };
	int non[5] = { 4, 4, 4, 4, 4 };
	probleme.dateDisponible = oui;
	probleme.solutions = non;

	heuristique2(probleme);
	for (int i = 0; i < 5; i++) {
		printf("Tache %d sur la machine %d\n", i, probleme.solutions[i]);
	}

	scanf_s("%s", exit);



	/*s_liste_taches * liste_taches = creer_liste_taches(5);
	liste_taches->taches[0] = creer_tache(1, 2);
	liste_taches->taches[1] = creer_tache(2, 3);
	liste_taches->taches[2] = creer_tache(3, 4);
	liste_taches->taches[3] = creer_tache(2, 4);
	liste_taches->taches[4] = creer_tache(3, 5);

	heuristique1(liste_taches, liste_taches->nb_taches);*/

	return 0;
}