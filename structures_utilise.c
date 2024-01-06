
typedef struct {
    int day;
    int month;
    int year;
} Date;


Date fillDate() {
    Date userDate;

    printf("Jour : ");
    scanf("%d", &userDate.day);
    printf("Mois : ");
    scanf("%d", &userDate.month);
    printf("Annee : ");
    scanf("%d", &userDate.year);
    return userDate;
}
void printDate(Date date) {
    printf("%d/%d/%d", date.day, date.month, date.year);
}

typedef struct{
    int id_employe;
    char nom[20];
    char prenom[20];
    char tel[11];
    int poste;
    char rib[25];
    char email_address[100];
}EMPLOYE;
//----------------------------
typedef struct{
    int id_utilisateur;// cet id referre a id_employe
    int privilege;// les privileges de 1 a 4
}UTILISATEUR;

typedef struct{
    int id_medcecin;
    char nom[20];
    char prenom[20];
    char tel[11];
    char email_address[100];
    char specialite[50];
    char address[100];
}MEDECIN;
//-----------------------------
typedef struct{
    int id_fournisseur;
    char nom[30];
    char tel[11];
    char email_address[100];
}FOURNISSEUR;

typedef struct{
    char nom[50];
    char fabriquant[30]; // la nom du fournisseur du produit
    char type[20];
    Date date_fabrication;//la date est stocker sous forme jj/mm/year
    Date date_expiration;//la date est stocker sous forme jj/mm/year
    float prix;
    int quantite;
}PRODUIT;

typedef struct{
    char nom[50];// c'est le meme que le nom du produit
    char Dosage[10];
    char Fabriquant[30]; // medicament.fabriquant == produit.fabriquant
    char Composition[30];// c'est le composant majeur
}MEDICAMENT;

typedef struct{
    int id_achat;
    int nombre_produit;
    int id_vendeur;
    float montant_total;
    Date date;
}ACHAT;

typedef struct{
    Date date_demande;
    float montant;
    char nom_fournissur[30];
}COMMANDE;


