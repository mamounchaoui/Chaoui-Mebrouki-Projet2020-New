
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
     FILE *db2 = fopen("test/employe.csv", "r");
     FILE *db3 = fopen("test/poste.csv", "r");
     FILE *db4 = fopen("test/entreprise.csv", "r");
     // tests pour 'entreprise'

     // // tests pour 'chercheurdemploi'
     // tests nbrligne

     TEST(nbrligne(db1) == 4);
     TEST(nbrligne(db2) == 4);
     TEST(nbrligne(db3) == 5);
     TEST(nbrligne(db4) == 5);

     // tests Creer_profil
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
     // tests pour 'employe'

     fclose(db1);
     fclose(db2);
     fclose(db3);
     fclose(db4);

     printf("%d/%d\n", tests_reussis, tests_executes);

     return tests_executes - tests_reussis;
}