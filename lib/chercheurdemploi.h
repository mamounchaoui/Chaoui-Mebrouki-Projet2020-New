#pragma once
#include <stdlib.h>
#include <stdio.h>

// compte le nombre le lignes d'un fichier
int nbrligne(FILE* dbb);

// permet de créer un nouveau profil à la fin du fichier chercheurdemploi.cv
void Creer_profil(char nom[128], char prenom[128],char mail[128], char code_postal[128], char competence[128], char collegue[128]);

// permet de modifier une donnée dans le profil d'un chercheur d'emploi (selon le choix de l'utilisateur)
// choix=1:ajouter une compétence
// choix=2:ajouter un ancien collègue de travail
// choix=3:modifier le code postal
void Modifier_profil(char nom[128], char prenom[128], char compe[128], char col[128], char code[128], int choix);

// cette fonction permet: 
// -de supprimer un profil du fichier chercheurdemploi.csv(et décrémente les id des profils qui se situent juste après le profil supprimé)
// -d'ajouter le profil supprimé du fichier cherchcheurdemploi.csv à la fin du fichier employe.csv , tout en ajoutant l'entreprise que la personne vient d'intégrer
// -d'ajouter à l'attibut collegues tous les profils qui travaillent pour la même entreprise que la personne ajoutée
// -d'ajouter comme nouveau collègue la nouvelle personne ajoutée à l'attibut collegues de tous les profils qui travaillent pour la même entreprise que cette nouvelle personne
void Transitionner_profil(char nom[128], char prenom[128], char entrep[128]);

//permet de supprimer un profil du fichier chercheurdemploi.csv (et décrémente les id des profils qui se situent juste après le profil supprimé)
void Supprimer_profil(char nom[128], char prenom[128]);

// cette fonction affiche des informations (Titre du poste/Nom de l'entreprise/Adresse mail de l'entreprise/Code postal de l'entreprise) 
// sur les postes à pourvoir qui correspondent au profil du chercheur d'emploi.
// l'utilisateur a le choix entre deux façons de recherche;
// choix=1:Recherche par compétences (il faut qu'au moins une compétence du chercheur d'emploi corresponde à une compétence du poste à pourvoir)
// choix=2:Recherche par compétences et code postal(il faut qu'au moins une compétence du chercheur d'emploi corresponde à une compétence du poste à pourvoir 
// et que le code postal du chercheur d'emploi corresponde au code postal de l'entreprise)
void Recherche_par_poste(char nom[128], char prenom[128], int choix);

// permet d'ffectuer une recherche parmi les anciens collègues et affiche des informations sur les collègues (Nom du (de la) collègue/Prénom 
// du (de la) collègue/Adresse mail du (de la) collègue)
// l'utilisateur a le choix entre deux façons de recherche:
// choix=1:Recherche par entreprise (retoune les ancien(ne)s collègues employés à l'entreprise)
// choix=2:Recherche par compétences (pour les compétences du chercheur d'emploi, retourne les ancien(ne)s collègues employés aux entreprises qui recherchent ces compétences)
void Rechercher_par_anciencollegue(char nom[128], char prenom[128], char entrep[128], int choix);

