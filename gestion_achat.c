#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


Date getCurrentDate() {
    Date currentDate;

    // Obtenir le temps actuel
    time_t t = time(NULL);
    struct tm* now = localtime(&t);

    // Remplir la structure Date avec la date actuelle
    currentDate.day = now->tm_mday;
    currentDate.month = now->tm_mon + 1;
    currentDate.year = now->tm_year + 1900;
    return currentDate;
}


void effectuer_achat(UTILISATEUR *user){
    FILE *achat_file=fopen("achats.bin","ab");
    if(achat_file==NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    ACHAT achat;
    PRODUIT *produits;
    achat.id_vendeur = user->id_utilisateur;
    achat.date = getCurrentDate();
    achat.montant_total = 0;
    FILE *achats_config=fopen("system/achats.conf","rt");
    if(achats_config==NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    int id;
    fscanf(achats_config,"%d",&id);
    achat.id_achat = id;
    fclose(achats_config);
    achats_config=fopen("system/achats.conf","wt");
    if(achats_config==NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    fprintf(achats_config,"%d",id+1);
    fclose(achats_config);

    int number = achat.id_achat;
    char stringNumber[20];
    sprintf(stringNumber, "%d", number);
    const char *text = "achat/";
    int resultLength = snprintf(NULL, 0, "%s%s", text, stringNumber) + 1;
    char filename[resultLength];
    snprintf(filename, resultLength, "%s%s", text, stringNumber);

    FILE *achats_produis=fopen(filename,"wb");
    if(achats_produis==NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    printf("Donner le nombre du produits : ");
    scanf("%d",&achat.nombre_produit);
    char *buffer = malloc(sizeof(char) * 100);
    produits = malloc(sizeof(PRODUIT));
    if (produits == NULL) {
        printf("Erreur d'allocation de memoire");
        exit(0);
    }
    for(int i = 0; i < achat.nombre_produit; i++){
        FILE *stock = fopen("stock.bin","rb");
        if (stock == NULL){
            printf("Erreur d'overture du fichier");
            exit(0);
        }
        FILE *stock_temp=fopen("temp","wt");
        if (stock_temp == NULL){
            printf("Erreur d'overture du fichier");
            exit(0);
        }
        printf("entrer le nom de produits %d\n", i + 1);
        scanf("%s",buffer);
        int test = 0;
        while(fread(produits,sizeof(PRODUIT),1,stock)!=0){
            if (strcmp(buffer,produits->nom) == 0){
                int quantite;
                printf("entrer la quantite de produits %d\n", i + 1);
                scanf("%d",&quantite);
                if (quantite > produits->quantite){
                    achat.nombre_produit--;
                    printf("quantite insuffisante\n");
                    printf("il reste seulement %d\n",produits->quantite);
                }
                else{
                    achat.montant_total += quantite * produits->prix;
                    produits->quantite -= quantite;
                    int temp = produits->quantite;
                    produits->quantite = quantite;
                    fwrite(produits,sizeof(PRODUIT),1,achats_produis);
                    produits->quantite = temp;
                    FILE *produits_vendues= fopen("produits.txt","at");
                    fclose(produits_vendues);
                    produits_vendues= fopen("produits.txt","rt");
                    if (produits_vendues == NULL){
                        printf("Erreur d'overture du fichier");
                        exit(0);
                    }
                    FILE *produits_venduestemp= fopen("produit_temp","wt");
                    if (produits_venduestemp == NULL){
                        printf("Erreur d'overture du fichier");
                        exit(0);
                    }
                    char nomtmp[100];
                    int quanttemp;
                    int test1 =0;
                    while(fscanf(produits_vendues,"%s %d",nomtmp,&quanttemp) == 2){
                        if(strcmp(buffer,nomtmp) == 0){
                            quanttemp += quantite;
                            test1 = 1;
                        }
                        fprintf(produits_venduestemp,"%s %d\n",nomtmp,quanttemp);
                    }
                    if (test1 == 0){
                        fprintf(produits_venduestemp,"%s %d\n",buffer,quantite);
                    }
                    fclose(produits_vendues);
                    fclose(produits_venduestemp);
                    remove("produits.txt");
                    rename("produit_temp","produits.txt");
                }
                test = 1;

            }
            if (produits->quantite != 0)
                fwrite(produits,sizeof(PRODUIT),1,stock_temp);
        }
        if (test == 0){
            printf("produit introvable");
            achat.nombre_produit--;
        }
        fclose(stock);
        fclose(stock_temp);
        remove("stock.bin");
        rename("temp","stock.bin");
    }
    if (achat.nombre_produit != 0)
        fwrite(&achat,sizeof(ACHAT),1,achat_file);
    free(buffer);
    fclose(achats_produis);
    if (achat.nombre_produit == 0)
        remove(filename);
    fclose(achat_file);
}

void afficher_achat(){
    FILE *achats=fopen("achats.bin","rb");
    if(achats==NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    ACHAT achat;
    printf("ID DATE VENDEUR MONTANT NBRPRO PRODUITS(NOM Quantite)\n");
    while(fread(&achat,sizeof(ACHAT),1,achats)!=0){
        PRODUIT *produits = malloc(sizeof(PRODUIT));
        printf("%d ",achat.id_achat);
        printDate(achat.date);
        printf(" ");
        printf("%d ",achat.id_vendeur);
        printf("%.2f ",achat.montant_total);
        printf("%d ",achat.nombre_produit);
        int number = achat.id_achat;
        char stringNumber[20];
        sprintf(stringNumber, "%d", number);
        const char *text = "achat/";

        int resultLength = snprintf(NULL, 0, "%s%s", text, stringNumber) + 1;
        char filename[resultLength];
        snprintf(filename, resultLength, "%s%s", text, stringNumber);

        FILE *achats_produis=fopen(filename,"rb");
        if(achats_produis==NULL){
            printf("Error lors d'ouverture du fichier");
            exit(0);
        }
        while(fread(produits,sizeof(PRODUIT),1,achats_produis)!=0){
            printf("%s %d ",produits->nom,produits->quantite);
        }
        printf("\n");
        free(produits);
    }
    fclose(achats);
}

void achat_menu(){
    draw_head(30);
    printf("\n");
    printf("\t\t%c         GESTION ACHATS       %c\n",186,186);
    draw_dvider(30);
    printf("\t\t%c        1-Effectuer achats    %c\n",186,186);
    printf("\t\t%c        2-Afficher achats     %c\n",186,186);
    printf("\t\t%c            q-QUIT            %c\n",186,186);
    draw_bottom(30);

}
void achat_base(UTILISATEUR *user){
    system("cls");
        while (1){
            achat_menu();
            printf("\n");
            char c=_getch();
            if (c == '1'){
                system("cls");
                effectuer_achat(user);
                getch();
                system("cls");
            }
            else if (c == '2'){
                system("cls");
                afficher_achat();
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

