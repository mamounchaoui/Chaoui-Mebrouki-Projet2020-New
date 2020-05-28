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

typedef struct chercheurEmploi
{
    int index;
    char *nom;
    char *Prenom;
    char *mail;
    char *codepostal;
} chercheurEmploi;

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
//Sortie : 1 -> Suppression effectué
//          0 -> Erreur sur le nom fourni
int supprimer_entreprise(FILE* fic,FILE* fic2, char* nom_ent);


//Objectif : Supprimer un poste du fichier poste.csv. On effacera le fichier crée pour le remplacer par une nouvelle version sans le poste. 
// Entrée : fic : fichier dans lequel on veut supprimer le poste
//          index : l'index du poste que l'on veut supprimer
//          titre : nom du poste
//Sortie : 1 -> Suppression effectué
//          0 -> Erreur sur le nom fourni
int supprimer_poste(FILE* fic, int index, char* titre);

//  Supprime un poste avec seulement l'index fourni
void supprimer_poste_index(FILE* fic, int indexEnt);


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
//Sortie : Le nombre de profil correspondant
int trouver_poste_par_competence(FILE* fic, char* competence, int entTrouve[128]);

// Objectif : Trouver dans le fichier chercheur demploi un chercheur demploi qui possede la compétence
int trouver_emploi_par_competence(FILE* fic, char* competencess, int emploiTrouve[128]);

// Objectif : Trouver dans le fichier chercheur demploi un chercheur demploi qui possede le code postal
int trouver_emploi_par_codep(FILE* fic, char* codepp, int emploiTrouve[128]);

// Objectif : Trouver dans le fichier chercheur demploi un chercheur demploi qui possede la compétence et le code postal
int trouver_emploi_par_competcode(FILE* fic, char* comp,char* codepos, int emploiTrouve[128]);

//Objectif : Retourner une structure chercheur d'emploi à partir d'un index. 
// Entrée : fic : fichier dans lequel on cherche
//          indexB : l'index du chercheur d'emploi.
//Sortie : Structure chercheurEmploi correspondant a l'index donné
chercheurEmploi* get_emploi(FILE* fic, int indexB);

// Objectif : Obtenir la liste des compétences d'un chercheur d'emploi
void get_chercheur(FILE* fic, char* nom,char * prenom,char* retour);

// Objectif : Mettre a jour le fichier fourni en paramètre pour les indexs (ne fonctionne que pour poste.csv, à fix si plus de temps)
void update_index(FILE* fic);