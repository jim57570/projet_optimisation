#pragma once
/*
//repr�sente les diff�rentes structures pour le projet

//structure pour repr�senter une t�che avec une dur�e et une date � laquelle la t�che doit �tre fini au plus tard
typedef struct tache {
	int duree;
	int deadline;
} s_tache;

//structure pour repr�senter une liste de t�ches avec le nombre de t�ches pr�sente
typedef struct liste_taches {
	int nb_taches;
	s_tache ** taches;
} s_liste_taches;

//structure pour repr�senter une machine avec une liste de t�che � effectuer, une date � partir du quelle est disponible et des p�riodes d'indisponibilit�s
typedef struct machine {
	s_liste_taches * liste_taches;
	int disponibilite;
	int * dateDeb;
	int * dateFin;
} s_machine;

//structure pour repr�senter notre exemple de machines avec 3 machines et une p�riode d'indisponibilit�
typedef struct exemple {
	s_machine * m1, *m2, *m3;
	s_liste_taches * liste_taches;
} s_exemple;

//pour cr�er une t�che � partir d'une dur�e et d'une deadline
s_tache * creer_tache(int d, int dl);

//pour cr�er une liste de t�ches � partir d'un nombre de t�ches
s_liste_taches * creer_liste_taches(int nb);

//pour cr�er une machine � partir de p�riodes d'indisponibilit�s et d'un nombre de t�ches
s_machine * creer_machine(int * db, int * df, int nb);

//pour cr�er notre exemple avec 3 machines
s_exemple * creer_exemple(s_liste_taches * l);
*/