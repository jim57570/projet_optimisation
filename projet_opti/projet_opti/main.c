#include <stdio.h>
#include "heuristique.h"

void afficher(s_ordonnancement o) {
	for (int i = 0; i < 5; i++) {
		printf("Tache %d sur la machine %d\n", i+1, o.solutions[i]+1);
	}
	printf("\n\n");
}

//initialisation du problème (tableau des solutions et des disponibilités des machines)
void init_probleme(s_ordonnancement o) {
	for (int i = 0; i < 3; i++) {
		o.dateDisponible[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		o.solutions[i] = 0;
	}
}

int main() {

	printf("Hello World !\n");

	char exit[20] = { 0 };

	//création du problème
	s_ordonnancement probleme;
	int durees[5] = { 1, 2, 3, 2, 3 };
	int deadlines[5] = { 2, 3, 4, 4, 5 };
	int debIndispo[3] = { 4, 3, 5 };
	int finIndispo[3] = { 5, 5, 6 };
	int dispo[3] = { 0, 0, 0 };
	int solution[5] = { 4, 4, 4, 4, 4 };
	probleme.nbMachines = 3;
	probleme.nbTaches = 5;
	probleme.dateDebIndisponibilite = debIndispo;
	probleme.dateFinIndisponibilite = finIndispo;
	probleme.dureesTaches = durees;
	probleme.deadlinesTaches = deadlines;
	probleme.dateDisponible = dispo;
	probleme.solutions = solution;

	heuristique1(probleme);
	printf("Résultat heuristique 1:\n");
	afficher(probleme);

	//on réinitialise les dates de disponibilités des machines et la solution
	init_probleme(probleme);

	heuristique2(probleme);
	printf("Résultat heuristique 2:\n");
	afficher(probleme);


	//on réinitialise les dates de disponibilités des machines et la solution
	init_probleme(probleme);

	heuristique3(probleme);
	printf("Résultat heuristique 3:\n");
	afficher(probleme);

	//on réinitialise les dates de disponibilités des machines et la solution
	init_probleme(probleme);

	heuristique4(probleme);
	printf("Résultat heuristique 4:\n");
	afficher(probleme);

	scanf_s("%s", exit);

	return 0;
}