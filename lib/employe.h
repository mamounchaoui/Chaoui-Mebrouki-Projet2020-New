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

// cette fonction permet de modifier un profil dans la table employe selon le choix de l'utilisateur:
// choix=1:ajouter une compétence
// choix=2:ajouter un ancien collègue de travail
// choix=3:modifier le code postal
// choix=4:modifier l'entreprise
void Modifier_profil2(char nom[128], char prenom[128], char compe[128], char col[128], char code[128], char entrep[128], int choix);

// cette fonction permet de:
// transitionner un profil de la table vers la table chercheurdemploi
// supprime de l'attribut collegues toute personne qui a comme collègue le profil supprimé (que ça soit dans la table employe ou dans la table chercheurdemploi)
// décrémente de l'attribut collegues les id qui sont supérieurs à celui du profil transitionné (que ça soit dans la table employe ou dans la table chercheurdemploi)
void Transitionner_profil2(char nom[128], char prenom[128]);

// cette fonction permet de:
// supprime de l'attribut collegues toute personne qui a comme collègue le profil supprimé (dans la table employe)
// décrémente de l'attribut collegues les id qui sont supérieurs à celui du profil transitionné (dans la table employe)
void Supprimer_profil2(char nom[128], char prenom[128]);

// cette fonction affiche les postes à pourvoir qui correspondent au profil de l'employé. Deux modes de recherches sont possibles:
// -choix=1:Recherche par compétences (les compétences sont directement récupérées du profil de l'employé)
// -choix=2:Recherche par compétences et code postal (les compétences et le code postal sont directement récupérés du profil de l'employé)
void Recherche_par_poste2(char nom[128], char prenom[128], int choix);

// cette fonction permet rechercher parmi les anciens collègues. Deux modes de recherches sont possibles::
// -choix=1:Recherche par entreprise (retoune les ancien(ne)s collègues employés à l'entreprise)
// -choix=2:Recherche par compétences (les compétences sont directement récupérées du profil de l'employé)
void Rechercher_par_anciencollegue2(char nom[128], char prenom[128], char entreprise[128], int choix);