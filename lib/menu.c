#include "chercheurdemploi.h"
#include "employe.h"
#include "entreprise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuEnt(void);
void menuPrincipal(void);
void choixRecherche(void);
void menuEmploye(void);
void menuChercheurEmploi(void);

void menuEnt(void){
     char choisir;
     char nomEnt[128] = "nomDefaut", codepost[128] ="code post defaut", mail[128]="mail defaut";
     char titre[128]="titredefaut", competences[1048]="competence defaults", entName[128]="entdefault"; 
     int indexEnt;
     char debug2=' ';

     FILE *fic;
     FILE *fic2;
     fic = fopen("test/poste.csv","r+");
     fic2 = fopen("test/entreprise.csv","r+");

     printf("\n");
     printf("-------------------------------------------------------\n");
     printf("-------------------- Menu Entreprise ------------------\n");
     printf("-------------------------------------------------------\n");

     printf("Vous voulez :\n");
     printf("1. Créer le profil de votre entreprise \n");
     printf("2. Créer le profil d'un poste à pourvoir \n");
     printf("3. Supprimer le profil d'un poste maintenant pourvu \n");
     printf("4. Supprimer le profil d'une entreprise \n");
     printf("5. Faire une recherche parmi les chercheurs d'emploi \n");
     printf("\n");
     printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : \n");

     choisir = getchar();
     switch(choisir){

          case '1' : printf("Entrez les données de votre entreprise : \n");
                    printf("Le nom de votre entreprise : \n ");
                    scanf("%s",nomEnt);
                    printf("Le code postal de votre entreprise : \n ");
                    scanf("%s",codepost);
                    printf("L'adresse mail de votre entreprise : \n ");
                    scanf("%s",mail);
                    entreprise ent = {1,nomEnt,codepost,mail};
                    FILE *fic1;
                    fic1 = fopen("test/entreprise.csv","r+");
                    creer_profil_entreprise(fic1,&ent);
                    break;

          case '2' : printf("Entrez les données de votre poste : \n");
                    printf("L'intitulé du poste : \n ");
                    scanf("%s",titre);
                    printf("Les compétences requises pour le poste (séparer les compétences par des ;) : \n ");
                    scanf("%s",competences);
                    printf("Le nom de votre entreprise (Si vous l'avez créer) : \n ");
                    scanf("%s",entName);
                    indexEnt = trouver_nom_ent(fic2,entName);
                    if(indexEnt == 0){
                         printf("Erreur l'entreprise fourni n'existe pas ! \n");
                         break;
                    }
                    entreprise* ent2 = get_ent(fic2,indexEnt);
                    poste poste1= {1,titre,competences, ent2};
                    creer_poste_a_pourvoir(fic, &poste1);
                    printf("Votre poste a été crée avec succès ! \n");
                    break;

          case '3' :printf("Entrez le nom du poste que vous souhaitez supprimer : \n");
                    scanf("%s",titre);
                    printf("Entrez le nom de votre entreprise : \n");
                    scanf("%s",nomEnt);
                    indexEnt = trouver_nom_ent(fic2,nomEnt);
                    int test = supprimer_poste(fic,indexEnt,titre);
                    if(test == 1){
                         printf("Nous avons supprimé avec succès le poste indiqué ! \n");
                    }
                    else{
                         printf("Erreur : le nom du poste ou le nom de l'entreprise est incorrect ! Vérifiez les MAJs !\n");
                    }
                    break;

          case '4' :printf("Entrez le nom de l'entreprise que vous souhaitez supprimer : \n");
                    scanf("%s",nomEnt);

                    int test4 = supprimer_entreprise(fic2,fic,nomEnt);
                    if(test4 == 1){
                         printf("Nous avons supprimé avec succès l'entreprise indiqué ! \n");
                    }
                    else{
                         printf("Erreur : le nom de l'entreprise est incorrect ! Vérifiez les MAJs !\n");
                    }
                    break;
          case '5' : choisir = getchar(); printf("%c", debug2);
                    choixRecherche();
                    break;          
          case 'q' : printf("FERMETURE ... \n"); break;
          case 'p' :printf("Retour au menu précédent \n"); choisir = getchar(); printf("%c", debug2);
                    menuPrincipal(); break;
          default : printf("Erreur de saisie ! \n");break;
     }
}

void choixRecherche(void){

//     FILE *fic;
//     FILE *fic2;
     FILE *fic3;
//     fic = fopen("test/poste.csv","r+");
//     fic2 = fopen("test/entreprise.csv","r+");
     fic3 = fopen("test/chercheurdemploi.csv","r+"); 

     char compo[128] = {0};
     char codeep[128] = {0};
     int solution[128] = {0};
     char debug2 = ' ';

     printf("\n");
     printf("-------------------------------------------------------\n");
     printf("------------- Menu Entreprise - Recherche -------------\n");
     printf("-------------------------------------------------------\n");

     printf("Vous souhaitez :\n");
     printf("1. Chercher par compétences  \n");
     printf("2. Chercher par code postal \n");
     printf("3. Chercher par compétences et code postal \n");

     printf("\n");
     printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : \n");

     char choix1 = getchar();
     switch(choix1){ 
          case '1' :
                    printf("Entrez la competence recherché : \n");
                    scanf("%s",compo);
                    int test = trouver_emploi_par_competence(fic3,compo,solution);

                    if(test == 0){
                         printf("Désolé, aucun chercheur d'emploi ne possède cette compétence");
                         break;
                    }

                    printf("%d postes ont été trouvés ! \n",test);
                    printf("Voici les infos des chercheurs d'emploi qui possèdent cette compétence : \n");
                    printf("------------------ \n");
                    
                    for(int k=0;k<test;k++){
                         chercheurEmploi* emploi2 = get_emploi(fic3,solution[k]);
                         printf("Prénom : "); puts(emploi2->Prenom);
                         printf("Nom : ");puts(emploi2->nom);
                         printf("Mail : ");puts(emploi2->mail);
                         printf("------------------ \n");
                    }
                    
                    break;

          case '2' : printf("Entrez le code postal recherché : \n");
                    scanf("%s",codeep);
                    int test2 = trouver_emploi_par_codep(fic3,codeep,solution);
                    if(test2 == 0){
                         printf("Désolé, aucun chercheur d'emploi ne possède ce code postal");
                         break;
                    }

                    printf("%d postes ont été trouvés ! \n",test2);
                    printf("Voici les infos des chercheurs d'emploi qui possèdent cette compétence : \n");
                    printf("------------------ \n");
                    
                    for(int k=0;k<test2;k++){
                         chercheurEmploi* emploi2 = get_emploi(fic3,solution[k]);
                         printf("Prénom : "); puts(emploi2->Prenom);
                         printf("Nom : ");puts(emploi2->nom);
                         printf("Mail : ");puts(emploi2->mail);
                         printf("------------------ \n");
                    } break;

          case '3' : printf("Entrez la competence recherché : \n");
                    scanf("%s",compo);
                    printf("Entrez le code postal recherché : \n");
                    scanf("%s",codeep);
                    int test3 = trouver_emploi_par_competcode(fic3,compo,codeep,solution);
                    if(test3 == 0){
                         printf("Désolé, aucun chercheur d'emploi ne possède ce code postal et cette compétence \n");
                         break;
                    }

                    printf("%d postes ont été trouvés ! \n",test3);
                    printf("Voici les infos des chercheurs d'emploi qui possèdent ces spécifications : \n");
                    printf("------------------ \n");
                    for(int k=0;k<test3;k++){
                         chercheurEmploi* emploi2 = get_emploi(fic3,solution[k]);
                         printf("Prénom : "); puts(emploi2->Prenom);
                         printf("Nom : ");puts(emploi2->nom);
                         printf("Mail : ");puts(emploi2->mail);
                         printf("------------------ \n");
                    }

                    break;
          case 'q' : printf("FERMETURE ... \n"); break;
          case 'p' :printf("Retour au menu précédent \n"); debug2 = getchar(); printf("%c", debug2);
                    menuEnt(); break;
          default : printf("Erreur de saisie ! \n");break;
    }

}

void menuPrincipal(void){
     char choix1;
     char debug=' ';
     printf("\n");
     printf("---------------- Bienvenue sur LuminIn ----------------\n");

     printf("-------------------- Menu Principal -------------------\n");


     printf("Vous êtes :\n");
     printf("1. Une entreprise \n");
     printf("2. Un employé \n");
     printf("3. Un chercheur d'emploi \n");
     printf("\n");
     printf("Votre choix ('q' pour quitter) : \n");

     choix1 = getchar();
     switch(choix1){ 
          case '1' : debug = getchar(); printf("%c", debug); // ca bug donc je fais ca
                    menuEnt();
                    break;
          case '2' : debug = getchar(); printf("%c", debug); // ca bug donc je fais ca
                    menuEmploye();
                    break;
          case '3' : debug = getchar(); printf("%c", debug); 
                    menuChercheurEmploi();
                    break;
          case 'q' : printf("FERMETURE ... \n"); break;
    }

}


void menuEmploye(void){
     char choix1;
     int choix2;
     char debug=' ';

     char nom[128] = {0};
     char prenom[128]= {0};
     char mail[128]= {0};
     char code_postal[128]= {0};
     char competence[128]= {0}; 
     char collegue[128]= {0}; 
     char entreprise[128]= {0};

     printf("\n");
     printf("----------------------------------------------------\n");
     printf("-------------------- Menu Employé ------------------\n");
     printf("----------------------------------------------------\n");


     printf("Vous voulez :\n");
     printf("1. Créer un profil \n");
     printf("2. Modifier un profil \n");
     printf("3. Transitionner le profil de «chercheur d'emploi» à un profil «employé» \n");
     printf("4. Supprimer un profil \n");
     printf("5. Rechercher parmi les les postes à pourvoir qui correspondent à son profil\n");
     printf("6. Rechercher parmi les anciens collègues \n");
     printf("\n");
     printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : \n");

     choix1 = getchar();
     switch(choix1){ 
          case '1' : printf("Entrez les données suivantes : \n");
                    printf("Le nom de l'employé : \n ");
                    scanf("%s",nom);
                    printf("Le Prénom de l'employé : \n ");
                    scanf("%s",prenom);
                    printf("L'adresse mail de l'employé : \n ");
                    scanf("%s",mail);
                    printf("Le code postal de l'employé : \n ");
                    scanf("%s",code_postal);
                    printf("Les compétences de l'employé (séparez les différentes compétences par des ;) : \n ");
                    scanf("%s",competence);
                    printf("Le nom et prénom du collegue de l'employé : \n ");
                    scanf("%s",collegue);
                    printf("L'entreprise de l'employé : \n ");
                    scanf("%s",entreprise);
                    Creer_profil2(nom,prenom,mail,code_postal,competence,collegue,entreprise);

                    break;
          case '2' : printf("Vous voulez :\n");
                    printf("1. Ajouter des compétences \n");
                    printf("2. Ajouter un(e) ancien(ne) collègue de travail \n");
                    printf("3. Modifier le code postal \n");
                    printf("4. Modifier l'entreprise \n");
                    scanf("%d",&choix2);
                    switch(choix2){
                         case 1:   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez la compétence à ajouter: \n ");
                                   scanf("%s",competence);
                                   Modifier_profil2(nom,prenom,competence,"defaut","defaut","defaut",1);
                                   break;
                         case 2:   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nom et prénom du collègue à ajouter(ex : nom,prenom ): \n ");
                                   scanf("%s",collegue);
                                   Modifier_profil2(nom,prenom,"defaut",collegue,"defaut","defaut",2);
                                   break;
                         case 3:   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nouveau code postal : \n ");
                                   scanf("%s",code_postal);
                                   Modifier_profil2(nom,prenom,"defaut","defaut",code_postal,"defaut",3);
                                   break;
                         case 4:   
                                   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nouveau nom de l'entreprise : \n ");
                                   scanf("%s",entreprise);
                                   Modifier_profil2(nom,prenom,competence,"defaut","defaut","defaut",4);
                                   break;
                         default:  printf("Erreur de saisie !");
                    }
                    break;

          case '3' : printf("Entrez le nom du profil à transitionner: \n ");
                    scanf("%s",nom);
                    printf("Entrez le prénom du profil à transitionner: \n ");
                    scanf("%s",prenom);  
                    Transitionner_profil2(nom,prenom);
                    break;
          case '4' : printf("Entrez le nom du profil à supprimer: \n ");
                    scanf("%s",nom);
                    printf("Entrez le prénom du profil à supprimer: \n ");
                    scanf("%s",prenom);  
                    Supprimer_profil2(nom,prenom);
                    break;
          case '5' : printf("Vous voulez :\n");
                    printf("1. Rechercher par compétences \n");
                    printf("2. Rechercher par compétences et code postal \n");
                    scanf("%d",&choix2);
                    switch(choix2){
                         case 1:   printf("Entrez le nom du profil qui effectue la recherche: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil qui effectue la recherche: \n ");
                                   scanf("%s",prenom);
                                   Recherche_par_poste2(nom,prenom,1);
                                   break;
                         case 2:    printf("Entrez le nom du profil qui effectue la recherche: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil qui effectue la recherche: \n ");
                                   scanf("%s",prenom);
                                   Recherche_par_poste2(nom,prenom,2);
                                   break;
                         default:  printf("Erreur de saisie !");break;
                    }
                    break;
          case '6' : printf("Vous voulez :\n");
                    printf("1. Rechercher par entreprise \n");
                    printf("2. Rechercher par compétences \n");
                    scanf("%d",&choix2);
                    switch(choix2){
                         case 1:   printf("Entrez le nom du profil: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil : \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nom de l'entreprise : \n ");
                                   scanf("%s",entreprise);
                                   Rechercher_par_anciencollegue2(nom,prenom,entreprise,1);
                                   break;
                         case 2:    printf("Entrez le nom du profil qui effectue la recherche: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil qui effectue la recherche: \n ");
                                   scanf("%s",prenom);
                                   Rechercher_par_anciencollegue2(nom,prenom,"defaut",2);
                                   break;
                         default:  printf("Erreur de saisie !");break;
                    }
                    break;
          case 'p' :printf("Retour au menu précédent \n"); debug = getchar(); printf("%c", debug);
                    menuPrincipal(); break;
          case 'q' : printf("FERMETURE ... \n"); break;
    }

}

void menuChercheurEmploi(void){
     char choix1;
     int choix2;
     char debug=' ';

     char nom[128] = {0};
     char prenom[128]= {0};
     char mail[128]= {0};
     char code_postal[128]= {0};
     char competence[128]= {0}; 
     char collegue[128]= {0}; 
     char entreprise[128]= {0};

     printf("\n");
     printf("----------------------------------------------------\n");
     printf("-------------- Menu Chercheur d'emploi -------------\n");
     printf("----------------------------------------------------\n");


     printf("Vous voulez :\n");
     printf("1. Créer un profil \n");
     printf("2. Modifier un profil \n");
     printf("3. Transitionner le profil de «chercheur d'emploi» à un profil «employé» \n");
     printf("4. Supprimer un profil \n");
     printf("5. Rechercher parmi les les postes à pourvoir qui correspondent à son profil\n");
     printf("6. Rechercher parmi les anciens collègues \n");
     printf("\n");
     printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : \n");

     choix1 = getchar();
     switch(choix1){ 
          case '1' : printf("Entrez les données suivantes : \n");
                    printf("Le nom du chercheur d'emploi : \n ");
                    scanf("%s",nom);
                    printf("Le Prénom du chercheur d'emploi : \n ");
                    scanf("%s",prenom);
                    printf("L'adresse mail du chercheur d'emploi : \n ");
                    scanf("%s",mail);
                    printf("Le code postal du chercheur d'emploi : \n ");
                    scanf("%s",code_postal);
                    printf("Les compétences du chercheur d'emploi (séparez les différentes compétences par des ;) : \n ");
                    scanf("%s",competence);
                    printf("Le nom et prénom du collegue du chercheur d'emploi : \n ");
                    scanf("%s",collegue);
                    printf("L'entreprise du chercheur d'emploi : \n ");
                    scanf("%s",entreprise);
                    Creer_profil(nom,prenom,mail,code_postal,competence,collegue);
                    break;

          case '2' : printf("Vous voulez :\n");
                    printf("1. Ajouter des compétences \n");
                    printf("2. Ajouter un(e) ancien(ne) collègue de travail \n");
                    printf("3. Modifier le code postal \n");
                    scanf("%d",&choix2);
                    switch(choix2){
                         case 1:   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez la compétence à ajouter: \n ");
                                   scanf("%s",competence);
                                   Modifier_profil(nom,prenom,competence,"defaut","defaut",1);
                                   break;
                         case 2:   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nom et prénom du collègue à ajouter(ex : nom,prenom ): \n ");
                                   scanf("%s",collegue);
                                   Modifier_profil(nom,prenom,"defaut",collegue,"defaut",2);
                                   break;
                         case 3:   printf("Entrez le nom du profil à modifier: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil à modifier: \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nouveau code postal : \n ");
                                   scanf("%s",code_postal);
                                   Modifier_profil(nom,prenom,"defaut","defaut",code_postal,3);
                                   break;
                         default:  printf("Erreur de saisie !");
                    }
                    break;

          case '3' : printf("Entrez le nom du profil à transitionner: \n ");
                    scanf("%s",nom);
                    printf("Entrez le prénom du profil à transitionner: \n ");
                    scanf("%s",prenom); 
                    printf("Entrez l'entreprise à transitionner: \n ");
                    scanf("%s",entreprise);  
                    Transitionner_profil(nom,prenom,entreprise);
                    break;
          case '4' : printf("Entrez le nom du profil à supprimer: \n ");
                    scanf("%s",nom);
                    printf("Entrez le prénom du profil à supprimer: \n ");
                    scanf("%s",prenom);  
                    Supprimer_profil(nom,prenom);
                    break;
          case '5' : printf("Vous voulez :\n");
                    printf("1. Rechercher par compétences \n");
                    printf("2. Rechercher par compétences et code postal \n");
                    scanf("%d",&choix2);
                    switch(choix2){
                         case 1:   printf("Entrez le nom du profil qui effectue la recherche: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil qui effectue la recherche: \n ");
                                   scanf("%s",prenom);
                                   Recherche_par_poste(nom,prenom,1);
                                   break;
                         case 2:    printf("Entrez le nom du profil qui effectue la recherche: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil qui effectue la recherche: \n ");
                                   scanf("%s",prenom);
                                   Recherche_par_poste(nom,prenom,2);
                                   break;
                         default:  printf("Erreur de saisie !");break;
                    }
                    break;
          case '6' : printf("Vous voulez :\n");
                    printf("1. Rechercher par entreprise \n");
                    printf("2. Rechercher par compétences \n");
                    scanf("%d",&choix2);
                    switch(choix2){
                         case 1:   printf("Entrez le nom du profil: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil : \n ");
                                   scanf("%s",prenom);
                                   printf("Entrez le nom de l'entreprise : \n ");
                                   scanf("%s",entreprise);
                                   Rechercher_par_anciencollegue(nom,prenom,entreprise,1);
                                   break;
                         case 2:    printf("Entrez le nom du profil qui effectue la recherche: \n ");
                                   scanf("%s",nom);
                                   printf("Entrez le prénom du profil qui effectue la recherche: \n ");
                                   scanf("%s",prenom);
                                   Rechercher_par_anciencollegue(nom,prenom,"defaut",2);
                                   break;
                         default:  printf("Erreur de saisie !");break;
                    }
                    break;
          case 'p' :printf("Retour au menu précédent \n"); debug = getchar(); printf("%c", debug);
                    menuPrincipal(); break;
          case 'q' : printf("FERMETURE ... \n"); break;
    }

}

int main()
{    
     menuPrincipal();
     return 0;
}