#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fisier constante.c"

void eliminare_spatii_punctuatie(char *);
int valabilitate (char *);
void majuscule (char *);
void inlocuire_J_I (char *);
void separare_litere_duble (char *);
void frecventa_litere (char *, struct vector_frecvente *);
void creare_matrice ();
void eliminare_litere_duble(char *,char *, struct vector_frecvente *);
void prelucrare_matrice(struct matrica **, char *, struct vector_frecvente *);
void criptare_playfair (char *,struct  matrica **, char *);

struct vector_frecvente
{
    unsigned char litera: 1;
    int frecv;
    unsigned int marcat: 1;

};
struct matrica
{
    char litera;
    int lin;
    int col;
};
FILE *f,*g;
int main()
{
    char *prop, *key, *key2, *mesajul_criptat;
    int valabil;
    f=fopen("matrice_criptare.out","w");
    g=fopen("date_criptare.in", "r");
    int i,j,k;
    //alocare dinamica//
    struct vector_frecvente *v;
    v=(struct vector_frecvente *)calloc(ALFABET, sizeof(struct vector_frecvente));//Am folosit calloc pentru a initioaliza toate campurile structurii cu '0'//
    prop=(char *)malloc(DIMMAX*sizeof(char));
    key=(char *)malloc(DIMMAX*sizeof(char));
    key2=(char *)malloc(DIMMAX*sizeof(char));
    mesajul_criptat=(char *)malloc(DIMMAX*sizeof(char));
    //creare matrice//
    struct matrica **matrix= NULL;

    matrix=(struct matrica **)calloc(5,sizeof(struct matrica*));

    for (i=0; i<5; i++)
    {
        matrix[i]=(struct matrica *)calloc(5,sizeof(struct matrica));
    }
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {

            (matrix[i][j]).lin=i;
            (matrix[i][j]).col=j;

        }
    }

    fgets(prop, DIMMAX, g);     //citire date//
    fgets(key,DIMMAX,g);
    //prelucrare prop+cazurile speciale//
    valabil=valabilitate(prop);
    if (valabil==0)
    {
        printf("Reintroduceti un mesaj valabil(continand cel putin o litera)!");
        exit(0);
    }
    eliminare_spatii_punctuatie(prop);
    majuscule(prop);
    separare_litere_duble(prop);
    if(strlen(prop)%2!=0)
    {
        strcat(prop, "Z");
    }
    fprintf(f,"Mesajul prelucrat este: ");
    fprintf(f,"%s\n",prop);
    //prelucrare key+cazurile speciale//
    valabil=valabilitate(key);
    if (valabil==0)
    {
        printf("Reintroduceti o cheie valabila(continand cel putin o litera)!");
        exit(0);
    }
    eliminare_spatii_punctuatie(key);
    majuscule(key);
    inlocuire_J_I(key);
    frecventa_litere(key,v);
    eliminare_litere_duble(key,key2,v);
    fprintf(f,"Cheia prelucrata este: ");
    fprintf(f,"%s\n", key2);
    //prelucrare matrice//
    fprintf(f,"Matricea asociata criptarii este: \n");
    prelucrare_matrice(matrix, key2, v);
    //afisare matrice//
    for (i=0; i<LIN; i++)
    {
        for (j=0; j<COL; j++)
        {
            fprintf(f,"%c ", (matrix[i][j]).litera);
        }
        fprintf(f,"\n");
    }
    //criptarea mesajului //
    criptare_playfair(prop, matrix, mesajul_criptat);
    fprintf(f,"Mesajul criptat este: ");
    for(i=0; i<strlen(prop); i++)
        fprintf(f,"%c", mesajul_criptat[i]);
    printf("\n");
    printf("Pentru a vizualiza matricea asociata criptarii Playfair accesati fisierul matrice_criptare.out");
    return 0;
}
