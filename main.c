#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 500
#define TAILLEPLAT 11


void initialize(int tab[TAILLEPLAT][TAILLEPLAT]);
int useItem(char inv[TAILLE], char item[TAILLE]);
int afficherMenu(int joueur,int Mov[4]);
void getTreasure(char inv[TAILLE],int *treasure);
void moveMonster(int *x, int *y ,int tab[TAILLEPLAT][TAILLEPLAT]);
void cyclePlayer(int *player);
void volerPM(int player, int Mov[4],char inv[TAILLE],int cible);
void getRune(int joueur, int rune[4]);
int validerVictoire(int joueur,int rune[4]);
void getTrapped(char inv[TAILLE],char Mov[4],int joueur);
void respawnTreasure(int *treasure, int tab[TAILLEPLAT][TAILLEPLAT]);


int main()
{
    srand (time(NULL));
    int input = 0;
    int leave = 1; // Indique a la boucle de menu qi on doit la quitter ou pas.
    int victory = 1; //Indique si le jeu a été fini ou pas.
    int plateau[TAILLEPLAT][TAILLEPLAT] = {0,}; //Matice repesentant le plateau.
    char inventaireJoueur1[TAILLE] = "";
    char inventaireJoueur2[TAILLE] = "";
    char inventaireJoueur3[TAILLE] = "";
    char inventaireJoueur4[TAILLE] = "";
    int joueur = 1; //Indique le joueur courant.
    int monsterx = 5; //Coordonées de départ du monstre.
    int monstery = 5;
    int Mov[4] = {3,3,3,3}; //Tableau des points de mouvmement pour les joueurs 1 , 2 , 3 , 4 , respectivement.
    int rune[4] = {0,0,0,0};


    initialize(plateau);

    int treasure = 4;
    do{
        leave = 1;
        do{
            switch(afficherMenu(joueur,Mov)){

            case 1 : if (joueur == 1) getTrapped(inventaireJoueur1,Mov,joueur);
                     else if (joueur == 2) getTrapped(inventaireJoueur2,Mov,joueur);
                     else if (joueur == 3) getTrapped(inventaireJoueur3,Mov,joueur);
                     else if (joueur == 4) getTrapped(inventaireJoueur4,Mov,joueur);
                     break;

            case 2 : if (treasure > 0){
                         if (joueur == 1) getTreasure(inventaireJoueur1,&treasure);
                         else if (joueur == 2) getTreasure(inventaireJoueur2,&treasure);
                         else if (joueur == 3) getTreasure(inventaireJoueur3,&treasure);
                         else if (joueur == 4) getTreasure(inventaireJoueur4,&treasure);
                     } else {
                         printf("Il n'y a plus de tresors!");
                         system("pause");
                     break;

            case 3 : printf("Qui avez vous croise?");
                     do{
                        scanf("%d",&input);
                     }while((input < 1)||(input > 4)||(input == joueur));
                     if (input == 1) volerPM(joueur,Mov,inventaireJoueur1,input);
                     if (input == 2) volerPM(joueur,Mov,inventaireJoueur2,input);
                     if (input == 3) volerPM(joueur,Mov,inventaireJoueur3,input);
                     if (input == 4) volerPM(joueur,Mov,inventaireJoueur4,input);
                     break;

            case 4 : if (joueur == 1) puts(inventaireJoueur1);
                     else if (joueur == 2) puts(inventaireJoueur2);
                     else if (joueur == 3) puts(inventaireJoueur3);
                     else if (joueur == 4) puts(inventaireJoueur4);

                     system("pause");
                     break;

            case 5 : leave = 0;
                     break;

            case 6 : getRune(joueur,rune);
                     break;

            case 7 : if (validerVictoire(joueur,rune) == 0){
                                victory = 0;
                                leave = 0;
            }
                     break;

            system("pause");

            }
        }while(leave == 1);

    cyclePlayer(&joueur);
    //Si joueur revient a 1, le tour est donc fini. On fait bouger le monstre.
    if (joueur == 1) {
        system("cls");
        printf("\nTOUR FINI! LE MONSTRE VA BOUGER");
        moveMonster(&monsterx,&monstery,plateau);
        moveMonster(&monsterx,&monstery,plateau);
        moveMonster(&monsterx,&monstery,plateau);
        printf("\n\n");
        Mov[0] = 3;
        Mov[1] = 3;
        Mov[2] = 3;
        Mov[3] = 3;
        system("pause");
        respawnTreasure(&treasure,plateau);
    }

    }while(victory == 1);

    return 0;
}

void initialize(int tab[TAILLEPLAT][TAILLEPLAT]){

    /*  BUT: Initialiser le plateau avec les murs.
        ENTREE: Le plateau non initalisé
        SORTIE: Le plateau , rempli de 0 pour le sol et de 1 ppur les murs.
    */

    int i,j = 0;
    int treasure = 0;

    for (i=0;i<TAILLEPLAT;i++){
        for (j=0;j<TAILLEPLAT;j++){

            tab[i][j] = 0;

            if ( i==1 && j==1 ) tab[i][j] = 1;
            if ( i==1 && j==2 ) tab[i][j] = 1;
            if ( i==2 && j==1 ) tab[i][j] = 1;
            if ( i==1 && j==3 ) tab[i][j] = 1;
            if ( i==3 && j==1 ) tab[i][j] = 1;

            if ( i==1 && j==7 ) tab[i][j] = 1;
            if ( i==1 && j==8 ) tab[i][j] = 1;
            if ( i==1 && j==9 ) tab[i][j] = 1;
            if ( i==2 && j==9 ) tab[i][j] = 1;
            if ( i==3 && j==9 ) tab[i][j] = 1;

            if ( i==7 && j==1 ) tab[i][j] = 1;
            if ( i==8 && j==1 ) tab[i][j] = 1;
            if ( i==9 && j==1 ) tab[i][j] = 1;
            if ( i==9 && j==2 ) tab[i][j] = 1;
            if ( i==9 && j==3 ) tab[i][j] = 1;

            if ( i==9 && j==7 ) tab[i][j] = 1;
            if ( i==9 && j==8 ) tab[i][j] = 1;
            if ( i==9 && j==9 ) tab[i][j] = 1;
            if ( i==7 && j==9 ) tab[i][j] = 1;
            if ( i==8 && j==9 ) tab[i][j] = 1;

            if ( i==3 && j==4 ) tab[i][j] = 1;
            if ( i==4 && j==3 ) tab[i][j] = 1;
            if ( i==6 && j==3 ) tab[i][j] = 1;
            if ( i==7 && j==4 ) tab[i][j] = 1;
            if ( i==3 && j==6 ) tab[i][j] = 1;
            if ( i==4 && j==7 ) tab[i][j] = 1;
            if ( i==6 && j==7 ) tab[i][j] = 1;
            if ( i==7 && j==6 ) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==3 && j==3 )) tab[i][j] = 1;
            if (((rand() % 2 + 1) == 1) && ( i==4 && j==4 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==6 && j==4 )) tab[i][j] = 1;
            if (((rand() % 2 + 1) == 1) && ( i==7 && j==3 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==3 && j==7 )) tab[i][j] = 1;
            if (((rand() % 2 + 1) == 1) && ( i==4 && j==6 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==6 && j==6 )) tab[i][j] = 1;
            if (((rand() % 2 + 1) == 1) && ( i==7 && j==7 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==1 && j==5 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==5 && j==1 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==5 && j==9 )) tab[i][j] = 1;

            if (((rand() % 2 + 1) == 1) && ( i==9 && j==7 )) tab[i][j] = 1;

        }

    }
        printf("Arrangez le plateau de cette facon\n\n");
        for (i=0;i<TAILLEPLAT;i++){
            for (j=0;j<TAILLEPLAT;j++){
                printf("%d",tab[i][j]);
            }
            printf("\n");
        }

    do{
        i = rand() % 6 + 3;
        j = rand() % 6 + 3;

        if (tab[i][j] == 0){
            printf("Placez un trésor en %d %d !\n",i+1,j+1);
            treasure++;
        }
    }while (treasure < 4);

    system("pause");
}

void getTreasure(char inv[TAILLE], int *treasure){
    /*
        BUT: Mettre un trésor tiré aléaoirement dans l'inventaire d'un joueur.
        ENTREE: L'inventaire du'un joueur
        SORTIE: La meme chaine, a laquelle est ajoutée l'objet ajouter, avec un texte disant quel objet a été donné.
    */

    int result = 0;
    result = rand() % 10 + 1; //On prends un chiffre entre 1 et 10, qu'on utilise pour determiner lequel des 10 objets le joueur obtient.

    switch (result){
        case 1 :
            printf("Vous avez recu un piege de mouvement!");  //On dis quel item a été obtenu.
            strncat(inv," Piege:mouvement",100);              //On le concatenne a la chaine d'inventaire.
        break;
        case 2 :
            printf("Vous avez recu un piege mur!");
            strncat(inv," Piege:Mur",100);
        break;
        case 3 :
            printf("Vous avez recu une hache!");
            strncat(inv," Hache",100);
        break;
        case 4 :
            printf("Vous avez recu des chaussures!!");
            strncat(inv," Chaussures",100);
        break;
        case 5 :
            printf("Vous avez recu un boulier!");
            strncat(inv," Bouclier",100);
        break;
        case 6 :
            printf("Vous avez recu un aimant!");
            strncat(inv," Aimant",100);
        break;
        case 7 :
            printf("Vous avez recu une boussole!");
            strncat(inv," Boussole",100);
        break;
        case 8 :
            printf("Vous avez recu un Repousse-Monstre!");
            strncat(inv," Repousse-Monstre",100);
        break;
        case 9 :
            printf("Vous avez recu un croche patte!");
            strncat(inv," Croche Patte",100);
        break;
        case 10 :
            printf("Vous avez recu un plus gros aimant!");
            strncat(inv," Gros Aimant",100);
        break;


    }
    *treasure = *treasure - 1;
    printf("   Il y a %d tresors.",*treasure);
    printf("\n");
    system("pause");
}

int afficherMenu(int joueur,int Mov[4]){
    /*  BUT: Afficher le menu.
        ENTREE: --
        SORTIE: Le menu.
    */

    system("cls");
    int input = 0;
    printf("===============================================\n");
    printf("==         C'est le tour du joueur %d         ==\n",joueur);
    printf("===============Vous avez %d PM(s)===============\n",Mov[joueur-1]);
    printf("Entrez un numero correspodnat a l'action souhaitee\n");
    printf("\n");
    printf("\n1.Piege ou monstre     2.Tresor      3.Voler PM\n"); //TODO Voler PM
    printf("\n4.Inventaire                 5.Finir votre tour\n"); //TODO FInir Inventaire
    printf("\n6.Déclarer l'obtention d'une rune  7.S'echapper\n"); //TODO Declarer Runes, Sortir
    scanf("%d",&input);                                            //TODO rechercher Item
    return input;

}

void moveMonster(int *x, int *y, int tab[TAILLEPLAT][TAILLEPLAT]){
    /*  BUT: BOuger le monstre dans le labyrinthe.
        ENTREE: Les coordonées du mosntres, le plateau.
        SORTIE: Les coordronées mis a jour du monstre.
    */


    srand (time(NULL));
    int result = 0;
    int isMoveValid = 1;

    do{
        result = rand() % 4 + 1; //On prends une direction au hasard. (1 est haut, et on comtpe dans les aiguilles d'ne montre.)

        switch (result){

            case 1: if (((*y + 1) <= 10) && (tab[*x][*y+1] != 1)){
                        isMoveValid = 0;
                        *y = *y+1;
                    }
                    break;

            /*
            On test si le monstre ne sortiras pas du plateau ou ne rentras pas dnas un mur si il fait le mouvement tiré.
            Si le mouvement ne fait rien de cela, on déclare le move valide, et on l'applique.
            */

            case 2: if (((*x + 1) <= 10) && (tab[*x+1][*y] != 1)){
                        isMoveValid = 0;
                        *x = *x+1;
                    }
                    break;


            case 3: if (((*y - 1) >= 0) && (tab[*x][*y-1] != 1)){
                        isMoveValid = 0;
                        *y = *y-1;
                    }
                    break;

            case 4: if (((*x - 1) >= 0) && (tab[*x-1][*y] != 1)){
                        isMoveValid = 0;
                        *x = *x-1;
                    }
                    break;


            default: break;
        }
    } while( isMoveValid == 1); //Si le move n'est pas valide, on en tire un nouveau jusqu'a qu'il soit valide.
    printf("\n\n Le monstre bouge a la case [%d,%d]!",*x + 1,*y + 1);
}

void cyclePlayer(int *player){
    /*  BUT:Passer au joueur suivant.
        ENTREE: Le numero du joueur actuel
        SORTIE: La variable modifiée a la valeure du joueur suivant.
    */

    if (*player == 1) *player = 2;
    else if (*player == 2) *player = 3;
    else if (*player == 3) *player = 4;
    else if (*player == 4) *player = 1;

}

void volerPM(int player, int Mov[4],char inv[TAILLE],int cible){

    int input = 0;

    if (useItem(inv,"Croche Patte") == 0){
        printf("Le joueur %d avait un crochepatte! %d perds tout ses poitns de mouvement.",cible,player);
        Mov[player-1] = 0;
    }else{
    printf("Vous avez vole un point de mouvment a %d .",cible);
    Mov[player-1]++;
    Mov[cible-1]--;
    }
    system("pause");
}

void getRune(int joueur, int rune[4]){

    printf("Vous avez recupere un rune!\n");
    rune[joueur-1] = 1;
    system("pause");

}

int validerVictoire(int joueur,int rune[4]){

    if (rune[joueur-1] == 0) {
        printf("\n\nVous n'avez pas de rune! VOus ne pouvea pas sortir!");
        return 1;
    }
    else {
        printf("\n\nVous vous etes echappe!");
        return 0;
    }

    system("pause");
}

void getTrapped(char inv[TAILLE],char Mov[4],int joueur){

    int input = 0;
    int input2 = 0;
    printf("\nQuel genre de piege avez vous subis?\n");
    printf("\n 1. Des ronces       2.Un monstre\n");
    do{
        scanf("%d",&input);
    }while ((input != 1)&&(input != 2));

    if (input == 1){
        if (useItem(inv,"Chaussures") == 0){
            printf(" VOus avez evite le piege!");
        }else{
            printf(" VOus perdez tout vos PMs!");
            Mov[joueur-1] = 0;
        }
    }

    if (input == 2){
        if (useItem(inv,"Repousse-Monstre") == 0){
            printf("Vous avez evite le monstre!\n");
            printf("Chez qui voulez vous renvoyer le monstre?");
            do{
                scanf("%d",&input2);
            }while((input2 <= 1)||(input2 >= 4)||(input2 == joueur));
            printf("\n Le joueur %d a pris le monstre a votre place!", input2-1);
            Mov[input2-1] = 0;
        }else if (useItem(inv,"Bouclier") == 0){
            printf("Vous evitez le piege.");
        }else{
            printf(" VOus perdez tout vos PMs!");
            Mov[joueur-1] = 0;
        }
    }
    system("pause");

}

int useItem(char inv[TAILLE], char item[TAILLE]){

    int input = 0;

    if (strstr (inv,item)){
        printf("\nVous avez un objet ous permettant de contrer ce piege! (%s) Voulez-vous l'utiliser? ( Taper 0 pour oui. )\n",item);
        scanf("%d",&input);
        if (input == 0){
            printf("Vous avez utilisé %s !",item);
            return 0;
        }else{
            printf("Vous vous prenez le piege.\n");
            return 1;
        }
    }else{
        return 1;
    }

}

void respawnTreasure(int *treasure, int tab[TAILLEPLAT][TAILLEPLAT]){

    int j = 0;
    int i = 0;
    while(*treasure < 4){

        i = rand() % 6 + 3;
        j = rand() % 6 + 3;

        if (tab[i][j] == 0){
            printf("Placez un trésor en %d %d !\n",i+1,j+1);
            *treasure = *treasure + 1;
        }
    }
system("pause");
}
