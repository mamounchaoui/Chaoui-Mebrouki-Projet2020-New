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

//Objectif : Créer une entreprise a partir de la structure fourni en input. On ecrit a la suite dans un fichier csv. 
// Entrée : fic : fichier dans lequel on écrit
//          ent : entreprise que l'on veut crée
//Sortie : aucune
void creer_profil_entreprise(FILE* fic, entreprise* ent);


//Objectif : Créer un poste a partir de la structure fourni en input. On ecrit a la suite dans un fichier csv. 
// Entrée : fic : fichier dans lequel on écrit
//          unposte : le poste que l'on veut crée
//Sortie : aucune
void creer_poste_a_pourvoir(FILE* fic, poste* unposte);


//Objectif : Supprimer une entreprise du fichier entreprise.csv
// Entrée : fic : fichier dans lequel on veut supprimer l'entreprise
//          nom_ent : le nom de l'entreprise que l'on veut supprimer
//Sortie : aucune
void supprimer_entreprise(FILE* fic, char* nom_ent);


//Objectif : Supprimer un poste du fichier poste.csv. On effacera le fichier crée pour le remplacer par une nouvelle version sans le poste. 
// Entrée : fic : fichier dans lequel on veut supprimer le poste
//          titre : l'intitulé du poste que l'on veut supprimer
//Sortie : aucune
void supprimer_poste(FILE* fic, char* titre);


//Objectif : Obtenir l'index correspondant au nom de l'entreprise fourni en entrée.
// Entrée : fic : fichier dans lequel on cherche
//          nom_ent : le nom de l'entreprise que l'on cherche
//Sortie : l'index de l'entreprise correspondant
int trouver_nom_ent(FILE* fic,char* nomEnt);


//Objectif : Créer une structure entreprise à partir d'un index. 
// Entrée : fic : fichier dans lequel on cherche
//          indexB : l'index de l'entreprise.
//Sortie : Structure entreprise correspondant a l'index donné
entreprise* get_ent(FILE* fic, int indexB);


//Objectif : Trouver un poste correspondant a la compétence donnée 
// Entrée : fic : fichier dans lequel on cherche
//          competences : chaine de caractères contenant la compétence recherché
//          entTrouve : tableau contenant les index des postes qui contiennent la competence recherché
//Sortie : Structure entreprise correspondant a l'index donné
int trouver_poste_par_competence(FILE* fic, char* competence, int entTrouve[128]);

