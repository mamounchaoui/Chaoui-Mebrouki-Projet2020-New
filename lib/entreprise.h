#pragma once
#include <stdbool.h>
#include <stdio.h>


typedef struct entreprise
{
    int index;
    char nom[128];
    char codepost[128];
    char courriel[128];
} entreprise;

#define MAX_ENT 5

typedef struct poste
{
    int index;
    char titre[128];
    char competences[128];
    struct entreprise *ent[MAX_ENT];
} poste;


void creer_profil_entreprise(FILE* fic, entreprise* ent);
void creer_poste_a_pourvoir(FILE* fic, poste* unposte);
void supprimer_entreprise(FILE* fic, char* nom_ent);
void supprimer_poste(FILE* fic, char* titre);
int trouver_nom_ent(FILE* fic);
int trouver_poste_par_competence(FILE* fic, char* competence);

