#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


void ajoute_in_stock(UTILISATEUR usr){
    FILE *stock =fopen("stock.bin","ab");
    fclose(stock);
    stock=fopen("stock.bin","r+b");
    if(stock == NULL){
        printf("Probleme d'ouverture de stock file\n");
        exit(0);
    }
    if(usr.privilege > 3){
        printf("Vous n'avez pas le droit pour ajouter des produits au stock");
        exit(0);
    }
    else{
        PRODUIT produit_ajoute,produit_aide;
        int test_existance=0;
        printf("Entrer le nom du produit a ajouter dans le stock :\n");
        scanf("%s",produit_ajoute.nom);
        fseek(stock,0,SEEK_SET);
        //boucle pour cheker si le produit deja existe ou pas
        while(fread(&produit_aide,sizeof(PRODUIT),1,stock)==1){
            if(strcmp(produit_aide.nom,produit_ajoute.nom)==0){
                printf("Ce produit existe deja \n");
                test_existance=1;
                break;
            }
        }
        fseek(stock,0,SEEK_END);
        if(test_existance==0){
            produit_ajoute=remplissage_produit();
            fwrite(&produit_ajoute,sizeof(PRODUIT),1,stock);
        }
    }
    fclose(stock);
}

void modifier_info_in_stock(UTILISATEUR usr){
    FILE *stock =fopen("stock.bin","ab");
    FILE *temporaire =fopen("temporaire.bin","ab");
    fclose(stock);
    stock=fopen("stock.bin","r+b");
    if(stock == NULL){
        printf("Probleme d'ouverture de stock file\n");
        exit(0);
    }
    if(usr.privilege > 3){
        printf("Vous n'avez pas le droit pour modifier dans le stock");
        exit(0);
    }
    else{
        PRODUIT produit_modifie;
        char nom_produit[50];
        printf("Entrer le nom du produit a modifier dans le stock :\n");
        scanf("%s",nom_produit);
        fseek(stock,0,SEEK_SET);
        while(fread(&produit_modifie,sizeof(PRODUIT),1,stock)==1){
            if(strcmp(produit_modifie.nom,nom_produit)==0){
                affichage_produit(produit_modifie);
                produit_modifie=remplissage_produit();
            }
            fwrite(&produit_modifie,sizeof(PRODUIT),1,temporaire);
        }
    }
    fclose(stock);fclose(temporaire);
    remove("stock.bin");
    rename("temporaire.bin","stock.bin");
}

void supression_in_stock(UTILISATEUR usr){
    FILE *stock =fopen("stock.bin","ab");
    FILE *temporaire =fopen("temporaire.bin","ab");
    fclose(stock);
    stock=fopen("stock.bin","r+b");
    if(stock == NULL){
        printf("Probleme d'ouverture de stock file\n");
        exit(0);
    }
    if(usr.privilege > 3){
        printf("Vous ne possedez pas du droit pour supprimer des produits du stock");
        exit(0);
    }
    else{
        PRODUIT produit;
        char nom_produit[50];
        printf("Entrer le nom du produit a modifier dans le stock :\n");
        scanf("%s",nom_produit);
        fseek(stock,0,SEEK_SET);
        //boucle pour cheker si le produit deja existe ou pas
        while(fread(&produit,sizeof(PRODUIT),1,stock)==1){
            if(strcmp(produit.nom,nom_produit)==0){
                continue;
            }
            fwrite(&produit,sizeof(PRODUIT),1,temporaire);
        }
    }
    fclose(stock);fclose(temporaire);

    remove("stock.bin");rename("temporaire.bin","stock.bin");
}

void affichage_de_stock(){
    FILE *stock=fopen("stock.bin","rb");
    if (stock == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    PRODUIT produit;
    int conteur=0,test_eof=0,page=1;
    char touche;
    while( 0 == test_eof){
        system("cls");
        int i;
        printf("Nom \t Fbriquant \t Type \t Prix \t Quantite \t Date de fabrication  \t Date d'expiration \n");
        for(i=0;i<10;i++){
            if(fread(&produit,sizeof(PRODUIT),1,stock)==1){
                printf(" %s \t %s \t %s \t %f \t %d \t ", produit.nom,produit.fabriquant,produit.type,produit.prix,produit.quantite);
                printDate(produit.date_fabrication);printf(" \t ");
                printDate(produit.date_expiration);printf(" \n");
            }
            else{
                test_eof=1;
            }
        }
        printf("Page %d \n Pour visualiser la page suivante : Right key \n Pour visualiser la page precedante : Left Key \n Pour quitter la visualisation : 'e' Key ",page);
        touche=getch();
        if(touche=='e' || touche=='E'){
            break;
        }
        else if(touche==77){
            page++;
            continue;
        }
        else if(touche==75){
            if(i==10){
                fseek(stock,(-10)*sizeof(PRODUIT),SEEK_CUR);
                page--;
            }
            else{
                fseek(stock,(-10-i)*sizeof(PRODUIT),SEEK_CUR);
                page--;
            }
        }
        else {
            system("cls");
        }
    }
    system("cls");
    //ici vous allez avoir une screen vide , vous pouvez utliser les autre fonctions
}

void chercher_produit(){
    PRODUIT pro_cher;
    FILE *stock=fopen("stock.bin","r+b");
    if (NULL == stock){
        printf("Erreur d'ouverture de fichier ");
        exit(0);
    }
    char nom[50];
    printf("donner le nom du produit a chercher :");
    scanf("%s",nom);
    while(fread(&pro_cher,sizeof(PRODUIT),1,stock)==1){
        if(strcmp(pro_cher.nom,nom)==0){
            affichage_produit(pro_cher);
        }
    }
}

void stock_menu(){

    printf("Pour choisir une operation , tapez juste son numero: \n");
    printf("1- Ajouter un produit\n");
    printf("2- Modifier un produit\n");
    printf("3- Supprimer un produit\n");
    printf("4- Afficher le stock\n");
}
void stock_base(UTILISATEUR usr){
    system("cls");
        while (1){
            stock_menu();
            printf("\n");
            char c=_getch();
            if (c == '1'){
                system("cls");
                ajoute_in_stock(usr);
                getch();
                system("cls");
            }
            else if (c == '2'){
                system("cls");
                modifier_info_in_stock(usr);
                getch();
                system("cls");
            }
            else if (c == '3'){
                system("cls");
                supression_in_stock(usr);
                getch();
                system("cls");
            }
            else if (c == '4'){
                system("cls");
                affichage_de_stock();
                getch();
                system("cls");
            }
            else if( c == 'q'){
                system("cls");
                break;
            }
            else{
                system("cls");
            }
        }
}