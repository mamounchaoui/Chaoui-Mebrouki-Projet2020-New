#include "chercheurdemploi.h"
#include "employe.h"
#include "entreprise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuEnt(void);
void menuPrincipal(void);
void choixRecherche(void);

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
     char choisir=' ';
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
          case '1' : choisir = getchar(); printf("%c", choisir); // ca bug donc je fais ca
                    menuEnt();
                    break;
          case '2' : break;
          case '3' : break;
          case 'q' : printf("FERMETURE ... \n"); break;
    }

}

int main()
{    
     menuPrincipal();
     return 0;
}