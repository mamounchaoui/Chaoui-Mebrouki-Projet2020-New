#pragma once
#include <stdlib.h>
#include <stdio.h>

int nbrligne(FILE* dbb);
void Creer_profil(char nom[128], char prenom[128],char mail[128], char code_postal[128], char competence[128], char collegue[128]);
void Modifier_profil();
void Transitionner_profil(char nom[128], char prenom[128], char entrep[128]);
void Supprimer_profil(char nom[128], char prenom[128]);
void Recherche_par_poste();
void Rechercher_par_anciencollegue();

