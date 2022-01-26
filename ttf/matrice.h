#include <stdio.h>
#include <stdlib.h>
 srand(time=NULL);
 int k=[36];
 int v[49];
    int c;
 for (i=0;i<36){
    k[i]=(rand%2)+1;
    int j=i/6;
    if (k[i]==1){
       //represente les lignes
       c=j+i;
       k[c]++;
       c=c+8;
       k[c]++;
    }
    if (k[i]==2){
       //represente les lignes
       c=j+i+1;
       k[c]++;
       c=c+7;
       k[c]++;
    }
 }

i=0;
    for (m=0; m<7; m++){
        for(l=0; l<7; l++){
            matrice[m][l]=v[i];
            i++;
        }
    }
    for (m=0; m<7; m++){
        for(l=0; l<7; l++){
    printf("%4d",matrice[m][l]);
        }printf("\n");
    }
