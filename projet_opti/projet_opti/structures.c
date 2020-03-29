#include "structures.h"
/*
//initialisation d'une tâche
s_tache * creer_tache(int d, int dl) {
	s_tache * tache = (s_tache *)malloc(sizeof(s_tache));
	tache->duree = d;
	tache->deadline = dl;
	return tache;
}

//initialisation d'une liste de tâche
s_liste_taches * creer_liste_taches(int nb) {
	s_liste_taches * liste_taches = (s_liste_taches *)malloc(sizeof(s_liste_taches));
	liste_taches->taches = (s_tache **)malloc(sizeof(s_tache*)*nb);
	liste_taches->nb_taches = nb;
	return liste_taches;
}

//initialisation d'une machine
s_machine * creer_machine(int * db, int * df, int nb) {
	s_machine * machine = (s_machine *)malloc(sizeof(s_machine));
	machine->liste_taches = creer_liste_taches(nb);
	machine->disponibilite = 0;
	machine->dateDeb = db;
	machine->dateFin = df;
	return machine;
}

//initialisation de notre exemple
s_exemple * creer_exemple(s_liste_taches * l) {
	s_exemple * exemple = (s_exemple *)malloc(sizeof(s_exemple));
	exemple->liste_taches = l;
	exemple->m1 = creer_machine(4, 5, l->nb_taches);
	exemple->m2 = creer_machine(3, 5, l->nb_taches);
	exemple->m3 = creer_machine(5, 6, l->nb_taches);
	return exemple;
}
*/