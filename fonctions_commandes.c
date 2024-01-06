#include <stdio.h>
#include <stdlib.h>
#include <time.h>



COMMANDE remplissage_commande(){
    COMMANDE com;
    printf("Donner le nom du fournisseur : ");
    scanf("%s",com.nom_fournissur);
    printf("Donner le montant de cette commande : ");
    scanf("%f",&com.montant);
    com.date_demande=getCurrentDate();
    return com;
}


void affichage_commande(COMMANDE com){
    printf("Informations sur la commande :");
    printf("nom du fournisseur : ",com.nom_fournissur);
    printf("le  montant : ",com.montant);
    printf("la date : ",com.date_demande);
}
