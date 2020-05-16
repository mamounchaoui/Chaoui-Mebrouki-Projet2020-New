#pragma once
#include <stdlib.h>
#include <stdio.h>

// cette fonction compte le nombre de lignes d'un fichier
int nbrligne2(FILE* dbb);

//cette fonction permet de:
//-ajouter un profil à la fin du fihier employe.csv
//-ajouter à l'attribut collegues de ce nouveau profil toutes les personnes qui travaillent pour le moment pour la même entreprise que lui
//-ajouter comme nouveau collègue la nouvelle personne ajoutée à l'attibut collegues de tous les profils qui travaillent pour la même entreprise que cette nouvelle personne
void Creer_profil2(char nom[128], char prenom[128], char mail[128], char code_postal[128], char competence[128], char collegue[128], char entreprise[128]);
void Modifier_profil2(char nom[128], char prenom[128], char compe[128], char col[128], char code[128], char entrep[128], int choix);
void Transitionner_profil2(char nom[128], char prenom[128]);
void Supprimer_profil2(char nom[128], char prenom[128]);
void Recherche_par_poste2(char nom[128], char prenom[128], int choix);
void Rechercher_par_anciencollegue2(char nom[128], char prenom[128], char entreprise[128], int choix);