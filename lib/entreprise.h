#pragma once
#include <stdbool.h>
#include <stdio.h>


typedef struct entreprise
{
    int index;
    char *nom;
    char *codepost;
    char *courriel;
} entreprise;

typedef struct poste
{
    int index;
    char *titre;
    char *competences;
    struct entreprise *ent;
} poste;


void creer_profil_entreprise(FILE* fic, entreprise* ent);
void creer_poste_a_pourvoir(FILE* fic, poste* unposte);
void supprimer_entreprise(FILE* fic, char* nom_ent);
void supprimer_poste(FILE* fic, char* titre);
int trouver_nom_ent(FILE* fic,char* nomEnt);
entreprise* get_ent(FILE* fic, int indexB);
int trouver_poste_par_competence(FILE* fic, char* competence, char entTrouve[128]);

