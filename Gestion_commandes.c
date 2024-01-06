#include <stdio.h>
#include <stdlib.h>



void ajouter_commande(UTILISATEUR usr){
    FILE *commandes=fopen("commandes.bin","ab");
    fclose(commandes);
    commandes=fopen("commandes.bin","r+b");
    if(commandes==NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    if(usr.privilege > 2){//Pour savoir si l'utilisateur est un pharmacien
        printf("Vous n'avez pas le droit d'ajouter une commande \nSi vous etes un pharmacien contactez le proprietere de votre pharmacie.");
        exit(0);
    }
    else{
        COMMANDE com_ajout;
        char conf[4]="non",pro_name[50];//conf est pour indique la comfirmation de la commande
        int id,pro_quantite;
        com_ajout = remplissage_commande();
        printf("donner le produit de cette commande :");
        scanf("%s",pro_name);
        printf("donner la quantite du produit pour de cette commande :");
        scanf("%s",&pro_quantite);
        if (ftell(commandes) == -1){
            //cette condition pour savoir si le fichier est vide
            id=1;
            fwrite(&id,sizeof(int),1,commandes);
            fwrite(&usr.id_utilisateur,sizeof(int),1,commandes);
            fwrite(&com_ajout,sizeof(COMMANDE),1,commandes);
            fwrite(conf,4*sizeof(char),1,commandes);
            fwrite(pro_name,50*sizeof(char),1,commandes);
            fwrite(&pro_quantite,sizeof(int),1,commandes);
        }
        else{
            fseek(commandes,-3*sizeof(int)-sizeof(COMMANDE)-54*sizeof(char),SEEK_END);
            fread(&id,sizeof(int),1,commandes);
            fseek(commandes,0,SEEK_END);
            id=id+1;
            //ajout dans le fichier ajouter ensuite une bonne insertion en fonction de usr.id_utilisateur
            fwrite(&id,sizeof(int),1,commandes);
            fwrite(&usr.id_utilisateur,sizeof(int),1,commandes);
            fwrite(&com_ajout,sizeof(COMMANDE),1,commandes);
            fwrite(conf,4*sizeof(char),1,commandes);
            fwrite(pro_name,50*sizeof(char),1,commandes);
            fwrite(&pro_quantite,sizeof(int),1,commandes);
        }
    }
    fclose(commandes);
}

void comfirmer_commande(UTILISATEUR usr){
    FILE *commandes=fopen("commandes.bin","r+b"),*temp_file=fopen("temporaire.bin","ab");
    if(( commandes==NULL )|| ( temp_file==NULL )){
        printf("Ereur d'ouverture des fichiers ");
        exit(0);
    }
    if(usr.privilege > 2){
        printf("Vous n'avez pas le droit pour comfirmer cette commande.");
        exit(0);
    }
    else{
        int id_conf,id,user_id,pro_quantite;
        COMMANDE com_conf;
        PRODUIT produit;
        char conf[4],pro_name[50];
        printf("Donner l'id de la commande : ");
        scanf("%d",&id_conf);
        while(fread(&id,sizeof(int),1,commandes)==1){
            fread(&user_id,sizeof(int),1,commandes);
            fread(&com_conf,sizeof(COMMANDE),1,commandes);
            fread(&conf,4*sizeof(char),1,commandes);
            fread(pro_name,50*sizeof(char),1,commandes);
            fread(&pro_quantite,sizeof(int),1,commandes);
            if(id==id_conf){
                strcpy(conf, "oui");
            }
            fwrite(&id,sizeof(int),1,temp_file);
            fwrite(&usr.id_utilisateur,sizeof(int),1,temp_file);
            fwrite(&com_conf,sizeof(COMMANDE),1,temp_file);
            fwrite(conf,4*sizeof(char),1,temp_file);
            fwrite(pro_name,50*sizeof(char),1,temp_file);
            fwrite(&pro_quantite,sizeof(int),1,temp_file);
        }
        printf("afin de terminer la comfrmation de la commande , vous etes sense d'entrer les informations du produit");
        ajoute_in_stock(usr);
        printf("la commande N:%d est comfirmer",id);
    }
    fclose(commandes);fclose(temp_file);
    remove("commandes.bin");rename("temporaire.bin","commandes.bin");
}

void commande_menu(){
    draw_head(30);
    printf("\n");
    printf("\t\t%c      Menu de commandes       %c\n",186,186);
    draw_dvider(30);
    printf("\t\t%c   1-Ajouter une commande.    %c\n",186,186);
    printf("\t\t%c  2-Comfirmer une commande.   %c\n",186,186);
    printf("\t\t%c            q-QUIT            %c\n",186,186);
    draw_bottom(30);
}

void commande_base(UTILISATEUR usr){
    system("cls");
        while (1){
            commande_menu();
            printf("\n");
            char c=_getch();
            system("cls");
            if (c == '1'){
                ajouter_commande(usr);
                getch();
                system("cls");
            }
            else if (c == '2'){
                comfirmer_commande(usr);
                getch();
                system("cls");
            }
            else if( c == 'q'){
                break;
            }
        }
}

