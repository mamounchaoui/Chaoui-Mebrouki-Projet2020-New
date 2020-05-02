
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

     // test de Supprimer_profil()
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

     // tests de Tronsitionner_profil
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
     TEST(strcmp(w7, "3") == 0);
     TEST(strcmp(w8, "1") == 0);
     fclose(db7);
     fclose(db8);
     }
     // tests pour 'employe'

     
     // fclose(db3);
     // fclose(db4);
     // fclose(db5);

     printf("%d/%d\n", tests_reussis, tests_executes);

     return tests_executes - tests_reussis;
}