#include "genetique.h"

void algo_genetique() {


	srand(time(0));
	int placements[7][NBTACHES] = { {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0},
									  {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 1, 1} };
	
	int limitDate[NBTACHES] = { 2, 3, 4, 4, 5 };
	int indisponibleStart[6] = { 4, 3, 5, 0, 0, 0 };
	int indisponibleFinish[6] = { 0, 0, 0, 5, 5, 6 };
	int durations[NBTACHES] = { 1, 2, 3, 2, 3 };
	int number_of_tasks = 5;

	struct Problem p;
	p.placements = &placements[0][0];
	p.deadlinesTaches = &limitDate[0];
	p.dateDebIndisponibilite = &indisponibleStart[0];
	p.dateFinIndisponibilite = &indisponibleFinish[0];
	p.dureesTaches = &durations[0];
	p.nbTaches = number_of_tasks;


	struct Problem* old_solutions[NBSOLUTIONS];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		struct Problem* new_p = malloc(sizeof(*new_p));
		new_p->placements = malloc(7 * NBTACHES * sizeof(int));
		copy_placements(new_p->placements, p.placements);
		new_p->deadlinesTaches = &limitDate[0];
		new_p->dateDebIndisponibilite = &indisponibleStart[0];
		new_p->dateFinIndisponibilite = &indisponibleFinish[0];
		new_p->dureesTaches = &durations[0];
		new_p->nbTaches = number_of_tasks;
		old_solutions[i] = new_p;
	}

	is_valid(old_solutions[2]);

	struct Problem* new_solutions[NBSOLUTIONS];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		struct Problem* new_p = malloc(sizeof(*new_p));
		new_p->placements = malloc(7 * NBTACHES * sizeof(int));
		copy_placements(new_p->placements, p.placements);
		new_p->deadlinesTaches = &limitDate[0];
		new_p->dateDebIndisponibilite = &indisponibleStart[0];
		new_p->dateFinIndisponibilite = &indisponibleFinish[0];
		new_p->dureesTaches = &durations[0];
		new_p->nbTaches = number_of_tasks;
		new_solutions[i] = new_p;
	}

	float avg[10000];

	for (int i = 0; i < 10000; i++) {
		// on génère une nouvelle solution
		for (int j = 0; j < NBSOLUTIONS; j++) {
			avg[i] = new_son(old_solutions, new_solutions[j]->placements);
		}
		//on copie la nouvelle solution dans l'ancienne
		for (int k = 0; k < NBSOLUTIONS; k++) {
			//on vérifie que les nouvelles solutions sont valides
			if (!is_valid(new_solutions[k]))
				printf("Erreur\n");
			copy_placements(old_solutions[k]->placements, new_solutions[k]->placements);
		}
	}

	
	printf("La solution la plus efficace issue de la dernière génération : \n");
	struct Problem* champion = best(new_solutions);
	display(champion);

}
