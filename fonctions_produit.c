#include <stdio.h>
PRODUIT remplissage_produit(){
    PRODUIT p;
    printf("Donner les informations suivantes du produit :\n");
    printf("Le nom :");
    scanf("%s",p.nom);
    printf("Le fabriquant du produit :");
    scanf("%s",p.fabriquant);
    printf("Le type de ce produit :");
    scanf("%s",p.type);
    printf("Le prix unitaire :");
    scanf("%f",&p.prix);
    printf("La quantit :");
    scanf("%d",&p.quantite);
    printf("La date de fabrication : \n");
    p.date_fabrication = fillDate();
    printf("La date d'expiration :\n");
    p.date_expiration = fillDate();
    return p;
}

void affichage_produit(PRODUIT p){
    printf("Voici les informations de ce produit :\n");
    printf("Le nom : %s\n",p.nom);
    printf("Le fabriquant : %s\n",p.fabriquant);
    printf("Le type : %s\n",p.type);
    printf("Prix unitaire : %f\n",p.prix);
    printf("Quantite desponible : %d\n",p.quantite);
    printf("La date de fabrication : ");
    printDate(p.date_fabrication);
    printf("La date d'expiration : ");
    printDate(p.date_expiration);
}

