
#include "chercheurdemploi.h"
#include "employe.h"
#include "entreprise.h"
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int tests_executes = 0;

int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)


#define TEST(x) tests_executes += 1;    \
                if(x)                   \
                {                       \
                    tests_reussis += 1; \
                    printf("[SUCCES] ");\
                }                       \
                else                    \
                {                       \
                    printf("[ECHEC ] ");\
                }                       \
                printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");


void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("[SEGFAULT]\n");
    printf("%d/%d\n", tests_reussis, tests_executes);
    exit(tests_reussis - tests_executes);
}

int main()
{
     FILE *db1 = fopen("test/chercheurdemploi.csv", "r");
     FILE *db3 = fopen("test/employe.csv", "r");
     FILE *db4 = fopen("test/entreprise.csv", "r");
     FILE *db5 = fopen("test/poste.csv", "r");
     // tests pour 'entreprise'

     // // tests pour 'chercheurdemploi'
     // tests nbrligne

     TEST(nbrligne(db1) == 4);
     TEST(nbrligne(db3) == 4);
     TEST(nbrligne(db4) == 5);
     TEST(nbrligne(db5) == 5);

     // // tests Creer_profil
     {
     int a;
     char nom[128]="Balança";
     char prenom[128]="Maxime";
     char mail[128]="maxbalança65@gmail.com";
     char code_postal[128]="33003";
     char competence[128]="theatre";
     char ancien_collegue[128]="Bartaire,Adrien";
     char str[128];
     char* v1,*v2,*v3,*v4,*v5,*v6,*v7;
     Creer_profil(nom, prenom, mail, code_postal, competence, ancien_collegue);
     
     a=nbrligne(db1);
     fseek(db1,0,SEEK_SET);
     fscanf(db1,"%*s");
     for (int i = 0; i <= a+1; i++)
     {
          fscanf(db1,"%s",str);
     }
     
     v1=strtok(str,",");
     v2=strtok(NULL,",");
     v3=strtok(NULL,",");
     v4=strtok(NULL,",");
     v5=strtok(NULL,",");
     v6=strtok(NULL,",");
     v7=strtok(NULL,",");
     
     TEST(strcmp(v1, "4") == 0);
     TEST(strcmp(v2, "Balança") == 0);
     TEST(strcmp(v3, "Maxime") == 0);
     TEST(strcmp(v4, "maxbalança65@gmail.com") == 0);
     TEST(strcmp(v5, "33003") == 0);
     TEST(strcmp(v6, "theatre") == 0);
     TEST(strcmp(v7, "1") == 0);
     fclose(db1);
     }

     // test de Modifier_profil
     {
          int x,y,z;
          char n3[128]="Dupont";
          char p3[128]="Michel";
          char n4[128]="Devathaire";
          char p4[128]="Emannuel";
          char n5[128]="Defritsh";
          char p5[128]="Gaetan";
          char compe[128]="Java";
          char col[128]="Bartaire,Adrien";
          char code[128]="12345";
          char str[128];
          char* x1,*x2,*x3,*x4,*x5,*x6,*x7;
          // 1-Ajouter des compétences
          // 2-Ajouter un(e) ancien(ne) collègue de travail
          // 3-Modifier le code postal
          x=1;
          y=2;
          z=3;

          Modifier_profil(n3, p3, compe, col, code, z);
          Modifier_profil(n4, p4, compe, col, code, x);
          Modifier_profil(n5, p5, compe, col, code, y);
          FILE *db9 = fopen("test/chercheurdemploi.csv", "r");

          fscanf(db9,"%*s");
          fscanf(db9,"%s",str);
          x1=strtok(str,",");
          x2=strtok(NULL,",");
          x3=strtok(NULL,",");
          x4=strtok(NULL,",");
          x5=strtok(NULL,",");
          x6=strtok(NULL,",");
          x7=strtok(NULL,",");
          
          TEST(strcmp(x1, "1") == 0);
          TEST(strcmp(x2, "Dupont") == 0);
          TEST(strcmp(x3, "Michel") == 0);
          TEST(strcmp(x4, "dup.michel@gmail.com") == 0);
          TEST(strcmp(x5, "12345") == 0);
          TEST(strcmp(x6, "bureatique") == 0);
          TEST(strcmp(x7, "2;1") == 0);

          fscanf(db9,"%s",str);
          x1=strtok(str,",");
          x2=strtok(NULL,",");
          x3=strtok(NULL,",");
          x4=strtok(NULL,",");
          x5=strtok(NULL,",");
          x6=strtok(NULL,",");
          x7=strtok(NULL,",");
          
          TEST(strcmp(x1, "2") == 0);
          TEST(strcmp(x2, "Devathaire") == 0);
          TEST(strcmp(x3, "Emannuel") == 0);
          TEST(strcmp(x4, "eannueldev@yahoo.fr") == 0);
          TEST(strcmp(x5, "13005") == 0);
          TEST(strcmp(x6, "CSS;HTML;JS;Java") == 0);
          TEST(strcmp(x7, "1") == 0);

          fscanf(db9,"%s",str);
          x1=strtok(str,",");
          x2=strtok(NULL,",");
          x3=strtok(NULL,",");
          x4=strtok(NULL,",");
          x5=strtok(NULL,",");
          x6=strtok(NULL,",");
          x7=strtok(NULL,",");
          // 3,Defritsh,Gaetan,defgaetan98@hotmail.fr,33003,theatre,3
          TEST(strcmp(x1, "3") == 0);
          TEST(strcmp(x2, "Defritsh") == 0);
          TEST(strcmp(x3, "Gaetan") == 0);
          TEST(strcmp(x4, "defgaetan98@hotmail.fr") == 0);
          TEST(strcmp(x5, "33003") == 0);
          TEST(strcmp(x6, "theatre") == 0);
          TEST(strcmp(x7, "3;1") == 0);
          fclose(db9);
     }
     
     // test de Supprimer_profil
     {
     char n[128]="Dupont";
     char p[128]="Michel";
     char str[128];
     char* w1,*w2;
     int b;
     
     Supprimer_profil(n, p);
     FILE *db2 = fopen("test/chercheurdemploi.csv", "r");

     b=nbrligne(db2);
     fseek(db2,0,SEEK_SET);
     fscanf(db2,"%*s");
     for (int i = 0; i < b-1; i++)
     {
          fscanf(db2,"%s",str);
          w1=strtok(str,",");
          w1=strtok(NULL,",");
          w2=strtok(NULL,",");
          TEST(strcmp(w1, "Dupont") != 0);
          TEST(strcmp(w2, "Michel") != 0);
     }
     fclose(db2);

     char n1[128]="Devathaire";
     char p1[128]="Emannuel";

     Supprimer_profil(n1, p1);
     FILE *db6 = fopen("test/chercheurdemploi.csv", "r");

     b=nbrligne(db6);
     fseek(db6,0,SEEK_SET);
     fscanf(db6,"%*s");
     for (int i = 0; i < b-1; i++)
     {
          fscanf(db6,"%s",str);
          w1=strtok(str,",");
          w1=strtok(NULL,",");
          w2=strtok(NULL,",");
          TEST(strcmp(w1, "Devathaire") != 0);
          TEST(strcmp(w2, "Emannuel") != 0);
     }
     fclose(db6);
     }

     // tests de Transitionner_profil
     {
     int c ,d;
     char n2[128]="Defritsh";
     char p2[128]="Gaetan";
     char entrep[128]="Disney";
     char* w1,*w2,*w3,*w4,*w5,*w6,*w7,*w8;
     char str[128];

     Transitionner_profil(n2, p2, entrep);

     FILE *db7 = fopen("test/chercheurdemploi.csv", "r");
     FILE *db8 = fopen("test/employe.csv", "r");
     c=nbrligne(db7);
     d=nbrligne(db8);
     fseek(db7,0,SEEK_SET);
     fseek(db8,0,SEEK_SET);

     fscanf(db7,"%*s");
     for (int i = 0; i < c-1; i++)
     {
          fscanf(db7,"%s",str);
          w1=strtok(str,",");
          w1=strtok(NULL,",");
          w2=strtok(NULL,",");
          TEST(strcmp(w1, "Defritsh") != 0);
          TEST(strcmp(w2, "Gaetan") != 0);
     }

     fscanf(db8,"%*s");
     for (int i = 0; i <=d+1; i++)
     {
          fscanf(db8,"%s",str);
     }
     w1=strtok(str,",");
     w2=strtok(NULL,",");
     w3=strtok(NULL,",");
     w4=strtok(NULL,",");
     w5=strtok(NULL,",");
     w6=strtok(NULL,",");
     w7=strtok(NULL,",");
     w8=strtok(NULL,",");

     TEST(strcmp(w1, "4") == 0);
     TEST(strcmp(w2, "Defritsh") == 0);
     TEST(strcmp(w3, "Gaetan") == 0);
     TEST(strcmp(w4, "defgaetan98@hotmail.fr") == 0);
     TEST(strcmp(w5, "33003") == 0);
     TEST(strcmp(w6, "theatre") == 0);
     TEST(strcmp(w7, "3;1") == 0);
     TEST(strcmp(w8, "1") == 0);
     fclose(db7);
     fclose(db8);
     }

     
     {

          char nom[128]="Dupont";
          char prenom[128]="Emannuel";
          char mail[128]="dup.michel@gmail.com";
          char code_postal[128]="67940";
          char competence[128]="bureatique";
          char ancien_collegue[128]="Buisson,Hugo";

          char nom1[128]="Devathaire";
          char prenom1[128]="Michel";
          char mail1[128]="eannueldev@yahoo.fr";
          char code_postal1[128]="13005";
          char competence1[128]="CSS;HTML;JS";
          char ancien_collegue1[128]="Bartaire,Adrien";
          // 3,Defritsh,Gaetan,defgaetan98@hotmail.fr,33003,theatre,3
          char nom2[128]="Defritsh";
          char prenom2[128]="Gaetan";
          char mail2[128]="defgaetan98@hotmail.fr";
          char code_postal2[128]="77700";
          char competence2[128]="theatre;comedie";
          char ancien_collegue2[128]="Bouvier,Rodolphe";
          Creer_profil(nom, prenom, mail, code_postal, competence, ancien_collegue);
          Creer_profil(nom1, prenom1, mail1, code_postal1, competence1, ancien_collegue1);
          Creer_profil(nom2, prenom2, mail2, code_postal2, competence2, ancien_collegue2);
     }

     // test Recherche_par_poste
     {
          char nom[128]="Dupont";
          char prenom[128]="Michel";
          int a,b;
          a=1;
          b=2;

     Recherche_par_poste(nom, prenom, a);
     // résultat obtenu:aucun résultat obtenu (résultat voulu)

     char nom1[128]="Devathaire";
     char prenom1[128]="Emannuel";
     Recherche_par_poste(nom1, prenom1, a);
     // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)

     char nom2[128]="Defritsh";
     char prenom2[128]="Gaetan";
     Recherche_par_poste(nom2, prenom2, a);
     // résultat obtenu: (corresspont au résultat voulu)
     // Voici le(s) résultat(s) de votre recherche
     // le titre du poste est:acteur
     // le nom de l'entreprise:Disney
     // l'adresse mail de l'entreprise est:walt@disney.com
     // le code postal de l'entreprise est:77700
     // ---------------------------------------
     // le titre du poste est:comedien
     // le nom de l'entreprise:Twitter
     // l'adresse mail de l'entreprise est:emps@google.com
     // le code postal de l'entreprise est:75029
     // ---------------------------------------
     // le titre du poste est:humouriste
     // le nom de l'entreprise:Comedieclub
     // l'adresse mail de l'entreprise est:comclub@yahoo.fr
     // le code postal de l'entreprise est:77700
     // ---------------------------------------

     Recherche_par_poste(nom2, prenom2, b);
     // résultat obtenu: (corresspont au résultat voulu)
     // Voici le(s) résultat(s) de votre recherche
     // le titre du poste est:acteur
     // le nom de l'entreprise:Disney
     // l'adresse mail de l'entreprise est:walt@disney.com
     // le code postal de l'entreprise est:77700
     // ---------------------------------------
     // le titre du poste est:humouriste
     // le nom de l'entreprise:Comedieclub
     // l'adresse mail de l'entreprise est:comclub@yahoo.fr
     // le code postal de l'entreprise est:77700
     // ---------------------------------------
     Recherche_par_poste(nom, prenom, b);
     // résultat obtenu: (corresspont au résultat voulu)
     // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
     }
     // tests pour 'employe'

     
     fclose(db3);
     fclose(db4);
     fclose(db5);

     printf("%d/%d\n", tests_reussis, tests_executes);

     return tests_executes - tests_reussis;

}