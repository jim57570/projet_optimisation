#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBTACHES 5
#define NBSOLUTIONS 50
#define BOUNDARY1 25
#define BOUNDARY2 40 

struct Problem {
	int nbTaches;
	int* placements;
	int* dateDebIndisponibilite;
	int* dateFinIndisponibilite;
	int* dureesTaches;
	int* deadlinesTaches;
};

//retourne le nombre de tâches non effectués 
int not_done(struct Problem * p) {
	int res;
	res = 0;
	for (int i = 0; i < p->nbTaches; ++i) {
		res += *(p->placements + 6 * (p->nbTaches) + i);
	}
	return res;
}

//retourne le nombre de tâches qui sont en retard
int not_in_time(struct Problem *p) {
	int taches;
	taches = 0;
	int res;
	// on regarde d'abord sur les machines 1 à 3
	for (int j = 0; j < 3; j++) {
		res = 0;
		for (int i = 0; i < p->nbTaches; i++) {
			res += (*(p->placements + j * p->nbTaches + i)) * (*(p->dureesTaches + i));
			if ((*(p->placements + j * p->nbTaches + i)) && res > (*(p->deadlinesTaches + i))) {
				taches++;
			}
		}
	}
	// puis sur les machines 4 à 6
	for (int j = 3; j < 6; j++) {
		res = (*(p->dateFinIndisponibilite + j));
		for (int i = 0; i < p->nbTaches; i++) {
			res += (*(p->placements + j * p->nbTaches + i)) * (*(p->dureesTaches + i));
			if ((*(p->placements + j * p->nbTaches + i)) && res > (*(p->deadlinesTaches + i))) {
				taches++;
			}
		}
	}
	// et enfin sur la dernière machine (non effectuées)
	taches += not_done(p);
	return taches;
}

//permet de définir si une solution est valide (toutes les tâches executé dans les temps)
int is_valid(struct Problem* p) {
	int res;
	for (int j = 0; j < 3; j++) {
		res = 0;
		for (int i = 0; i < p->nbTaches; i++) {
			res += *(p->placements + j * p->nbTaches + i) * *(p->dureesTaches + i);
		}
		if (res > *(p->dateDebIndisponibilite + j)) {

			return 0;
		}
	}
	for (int i = 0; i < p->nbTaches; i++) {
		res = 0;
		for (int j = 0; j < 7; j++) {
			res += *(p->placements + j * p->nbTaches + i);
		}
		if (res != 1) {
			return 0;
		}
	}
	// de la machine 1 à 3
	for (int j = 0; j < 3; j++) {
		res = 0;
		for (int i = 0; i < p->nbTaches; i++) {
			res += *(p->placements + j * p->nbTaches + i) * *(p->dureesTaches + i);
			if (*(p->placements + j * p->nbTaches + i) && res > *(p->deadlinesTaches + i)) {
				
				return 0;
			}
		}
	}
	// de la machine 4 à 6
	for (int j = 3; j < 6; j++) {
		res = *(p->dateFinIndisponibilite + j);
		for (int i = 0; i < p->nbTaches; i++) {
			res += *(p->placements + j * p->nbTaches + i) * *(p->dureesTaches + i);
			if (*(p->placements + j * p->nbTaches + i) && res > *(p->deadlinesTaches + i)) {
				
				return 0;
			}
		}
	}

	return 1;
}
void copy_placements(int* plac1, int* plac2) {

	for (int i = 0; i < 7; i++) {
		for (int h = 0; h < NBTACHES; h++) {
			*(plac1 + i * 5 + h) = *(plac2 + i * 5 + h);
		}
	}
}


//fonction pour comparer 2 solutions
int compare(const void* solutionA, const void * solutionB) {
	int nb_delayedA;
	int nb_delayedB;
	nb_delayedA = not_done((struct Problem *) solutionA);
	nb_delayedB = not_done((struct Problem *) solutionB);
	return nb_delayedA - nb_delayedB;
}

//fonction d'affichage
void display(struct Problem* p) {
	int machine[NBTACHES];
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < p->nbTaches; i++) {
			if (*(p->placements + j * p->nbTaches + i) == 1) {
				machine[i] = 1;
			}
			
		}
		if (j < 3) {
			printf("La machine %d effectue les tâches suivantes avant le début de l'indisponibilité de la machine : ", j + 1);
		}
		else if (j < 6) {
			printf("La machine %d effectue les tâches suivantes après la fin de l'indisponibilité de la machine : ", j - 2);
		}

		for (int k = 0; k < p->nbTaches; k++) {
			if (machine[k] == 1) {
				printf("%d ", k);
				machine[k] = 0;
			}
		}
		printf("\n");
	}
}

// fonction de mutation sur une solution aléatoire
int* mutation(int copie_placements[7][NBTACHES]) {
	int* new_vec = malloc(7 * NBTACHES * sizeof(int));
	int change = rand() % NBTACHES;
	int new_machine = rand() % 7;
	int i;

	for (int i = 0; i < 7; i++) {
		for (int h = 0; h < NBTACHES; h++) {
			*(new_vec + 5 * i + h) = copie_placements[i][h];
		}
	}

	for (i = 0; i < 7; i++) {
		if (*(new_vec + 5 * i + change) == 1)
			*(new_vec + 5 * i + change) = 0;
	}

	*(new_vec + 5 * new_machine + change) = 1;

	return new_vec;
}


// Fonction pour générer un membre de la nouvelle génération
float new_son(struct Problem* solutions[NBSOLUTIONS], int* placements_new) {
	int fit[NBSOLUTIONS];
	int sum = 0;
	float avg;

	for (int i = 0; i < NBSOLUTIONS; i++) {
		fit[i] = NBTACHES - not_done(solutions[i]);
		sum += fit[i];
	}

	avg = (double)sum / NBSOLUTIONS;

	// Roulette (on choisit un nombre au hasard)
	int luck = rand();
	luck = luck % sum;
	int select_ind;
	sum = 0;

	for (int i = 0; i < NBSOLUTIONS; i++) {
		if (sum <= luck && sum + fit[i] >= luck)
			select_ind = i;
		sum += fit[i];
	}

	int copie_placements[7][NBTACHES];

	copy_placements(&copie_placements[0][0], solutions[select_ind]->placements);

	// on essaye différente mutation
	do {
		copy_placements(solutions[select_ind]->placements, mutation(copie_placements));
	} while (!is_valid(solutions[select_ind]));

	int aux;

	copy_placements(placements_new, solutions[select_ind]->placements);
	copy_placements(solutions[select_ind]->placements, &copie_placements[0][0]);

	return avg;
}

//structure pour de la meilleure solution
struct Problem* best(struct Problem* solutions[NBSOLUTIONS]) {
	int best = not_done(solutions[0]);
	struct Problem* best_it = solutions[0];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		if (not_done(solutions[i]) < best) {
			best = not_done(solutions[i]);
			best_it = solutions[i];
		}
	}
	return best_it;
}


void algo_genetique();