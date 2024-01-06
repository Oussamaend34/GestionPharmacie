#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "structures_utilise.c"
#include "login.c"
#include "graph.c"
#include "help.c"
#include "gestion_utilisateurs.c"
#include "fonctions_employe.c"
#include "gestion_employe.c"
#include "log.c"
#include "menu_geston.c"
#include "gestion_achat.c"
#include "fonctions_commandes.c"
#include "fonctions_produit.c"
#include "Gestion_stock.c"
#include "Gestion_commandes.c"




int event_handler(UTILISATEUR *user,int *test){
    char c = _getch();
    if (c == 'q'){
        system("cls");
        exit(0);
    }
    else if (c == '1')
        stock_base(*user);
    else if (c == '2')
        commande_base(*user);
    else if (c == '3'){
        system("cls");
        gestion_des_employes();
        system("cls");
    }  
    else if (c == '4')
        achat_base(user);
    else if (c == '5')
        graph_base();
    else if (c == '6')
        *test = 0;   
    else
        system("cls");
    return 0;
}
void main_menu(){
    draw_head(30);
    printf("\n");
    printf("\t\t%c          Main Menu           %c\n",186,186);
    draw_dvider(30);
    printf("\t\t%c    1. Gestion des stocks     %c\n",186,186);
    printf("\t\t%c   2. Gestion des commandes   %c\n",186,186);
    printf("\t\t%c   3. Gestion des employees   %c\n",186,186);
    printf("\t\t%c    4. Gestion des achats     %c\n",186,186);
    printf("\t\t%c          5. GRAPH            %c\n",186,186);
    printf("\t\t%c        6-Deconnexion         %c\n",186,186);
    printf("\t\t%c            q-QUIT            %c\n",186,186);
    draw_bottom(30);
    printf("\n");
}
void main_base(){
    UTILISATEUR *user = malloc(sizeof(UTILISATEUR));
    user->id_utilisateur = 0;
    while (1){
        system("cls");
        printf("\t\tEntrer 'c' pour connexion et q pour deconnexion\n");
        while(1){
        char c = _getch();
        system("cls");
        if (c == 'q')
            exit(0);
        if( c == 'c'){
            break;
        }
        }
        login(user);
        int test = 1;
        char c;
        while (test == 1){
            main_menu();
            event_handler(user,&test);
        }
    }
}
int main(){
    main_base();
}