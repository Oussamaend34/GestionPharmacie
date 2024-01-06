#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct {
    char Nom[50];
    int val;
}donne;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[0;34m"

int* get_users(int *n){
    int *users;
    users = (int *)malloc(sizeof(int));
    FILE *file = fopen("login.txt","rt");
    if (file == NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    int count = 0;
    int id_file;
    char hash_file[65];
    while(fscanf(file, "%d,%s", &id_file, hash_file) != EOF){
        *(users +count) = id_file;
        count++;
        users = realloc(users,count+1);
    }    
    users = realloc(users,count);
    *n = count;
    return users;
}
float max(float * users, int n){
    float m = *(users);
    for(int i = 1; i < n; i++){
        if(*(users + i) > m){
            m = *(users + i);
        }
    }
    return m;
}
float min(float * users, int n){
    float m = *(users);
    for(int i = 1; i < n; i++){
        if(*(users + i) < m){
            m = *(users + i);
        }
    }
    return m;
}
int max_int(int * users, int n){
    int m = *(users);
    for(int i = 1; i < n; i++){
        if(*(users + i) > m){
            m = *(users + i);
        }
    }
    return m;
}
int max_index(int * scores, int n){
    int m = 0;
    for(int i = 1; i < n; i++){
        if(*(scores + i) > *(scores + m)){
            m = i;
        }
    }
    return m;
}
int min_index(int * scores, int n){
    int m = 0;
    for(int i = 1; i < n; i++){
        if(*(scores + i) < *(scores + m)){
            m = i;
        }
    }
    return m;
}

void graph_users(){
    int n;
    int *users = get_users(&n);
    float *montant = (float*)malloc(sizeof(float)*n);
    for(int i = 0; i < n ; i++){
        *(montant + i) = 0;
    }
    FILE *achats = fopen("achats.bin","rb");
    if (achats == NULL){
        printf("Error lors d'ouverture du fichier");
        exit(0);
    }
    ACHAT achat;
    while(fread(&achat,sizeof(ACHAT),1,achats)!=0){
        for(int i = 0; i < n ; i++){
            if (*(users + i) == achat.id_vendeur)
                *(montant + i)+=achat.montant_total;
        }
    }
    float a = max(montant, n);
    float b = min(montant, n);
    float variance = (a - b)/(float)6;
    int *score = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n ; i++){
        *(score + i) = *(montant + i) / variance; 
    }
    int index = max_index(score,n);
    int mindix = min_index(score,n);
    int taille = max_int(score,n);
    int matrice[taille][n];
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < taille - *(score + i) ; j++){
            matrice[j][i] = 0;
        }
        for(int j = taille - *(score + i) ; j <  taille; j++){
            matrice[j][i] = 1;
        }
    }
    for(int i = 0; i < n; i++){
        printf("\t%4.0f   ",*(montant +i));
    }
    printf("\n");
    for(int i = 0; i < taille ; i++){
        for(int j = 0; j < n ; j++){
            if (matrice[i][j] == 1)
                if (j == index)
                    printf(ANSI_COLOR_GREEN "\t%c%c%c%c" ANSI_COLOR_RESET,219,219,219,219);
                else if(j == mindix)
                    printf(ANSI_COLOR_RED "\t%c%c%c%c" ANSI_COLOR_RESET,219,219,219,219);
                else
                    printf("\t%c%c%c%c",219,219,219,219);
            else
                printf("\t    ");
            printf("  ");
        }
        printf("\n");
    }
    for(int i = 0; i < n; i++){
        printf("\t%d   ",*(users +i));
    }

}

void graph_produits(){

    FILE *produits_vendues= fopen("produits.txt","rt");
    if (produits_vendues == NULL){
    printf("Erreur d'overture du fichier");
    exit(0);
    }
    donne temp;
    int n=0;
    while(fscanf(produits_vendues,"%s %d",temp.Nom,&temp.val) == 2){
        n++;
    }
    fclose(produits_vendues);
    produits_vendues= fopen("produits.txt","rt");
    if (produits_vendues == NULL){
        printf("Erreur d'overture du fichier");
        exit(0);
    }
    donne *data=(donne*)malloc(sizeof(donne) * n);
    for(int i = 0; i < n; i++){
        fscanf(produits_vendues,"%s %d",(data+i)->Nom,&(data+i)->val);
    }
    printf("\t\t  =====GRAPH DES PRODUITS=======\n");
    printf("\t\t  ******************************\n");
    for(int i = 0;i < n;i++){
        printf("\t\t%10s   ",(data +i)->Nom);
        for(int j = 0; j < (data +i)->val; j++){
            printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET,219);
        }
        printf("  %d",(data+i)->val);
        printf("\n\n");
    }
    printf("\t\t  ******************************\n");
}

void draw_line(int n){
    for(int i = 0; i < n; i++){
        printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET,205);
    }
}
void draw_space(int n){
    for(int i = 0; i < n; i++){
        printf(" ");
    }
}
void draw_column(int n){
    printf("\n");
    for(int i = 0; i < n; i++){
        printf("\t\t%c",186);
        draw_space(30);
        printf("%c\n",186);
    }
}
void draw_head(int n){
    printf(ANSI_COLOR_BLUE "\t\t%c" ANSI_COLOR_RESET,201);
    draw_line(n);
    printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET,187);
}
void draw_bottom(int n){
    printf(ANSI_COLOR_BLUE "\t\t%c" ANSI_COLOR_RESET,200);
    draw_line(n);
    printf(ANSI_COLOR_BLUE "%c"ANSI_COLOR_RESET,188);
}
void draw_dvider(int n){
    printf("\t\t%c",204);
    draw_line(n);
    printf("%c\n",185);
}
void draw_menu(){

    draw_head(30);
    printf("\n");
    printf("\t\t%c     Menu de statistique      %c\n",186,186);
    draw_dvider(30);
    printf("\t\t%c        1-Graph Users         %c\n",186,186);
    printf("\t\t%c       2-Graph products       %c\n",186,186);
    printf("\t\t%c            q-QUIT            %c\n",186,186);
    draw_bottom(30);

}
void graph_base(){
    system("cls");
        while (1){
            draw_menu();
            printf("\n");
            char c=_getch();
            system("cls");
            if (c == '1'){
                graph_users();
                getch();
                system("cls");
            }
            else if (c == '2'){
                graph_produits();
                getch();
                system("cls");
            }
            else if( c == 'q'){
                break;
            }
        }
}

