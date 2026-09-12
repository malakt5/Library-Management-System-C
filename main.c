

Conversations
11 % sur 15 Go utilisés
Conditions d'utilisation · Confidentialité · Règlement du programme
Dernière activité sur le compte : il y a 7 heures
Détails
ibtissem. Appuyez sur Tabulation pour insérer.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LIVRE 200
#define nb_initial 20
#define MAX_EMPRUNTS 400
#define MAX_EMPRUNT 7
int n=nb_initial,nEmprunt=nb_initial;

/*initialisation des tableaux*/
int T_NLivre[MAX_LIVRE] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20
};

char T_Titre[MAX_LIVRE][50] = {
    "Le Petit Prince",
    "L'Etranger",
    "Les Miserables",
    "Madame Bovary",
    "Germinal",
    "Candide",
    "Le Rouge et le Noir",
    "Bel-Ami",
    "Notre-Dame de Paris",
    "La Peste",
    "Le Comte de Monte-Cristo",
    "Le Pere Goriot",
    "L'Assommoir",
    "Les Fleurs du mal",
    "La Condition humaine",
    "La Chartreuse de Parme",
    "Voyage au centre de la Terre",
    "Vingt mille lieues sous les mers",
    "L'Ile mysterieuse",
    "Les Trois Mousquetaires"
};

int T_Nbr_exp[MAX_LIVRE] = {
    10, 15, 8, 6, 5,
    12, 7, 18, 9, 11,
    14, 6, 13, 8, 10,
    13, 16, 7, 9, 12
};
/*initialisation de la matrice des emprunts des livres*/
int T_Emprunts[MAX_EMPRUNTS][8] = {
    /*   N_CIN   N_livre  J1  M1   A1     J2  M2   A2*/
    {01234567,     1,     5,  1, 2019,   25,  1, 2020},
    {11223344,     3,    12,  2, 2020,   10,  3, 2020},
    {10293847,     7,    25,  3, 2020,   24,  4, 2020},
    {03776543,    12,    14,  4, 2021,   12,  5, 2021},
    {10928374,    20,     3,  5, 2021,    2,  6, 2021},
    {12340001,     8,    29,  6, 2021,   28,  7, 2021},
    {10101010,    15,    10,  8, 2022,    9,  9, 2022},
    {01122334,     4,    17,  9, 2022,   16, 10, 2022},
    {10887766,     9,    21, 10, 2022,   20, 11, 2022},
    {01235576,    13,     2, 11, 2022,    1, 12, 2022},
    {10990011,    19,    12, 12, 2022,   11,  1, 2023},
    {10004567,    16,     5,  1, 2023,    4,  2, 2023},
    {01020304,     2,    13,  2, 2023,   13,  3, 2023},
    {12345678,     5,    28,  3, 2023,   27,  4, 2023},
    {10293847,    10,     7,  5, 2023,    6,  6, 2023},
    {01110022,    17,    16,  6, 2023,   15,  7, 2023},
    {10998877,    11,    20,  8, 2024,   19,  9, 2024},
    {01220447,     6,    10, 10, 2024,    9, 11, 2024},
    {12344321,    14,     5,  1, 2025,    4,  2, 2025},
    {10000001,    11,    28,  3, 2025,   27,  4, 2025}
};
/*les fonctions a utiliser*/
int recherche(char tab[][50],int taille,char titre[50]){
    int i=0,res=-1;
    while(i<taille&&res==-1){
        if (strcasecmp(tab[i],titre)==0){
            res=i;
        }
        else i++;
    }
    return res;
}
int rechercheNum(int tab[],int taille,int num){
    int i=0,res=-1;
    while(i<taille&&res==-1){
        if (tab[i]==num){
            res=i;
        }
        else i++;
    }
    return res;
}
bool dateSup(int jj1,int mm1,int aa1,int jj2,int mm2,int aa2){
    return(aa1 > aa2) ||
           (aa1 == aa2 && mm1 > mm2) ||
           (aa1 == aa2 && mm1 == mm2 && jj1 >= jj2);
}
int rechercheDateIntervalle(int jj,int mm,int aa,int t[][8],int i0,int taille){
    int res=-1,i=i0;
    while(i<taille&&res==-1){
        if(dateSup(jj,mm,aa,t[i][2],t[i][3],t[i][4])&&dateSup(t[i][5],t[i][6],t[i][7],jj,mm,aa))res=i;
        i++;
    }
    return res;
}
bool estNumerique(char ch[50],int taille){
    int i=0;
    bool res=true;
    while(i<taille&&res){
        if(!isdigit(ch[i])) res=false;
        i++;
    }
    return res;

}
bool estBissextile(int aa) {
    return (aa % 4 == 0 && aa % 100 != 0) || (aa % 400 == 0);
}
bool dateValide(int aa1,int jj, int mm, int aa) {
    bool valide = true;
    if (aa < aa1)/*a1 est l'année a partir de laquelle on va accepter le saisi*/
        valide = false;
    else if (mm < 1 || mm > 12)
        valide = false;
    else if (jj < 1)
        valide = false;
    else {
        int joursParMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31,30, 31};
        if (mm == 2) {
            if (estBissextile(aa)) {
                if (jj > 29) valide = false;
            } else {
                if (jj > 28) valide = false;
            }
        }
        else {
            if (jj > joursParMois[mm-1])
                valide = false;
        }
    }
    return valide;
}
int rechercheMatrice(int M[][8],int taille,int colonnex,int colonney,int x,int y){
    int res=-1,i=0,j;
    while(i<taille && res==-1){
        if(M[i][colonnex]==x&&M[i][colonney]==y)res=i;
        i++;
    }
    return res;
}
int compterOccurrence(int M[][8],int taille,int col,int indice){
    int nbOc=1,j;
    for(j=indice+1;j<taille;j++){
        if(M[indice][col]==M[j][col])nbOc++;
    }
    return nbOc;
}
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/*les fonctions sans code de retour*/
void gestion_biblio();
void gestion_emprunts();
void stat();
void au_revoir();
void interface_menu(){
    system("cls");
    printf(" ================================================================================================================= \n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------- BIENVENUE DANS LE MENU PRINCIPAL DE LA BIBLIOTHEQUE -------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------     Veuillez choisir     ----------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                        1. GESTION DE LA BIBLIOTHEQUE                                         ||\n");
    printf("||                                        2. GESTION DES EMPRUNTS                                               ||\n");
    printf("||                                        3. STATISTIQUES                                                       ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                        4. QUITTER L'APPLICATION                                              ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("==================================================================================================================\n");


    int choix;
    do{
        printf("\n Veuillez choisir une option: ");
        scanf("%d",&choix);
    }while(choix!=1&&choix!=2&&choix!=3&&choix!=4);
    switch(choix)
    {
        case 1:
            gestion_biblio();
        break;
        case 2:
            gestion_emprunts();
        break;
        case 3:
            stat();
        break;
        case 4:
            au_revoir();
        break;
    }
}
void retour_menu(){
    int retour;
    do{
        printf("Voulez-vous retourner au menu principal? 1:Oui 2:Non ");
        scanf("%d",&retour);
    }while(retour!=1&&retour!=2);
    if(retour==1) interface_menu();
    else au_revoir();
}
void au_revoir(){
    system("cls");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                   AU REVOIR!                                                 ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
}
void gestion_biblio(){
    system("cls");
    printf(" ================================================================================================================= \n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------       GESTION DE LA BIBILOTHEQUE        --------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------     Veuillez choisir     ----------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                        1. AFFICHER TOUS LES LIVRES DE LA BIBLIOTHEQUE                        ||\n");
    printf("||                                        2. AJOUTER UN NOUVEAU LIVRE                                           ||\n");
    printf("||                                        3. SUPPRIMER UN LIVRE                                                 ||\n");
    printf("||                                        4. MODIFIER LE NOMBRE D'EXEMPLAIRE D'UN LIVRE                         ||\n");
    printf("||                                        5. RECHERCHER UN LIVRE                                                ||\n");
    printf("||                                        6. AFFICHER LES LIVRES DISPONIBLES                                    ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                        7. MENU PRINCIPAL                                                     ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("==================================================================================================================\n");


    int choix_g,i;
    do{
        printf("\n Veuillez choisir une option: ");
        scanf("%d",&choix_g);
    }while(choix_g!=1&&choix_g!=2&&choix_g!=3&&choix_g!=4&&choix_g!=5&&choix_g!=6&&choix_g!=7);
    switch(choix_g){
        case 1:
            /* QUESTION 1 :AFFICHER TOUS LES LIVRES DE LA BIBLIOTHEQUE  */

            if ( T_NLivre[0]==0){
                printf("\n aucun livre enregistre\n");
            }
            else{
                printf("la liste des livres de bibiliotheque est :\n");
                for(i=0;i< n;i++) {
                    printf("numero:%d|titre:%s|exemplaires:%d\n", T_NLivre[i],T_Titre[i],T_Nbr_exp[i]);
                }
            }
            retour_menu();
        break;
        case 2:
            /*QUESTION 2 : AJOUTER UN NOUVEAU LIVRE*/
            n++;
            do{
                printf("Entrez le titre de livre: ");
                scanf(" %[^\n]",T_Titre[n-1]);
            }while(recherche(T_Titre,n-1,T_Titre[n-1])!=-1);
            printf("Entrez le nombre d'exemplaires: ");
            scanf("%d",&T_Nbr_exp[n-1]);
            T_NLivre[n-1]=n;
            printf("\n Livre ajoute avec succes!\n");
            retour_menu();

        break;
        case 3:{
            /*QUESTION 3 : SUPPRIMER UN LIVRE */
            char titre[50];
            do{
                printf("donner le titre du livre a supprimer: ");
                scanf(" %[^\n]",titre);
                i=recherche(T_Titre,n,titre);
            }while (i==-1);

            int j;
            for(j=i;j<n-1;j++){
                T_NLivre[j]=T_NLivre[j+1];
                strncpy(T_Titre[j], T_Titre[j+1], 49);
                T_Titre[j][49] = '\0';
                T_Nbr_exp[j]=T_Nbr_exp[j+1];
            }
            T_NLivre[n-1]=0;
            T_Titre[n-1][0]='\0';
            T_Nbr_exp[n-1]=0;
            n--;
            printf("livre supprime avec succes!\n");

            retour_menu();
        break;
        }
        case 4:{
            /*QUESTION 4 :MODIFIER LE NOMBRE D'EXEMPLAIRE D'UN LIVRE */
            char titre[50];
            int nb;
            do{
                printf("donner le titre: ");
                scanf(" %[^\n]",titre);
                i=recherche(T_Titre,n,titre);
            }while (i==-1);
            printf("donner le nouveau nombre d'exemplaires: ");
            scanf("%d",&nb);
            T_Nbr_exp[i]=nb;
            printf("nombre d'exmpelaires modifie avec succes!\n");

            retour_menu();
        break;
        }
        case 5:{
            /*QUESTION 5 : Rechercher un livre*/
            char titre[50];
            printf("donner le titre a chercher: ");
            scanf(" %[^\n]",titre);
            int i=recherche(T_Titre,n,titre);
            if (i==-1) printf("livre inexistant\n");
            else printf("%s existe sous le numero %d avec %d exemplaires\n",T_Titre[i],T_NLivre[i],T_Nbr_exp[i]);

            retour_menu();

        break;
        }
        case 6:
            /*QUESTION 6 : AFFICHER LES LIVRES DISPONIBLES*/
            for(i=0;i<n;i++) {
                    if (T_Nbr_exp[i]>0)printf("numero:%d|titre:%s|exemplaires:%d\n", T_NLivre[i],T_Titre[i],T_Nbr_exp[i]);
                }
            retour_menu();
        break;

        case 7:
           interface_menu();
        break;

    }
}


void gestion_emprunts(){
    system("cls");
    printf(" ================================================================================================================= \n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------          GESTION DES EMPRUNTS          ---------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------     Veuillez choisir     ----------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                        1. AJOUTER UN EMPRUNT                                                 ||\n");
    printf("||                                        2. CONSULTER LES EMPRUNTS D'UN ADHERENT                               ||\n");
    printf("||                                        3. ENREGISTRER LE RETOUR D'UN LIVRE                                   ||\n");
    printf("||                                        4. AFFICHER LA LISTE DES RMPRUNTS EN COURS                            ||\n");
    printf("||                                        5. AFFICHER LES LIVRES EN RETARD DE RETOUR                            ||\n");
    printf("||                                        6. AFFICHER LES EMPRUNTS RELATIFS A UNE DATE DE RETOUR PREVU          ||\n");
    printf("||                                        7. SUPPRIMER UN ENSEMBLE D'EMPRUNTS                                   ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                        8. MENU PRINCIPAL                                                     ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("==================================================================================================================\n");


    int choix_e,i;
    do{
        printf("\n Veuillez choisir une option: ");
        scanf("%d",&choix_e);
    }while(choix_e!=1&&choix_e!=2&&choix_e!=3&&choix_e!=4&choix_e!=5&&choix_e!=6&&choix_e!=7&&choix_e!=8);
    switch(choix_e){
        case 1:{
            /*Question 1: AJOUT D'UN EMPRUNT*/
            char cin[9],titre[50],date1[11],date2[11],j1[3],m1[3],a1[5],j2[3],m2[3],a2[5];
            int k;
            int jj1,mm1,aa1,jj2,mm2,aa2,jM,mM,aM,nEmp;
            do{
                printf("Entrez le CIN de l'adherent : ");
                scanf("%s",cin);
            }while(strlen(cin)!=8||!estNumerique(cin,8));
            /*verification du nombre d'emprunt pour cet adherent*/
            for(i=0;i<nEmprunt;i++){
                if(T_Emprunts[i][0]==atoi(cin))nEmp++;
            }
            if(nEmp>=MAX_EMPRUNT) printf("Vous avez atteint le nombre maximal d'emprunts!\n");
            else{
                do{
                    printf("donner le titre du livre a emprunter: ");
                    scanf(" %[^\n]",titre);
                    k=recherche(T_Titre,n,titre);
                }while(k==-1);
                do{
                    viderBuffer();
                    printf("Entrez la date d'emprunt (jj/mm/aaaa) : ");
                    fgets(date1,11,stdin);
                    date1[strcspn(date1, "\n")] = '\0';
                    strncpy(j1, date1,2);
                    j1[2] = '\0';
                    strncpy(m1, date1+3,2);
                    m1[2] = '\0';
                    strncpy(a1, date1+6,4);
                    a1[4] = '\0';
                    jj1 = atoi(j1);
                    mm1 = atoi(m1);
                    aa1 = atoi(a1);
                }while(date1[2]!='/'||date1[5]!='/'||!estNumerique(j1,2)||!estNumerique(m1,2)||!estNumerique(a1,4)||!dateValide(2025,jj1,mm1,aa1));
            /*ajout d'un mois pour obtenir la date de retour maximale jM/mM/aM)*/
                if(mm1==12){
                    jM=jj1;
                    mM=1;
                    aM=aa1+1;
                }
                else{
                    jM=jj1;
                    mM=mm1+1;
                    aM=aa1;
                }
                do {
                    viderBuffer();
                    printf("Entrez la date de retour prevue(jj/mm/aaaa): ");
                    fgets(date2,11,stdin);
                    date2[strcspn(date2, "\n")] = '\0';
                    strncpy(j2, date2,2);
                    j2[2]='\0';
                    strncpy(m2,date2+3,2);
                    m2[2]='\0';
                    strncpy(a2,date2+6,4);
                    a2[4]='\0';
                    jj2=atoi(j2);
                    mm2=atoi(m2);
                    aa2= atoi(a2);
                }while(date2[2]!='/'||date2[5]!='/'||!estNumerique(j2,2)||!estNumerique(m2,2)||!estNumerique(a2,4)||!dateValide(2025,jj2,mm2,aa2)||!dateSup(jj2,mm2,aa2,jj1,mm1,aa1)||!dateSup(jM,mM,aM,jj2,mm2,aa2));
                T_Emprunts[nEmprunt][0] = atoi(cin);
                T_Emprunts[nEmprunt][1] = T_NLivre[k];
                T_Emprunts[nEmprunt][2] = jj1;
                T_Emprunts[nEmprunt][3] = mm1;
                T_Emprunts[nEmprunt][4] = aa1;
                T_Emprunts[nEmprunt][5] = jj2;
                T_Emprunts[nEmprunt][6] = mm2;
                T_Emprunts[nEmprunt][7] = aa2;
                nEmprunt++;
                T_Nbr_exp[k]--;
                printf("Emprunt ajoute avec succes !\n");
            }
            retour_menu();

        break;
        }
        case 2:{
            /*Question 2: CONSULTER LES EMPRUNTS D'UN ADHERENT*/
            char cin[9];
            bool existe=false;
            int k;
            do{
                printf("Entrez le CIN de l'adherent : ");
                scanf("%s",cin);
            }while(strlen(cin)!=8||!estNumerique(cin,8));
            printf("\nListe des emprunts pour l'adherent %s :\n", cin);
            for(i = 0; i < nEmprunt; i++) {
                if(T_Emprunts[i][0] == atoi(cin)) {
                    existe=true;
                    int numLivre = T_Emprunts[i][1];
                    k=rechercheNum(T_NLivre,n,numLivre);
                    printf("%s | numero : %d | Emprunte le : %02d/%02d/%04d | Retour prevu : %02d/%02d/%04d\n",T_Titre[k],T_Emprunts[i][1],T_Emprunts[i][2], T_Emprunts[i][3], T_Emprunts[i][4],T_Emprunts[i][5], T_Emprunts[i][6], T_Emprunts[i][7]);
                }

            }
            if(!existe)printf("Aucun!\n");
            retour_menu();
        break;
        }
        case 3:{
            /*Question 3: ENREGISTREMENT DU RETOUR D'UN LIVRE*/
            char cin[9],titre[50];
            int j,k,c;
            do{
                printf("Entrez le CIN de l'adherent : ");
                scanf("%s",cin);
                printf("donner le titre du livre a retourner: ");
                scanf(" %[^\n]",titre);
                i=recherche(T_Titre,n,titre);
                c=rechercheMatrice(T_Emprunts,nEmprunt,0,1,atoi(cin),T_NLivre[i]);
            }while(strlen(cin)!=8||!estNumerique(cin,8)||c==-1);
            T_Nbr_exp[i]++;
            for(k=c;k<nEmprunt-1;k++){
                      for(j=0;j<8;j++){
                      T_Emprunts[k][j]=T_Emprunts[k+1][j];
                    }
           }
           for(j=0;j<8;j++){
                T_Emprunts[nEmprunt-1][j]=0;
           }
           nEmprunt--;
           printf("retour enregistre avec succes!\n");
           retour_menu();
        break;
        }
        case 4:{
            /*Question 4:AFFICHAGE DES EMPRUNTS EN COURS*/
            char date[11],j[3],m[3],a[5];
            int jj,mm,aa,k;
            do{
                viderBuffer();
                printf("Entrez la date d'aujourd'hui (jj/mm/aaaa) : ");
                fgets(date,11,stdin);
                date[strcspn(date,"\n")]='\0';
                strncpy(j,date,2);
                j[2]='\0';
                strncpy(m,date+3,2);
                m[2]='\0';
                strncpy(a,date+6,4);
                a[4]='\0';
                jj=atoi(j);
                mm=atoi(m);
                aa=atoi(a);
            }while(date[2]!='/'||date[5]!='/'||!estNumerique(j,2)||!estNumerique(m,2)||!estNumerique(a,4)||!dateValide(2019,jj,mm,aa));
            int i=rechercheDateIntervalle(jj,mm,aa,T_Emprunts,0,nEmprunt);
            if (i==-1){
                printf("Aucun livre emprunte en cours!\n");
            }
            else{
                printf("Les livres empruntes en cours:\n");
                int i0=0;
                while(i!=-1){
                    k=rechercheNum(T_NLivre,n,T_Emprunts[i][1]);
                    printf("Livre : %s | numero: %d | CIN : %08d | Retour prevu le : %02d/%02d/%04d\n",T_Titre[k],T_NLivre[k],T_Emprunts[i][0],T_Emprunts[i][5],T_Emprunts[i][6],T_Emprunts[i][7]);
                    i0=i+1;
                    i=rechercheDateIntervalle(jj,mm,aa,T_Emprunts,i0,nEmprunt);

                }
            }
            retour_menu();
        break;
        }
        case 5:{
            /*Question 5: AFFICHER LES LIVRES EN RETARD DE RETOUR*/
            char date[11],j[3],m[3],a[5];
            int jj,mm,aa,k;
            bool retard;
            do{
                viderBuffer();
                printf("Entrez la date actuelle (jj/mm/aaaa) : ");
                fgets(date,11,stdin);
                date[strcspn(date,"\n")]='\0';
                strncpy(j,date,2);
                j[2]='\0';
                strncpy(m,date+3,2);
                m[2]='\0';
                strncpy(a,date+6,4);
                a[4]='\0';
                jj=atoi(j);
                mm=atoi(m);
                aa=atoi(a);
            }while(date[2]!='/'||date[5]!='/'||!estNumerique(j,2)||!estNumerique(m,2)||!estNumerique(a,4)||!dateValide(2019,jj,mm,aa));

            printf("\nLivres en retard au %02d/%02d/%04d :\n", jj, mm, aa);
            retard=false;
            for(i = 0; i < nEmprunt; i++) {
                int j2 = T_Emprunts[i][5];
                int m2= T_Emprunts[i][6];
                int a2 = T_Emprunts[i][7];
                /* Vérifie si la date actuelle dépasse la date de retour prévue */
                if(dateSup(jj,mm,aa,j2,m2,a2)) {
                    retard=true;
                    int numLivre = T_Emprunts[i][1];
                    k=rechercheNum(T_NLivre,n,numLivre);
                    printf("Livre : %s | numero: %d | CIN : %08d | Retour prevu le : %02d/%02d/%04d\n",T_Titre[k],numLivre, T_Emprunts[i][0], j2, m2, a2);
                }
            }
            if(!retard) printf("Aucun\n");
            retour_menu();
        break;
        }

        case 6:{
            /*Question 6: AFFICHAGE DE L'ENSEMBLE DES EMPRUNTS RELATIFS A UNE DATE DE RETOUR PREVU*/
            char date[11],j[3],m[3],a[5];
            int k,jj,mm,aa;
            do{
                viderBuffer();
                printf("Entrez la date d'aujourd'hui (jj/mm/aaaa) : ");
                fgets(date,11,stdin);
                date[strcspn(date,"\n")]='\0';
                strncpy(j,date,2);
                j[2]='\0';
                strncpy(m,date+3,2);
                m[2]='\0';
                strncpy(a,date+6,4);
                a[4]='\0';
                jj=atoi(j);
                mm=atoi(m);
                aa=atoi(a);
            }while(date[2]!='/'||date[5]!='/'||!estNumerique(j,2)||!estNumerique(m,2)||!estNumerique(a,4)||!dateValide(2019,jj,mm,aa));
            printf("L'ensemble des emprunts relatifs a %s\n",date);
            int nb=0;
            for(i=0;i<nEmprunt;i++){
                if((T_Emprunts[i][5]==jj&&T_Emprunts[i][6]==mm&&T_Emprunts[i][7]==aa)){
                    k=rechercheNum(T_NLivre,n,T_Emprunts[i][1]);
                    printf("Livre : %s | numero: %d | CIN : %08d | Retour prevu le : %02d/%02d/%04d\n",T_Titre[k],T_NLivre[i],T_Emprunts[i][0],T_Emprunts[i][5],T_Emprunts[i][6],T_Emprunts[i][7]);
                    nb++;
                }
            }
            if(!nb) printf("Aucun\n");
            retour_menu();
        break;
        }
        case 7:{
            /*QUESTION 7: SUPPRESSION DE L'ENSEMBLE DES EMPRUNTS APPARTENANT A UNE PERIODE DONNÉE*/
            char date1[11],date2[11],j1[3],m1[3],a1[5],j2[3],m2[3],a2[5];
            int jj1,mm1,aa1,jj2,mm2,aa2;
            int j,k,c,nSup=0;/*nSup est le nombre d'emprunts supprimés*/
            do{
                viderBuffer();
                printf("Entrez la date debut de periode (jj/mm/aaaa) : ");
                fgets(date1,11,stdin);
                date1[strcspn(date1,"\n")]='\0';
                strncpy(j1,date1,2);
                j1[2]='\0';
                strncpy(m1,date1+3,2);
                m1[2]='\0';
                strncpy(a1,date1+6,4);
                a1[4]='\0';
                jj1=atoi(j1);
                mm1=atoi(m1);
                aa1=atoi(a1);
            }while(date1[2]!='/'||date1[5]!='/'||!estNumerique(j1,2)||!estNumerique(m1,2)||!estNumerique(a1,4)||!dateValide(2019,jj1,mm1,aa1));
            do{
                viderBuffer();
                printf("Entrez la date de fin de periode (jj/mm/aaaa): ");
                fgets(date2,11,stdin);
                date2[strcspn(date2, "\n")] = '\0';
                strncpy(j2, date2,2);
                j2[2]='\0';
                strncpy(m2,date2+3,2);
                m2[2]='\0';
                strncpy(a2,date2+6,4);
                a2[4]='\0';
                jj2=atoi(j2);
                mm2=atoi(m2);
                aa2= atoi(a2);
            }while(date2[2]!='/'||date2[5]!='/'||!estNumerique(j2,2)||!estNumerique(m2,2)||!estNumerique(a2,4)||!dateValide(2019,jj2,mm2,aa2)||!dateSup(jj2,mm2,aa2,jj1,mm1,aa1));
            i=0;
            while(i<nEmprunt){
                if(dateSup(T_Emprunts[i][2],T_Emprunts[i][3],T_Emprunts[i][4],jj1,mm1,aa1)&&dateSup(jj2,mm2,aa2,T_Emprunts[i][5],T_Emprunts[i][6],T_Emprunts[i][7])){
                    k=rechercheNum(T_NLivre,n,T_Emprunts[i][1]);
                    T_Nbr_exp[k]++;
                   printf("Livre : %s | numero: %d | CIN : %08d | Retour prevu le : %02d/%02d/%04d supprime avec succes!\n",T_Titre[k],T_NLivre[k],T_Emprunts[i][0],T_Emprunts[i][5],T_Emprunts[i][6],T_Emprunts[i][7]);
                   for(c=i;c<nEmprunt-1;c++){
                      for(j=0;j<8;j++){
                      T_Emprunts[c][j]=T_Emprunts[c+1][j];
                    }
                   }
                   for(j=0;j<8;j++){
                    T_Emprunts[nEmprunt-1][j]=0;
                   }
                   nSup++;
                   nEmprunt--;

           }
              else i++;
            }
            if(!nSup) printf("Aucun livre disponible a supprimer\n");
            retour_menu();
        break;
        }
        case 8:
            interface_menu();
        break;

    }
}
void stat(){
    system("cls");
    printf(" ================================================================================================================= \n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------          GESTION DES EMPRUNTS          ---------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------     Veuillez choisir     ----------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                  1. AFFICHER LE NOMBRE TOTAL DE LIVRES D'ADHERENTS ET  D'EMPRUNTS            ||\n");
    printf("||                                  2 AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S)                            ||\n");
    printf("||                                  3. AFFICHER LE(S) LIVRE(S) JAMAIS EMPRUNTE(S)                               ||\n");
    printf("||                                  4. AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S) DANS UNE PERIODE DONNEE   ||\n");
    printf("||                                  5. AFFICHER LE(S) EMPRUNTEURS LE(S) PLUS FREQUENT(S)                        ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                                                                              ||\n");
    printf("||                                  6. MENU PRINCIPAL                                                           ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------||\n");
    printf("==================================================================================================================\n");


    int choix_s,i;
    do{
        printf("\n Veuillez choisir une option: ");
        scanf("%d",&choix_s);
    }while(choix_s!=1&&choix_s!=2&&choix_s!=3&&choix_s!=4&&choix_s!=5&&choix_s!=6);
    switch(choix_s){
         case 1:{
             /* Question 1 :AFFICHER LE NOMBRE TOTAL DE LIVRES D'ADHERENTS ET  D'EMPRUNTS */
            int j,nbLivre=0,nbAdh=0,existe;
            for(i=0;i<n;i++){
                nbLivre+=T_Nbr_exp[i];
            }
            for(i =0;i<nEmprunt;i++){
                existe=0;
                j=0;
                while(j<i&&!existe){
                    if(T_Emprunts[j][0]==T_Emprunts[i][0])existe=1;
                    else j++;
                }
            if(!existe) nbAdh++;
        }

        printf("\nNombre total de livres : %d\n", nbLivre);
        printf("Nombre total d'adherents : %d\n", nbAdh);
        printf("Nombre total d'emprunts : %d\n", nEmprunt);

        retour_menu();
    break;
    }
        case 2:{
        /* Question 2 : AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S) */
        int nbOc, max = 1, res;

        printf("Le(s) livre(s) le(s) plus emprunte(s) :\n");

        for(i=0;i<nEmprunt;i++){
            nbOc = compterOccurrence(T_Emprunts, nEmprunt, 1, i);
            if(nbOc > max) max = nbOc;
        }

        for(i=0;i<nEmprunt;i++){
            nbOc = compterOccurrence(T_Emprunts, nEmprunt, 1, i);
            if(nbOc == max){
                res = rechercheNum(T_NLivre, n, T_Emprunts[i][1]);
                printf("%s | numero: %d | exemplaires: %d \n", T_Titre[res],T_NLivre[res],T_Nbr_exp[res]);
            }
        }
        retour_menu();
    break;
    }
        case 3:{
        /* Question 3 : AFFICHER LE(S) LIVRE(S) JAMAIS EMPRUNTE(S) */
        int j, emprunte;

        printf("Le(s) livre(s) jamais emprunte(s) :\n");

        for(i=0;i<n;i++){
            emprunte = 0;
            j=0;
            while(j<nEmprunt&&!emprunte){
                if(T_Emprunts[j][1] == T_NLivre[i]) emprunte = 1;
                else j++;
            }

            if(!emprunte){
                printf("%s | numero: %d | exemplaires: %d \n", T_Titre[i],T_NLivre[i],T_Nbr_exp[i]);
            }
        }
        retour_menu();
    break;
    }
        case 4:{
            /*Question 4: AFFICHAGE DE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S) DANS UNE PERIODE DONNEE */
            char date1[11],date2[11],j1[3],m1[3],a1[5],j2[3],m2[3],a2[5];
            int jj1,mm1,aa1,jj2,mm2,aa2;
            int nbOc,res,max=1;
            do{
                viderBuffer();
                printf("Entrez la date debut de periode (jj/mm/aaaa) : ");
                fgets(date1,11,stdin);
                date1[strcspn(date1,"\n")]='\0';
                strncpy(j1,date1,2);
                j1[2]='\0';
                strncpy(m1,date1+3,2);
                m1[2]='\0';
                strncpy(a1,date1+6,4);
                a1[4]='\0';
                jj1=atoi(j1);
                mm1=atoi(m1);
                aa1=atoi(a1);
            }while(date1[2]!='/'||date1[5]!='/'||!estNumerique(j1,2)||!estNumerique(m1,2)||!estNumerique(a1,4)||!dateValide(2019,jj1,mm1,aa1));
            do{
                viderBuffer();
                printf("Entrez la date de fin de periode (jj/mm/aaaa): ");
                fgets(date2,11,stdin);
                date2[strcspn(date2, "\n")] = '\0';
                strncpy(j2, date2,2);
                j2[2]='\0';
                strncpy(m2,date2+3,2);
                m2[2]='\0';
                strncpy(a2,date2+6,4);
                a2[4]='\0';
                jj2=atoi(j2);
                mm2=atoi(m2);
                aa2= atoi(a2);
            }while(date2[2]!='/'||date2[5]!='/'||!estNumerique(j2,2)||!estNumerique(m2,2)||!estNumerique(a2,4)||!dateValide(2019,jj2,mm2,aa2)||!dateSup(jj2,mm2,aa2,jj1,mm1,aa1));
            printf("Les livres les plus empruntes en cette periode:\n");
            for(i=0;i<nEmprunt;i++){
                if(dateSup(T_Emprunts[i][2],T_Emprunts[i][3],T_Emprunts[i][4],jj1,mm1,aa1)&&dateSup(jj2,mm2,aa2,T_Emprunts[i][2],T_Emprunts[i][3],T_Emprunts[i][4])){
                    nbOc=compterOccurrence(T_Emprunts,nEmprunt,1,i);
                    if(nbOc>max) max=nbOc;
                }
            }
            for(i=0;i<nEmprunt;i++){
                if(dateSup(T_Emprunts[i][2],T_Emprunts[i][3],T_Emprunts[i][4],jj1,mm1,aa1)&&dateSup(jj2,mm2,aa2,T_Emprunts[i][2],T_Emprunts[i][3],T_Emprunts[i][4])){
                    nbOc=compterOccurrence(T_Emprunts,nEmprunt,1,i);
                    if(nbOc==max){
                        res=rechercheNum(T_NLivre,n,T_Emprunts[i][1]);
                        printf("%s\n",T_Titre[res]);

                    }
                }
            }
            retour_menu();
        break;
        }

        case 5:{
            /*Question 5: AFFICHER LE(S) EMPRUNTEURS LE(S) PLUS FREQUENT(S)*/
            int max=1,nbOc;
            printf("Les emprunteurs les plus frequents sont:\n");
            for(i=0;i<nEmprunt;i++){
                nbOc=compterOccurrence(T_Emprunts,nEmprunt,0,i);
                if(nbOc>max) max=nbOc;
            }
            for(i=0;i<nEmprunt;i++){
                nbOc=compterOccurrence(T_Emprunts,nEmprunt,0,i);
                if(nbOc==max) printf("%d a emprunte %d fois\n",T_Emprunts[i][0],nbOc);
            }
            retour_menu();
        break;
        }
        case 6:
            interface_menu();
        break;
        }
}



int main()
{
    interface_menu();
    return 0;
}
