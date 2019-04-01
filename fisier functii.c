#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fisier constante.c"

struct vector_frecvente
{
    char litera;
    int frecv;
    int marcat;

};
struct matrica
{
    char litera;
    int lin;
    int col;
};
void eliminare_spatii_punctuatie(char *p)
{
    int i, flag;
    for (i=0; i<strlen(p); i++)
    {
        flag=isalpha(p[i]);
        if(!flag)
        {
            strcpy(p+i, p+i+1);
        }
    }
}
int valabilitate (char *p)
{
    int i, flag, valabil=0;
    for (i=0; i<strlen(p); i++)
    {
        flag=isalpha(p[i]);
        if(flag)
        {
            valabil++;

        }
    }
    return valabil;
}
void majuscule (char *p)
{
    int i, flag;
    for (i=0; i<strlen(p); i++)
    {
        flag=isupper(p[i]);
        if (!flag)
        {
            p[i]=p[i]-32;
        }
    }
}
void inlocuire_J_I (char *p)
{
    int i;
    for(i=0; i<strlen(p); i++)
    {
        if(p[i]=='J')
        {
            p[i]='I';
        }
    }
}
void separare_litere_duble (char *p) //in prop: literele identice alaturate se separa printr-un 'X'//
{
    int i,l;
    l=strlen(p);
    char *p2;
    p2=(char *)malloc(DIMMAX*sizeof(char));
    for (i=0; i<l; i=i+2)
    {
        if (p[i]==p[i+1])
        {
            strcpy(p2, p+i+1);
            strcpy(p+i+1, "X");
            strcpy(p+i+2,p2);
            l++;
        }
    }
}
void frecventa_litere (char *p, struct vector_frecvente *v)
{
    int i;
    for (i=0; i<strlen(p); i++)
    {
        int x;
        x=p[i]-'A';

        (v+x)->frecv++;
    }
}
void creare_matrice ()
{
    int i,j;
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
            (matrix[i][j]).litera='A'+i+j;
            (matrix[i][j]).lin=i;
            (matrix[i][j]).col=j;

        }
    }

}

void eliminare_litere_duble(char *p,char *p2, struct vector_frecvente *v)
{
    int i,j=0;

    for(i=0; i<strlen(p); i++)
    {
        int y;
        y=p[i]-'A';
        if((v+y)->frecv!=0 && (v+y)->marcat==0)
        {
            p2[j]=y+'A';
            j++;
            (v+y)->marcat++;

        }

    }
    p2[j]='\0';
}
void prelucrare_matrice(struct matrica **m, char *p, struct vector_frecvente *v)
{
    int i, j, k ,a;
    j=0;
    i=0;
    for(k=0; k<strlen(p); k++)
    {
        if(j==COL)
        {
            j=0;
            i++;

        }
        (m[i][j]).litera=p[k];
        j++;
    }
    for(a=0; a<ALFABET; a++)
    {
        if(j==COL)
        {
            j=0;
            i++;

        }
        char b= a+'A';
        if((v+a)->frecv==0 && b!='J')
        {
            (m[i][j]).litera=b;
            j++;

        }
    }

}
void criptare_playfair (char *p,struct matrica **m, char *mesaj)
{
    int l1,l2,c1,c2,k,i,j;
    for (k=0; k<strlen(p); k+=2)
    {
        for(i=0; i<LIN; i++)
        {
            for(j=0; j<COL; j++)            //cautare si retinere pozitie litere//
            {
                if(p[k]==(m[i][j]).litera)
                {
                    l1=i;
                    c1=j;


                }
                else  if(p[k+1]==(m[i][j]).litera)
                {
                    l2=i;
                    c2=j;

                }
            }
        }



        if(l1==l2)//daca se afla pe aceeasi linie//
        {
            mesaj[k]=(m[l1][(c1+1)%5]).litera;
            mesaj[k+1]=(m[l1][(c2+1)%5]).litera;
        }

        else if(c1==c2)//daca se afla pe aceeasi coloana//
        {
            mesaj[k]=(m[(l1+1)%5][c1]).litera;
            mesaj[k+1]=(m[(l2+1)%5][c1]).litera;

        }

        else//metoda dreptunghiului//
        {
            mesaj[k]=(m[l1][c2]).litera;
            mesaj[k+1]=(m[l2][c1]).litera;
        }

    }


}
