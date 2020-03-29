#pragma once
/*
//représente les différentes structures pour le projet

//structure pour représenter une tâche avec une durée et une date à laquelle la tâche doit être fini au plus tard
typedef struct tache {
	int duree;
	int deadline;
} s_tache;

//structure pour représenter une liste de tâches avec le nombre de tâches présente
typedef struct liste_taches {
	int nb_taches;
	s_tache ** taches;
} s_liste_taches;

//structure pour représenter une machine avec une liste de tâche à effectuer, une date à partir du quelle est disponible et des périodes d'indisponibilités
typedef struct machine {
	s_liste_taches * liste_taches;
	int disponibilite;
	int * dateDeb;
	int * dateFin;
} s_machine;

//structure pour représenter notre exemple de machines avec 3 machines et une période d'indisponibilité
typedef struct exemple {
	s_machine * m1, *m2, *m3;
	s_liste_taches * liste_taches;
} s_exemple;

//pour créer une tâche à partir d'une durée et d'une deadline
s_tache * creer_tache(int d, int dl);

//pour créer une liste de tâches à partir d'un nombre de tâches
s_liste_taches * creer_liste_taches(int nb);

//pour créer une machine à partir de périodes d'indisponibilités et d'un nombre de tâches
s_machine * creer_machine(int * db, int * df, int nb);

//pour créer notre exemple avec 3 machines
s_exemple * creer_exemple(s_liste_taches * l);
*/