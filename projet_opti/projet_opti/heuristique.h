#pragma once

typedef struct ordonnancement {
	int nbMachines;
	int nbTaches;
	int * dureesTaches;
	int * deadlinesTaches;
	int * dateDebIndisponibilite;
	int * dateFinIndisponibilite;
	int * dateDisponible;
	int * solutions;
} s_ordonnancement;



void heuristique1(s_ordonnancement o);

void heuristique2(s_ordonnancement o);

void heuristique3(s_ordonnancement o);

void heuristique4(s_ordonnancement o);
