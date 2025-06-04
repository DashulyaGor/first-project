#include <stdio.h>

#define GALEON 17
#define SICKLE 29

int money2knats(int g, int s, int k){
    return ((g * GALEON) + s) * SICKLE + k;
}

void knats2money(int t, int *pg, int *ps, int *pk){
    int g, s, k; //local variables

    k = t % SICKLE; //the total value of the knuts
    s = t / SICKLE; //sickles as a big pile
    g = s / GALEON; //the total value of the galleons
    s = s % GALEON; //the total value of the sickles

    //using the pointers, we will change the values of the variables

    *pk = k;
    *ps = s;
    *pg = g;
}

int main(){
    int g1, s1, k1, t1; //purse 1
    int g2, s2, k2 ,t2; //purse 2
    int g, s, k, t; // result purse

    //reading the input data
    scanf("%d%d%d", &g1, &s1, &k1);
    scanf("%d%d%d", &g2, &s2, &k2);

    //from coins to the total number of knuts
    t1 = money2knats(g1, s1, k1); //calling the money2knats function
    t2 = money2knats(g2, s2 ,k2); //calling the money2knats function

    //the amount of knuts from all purses
    t = t1 + t2;

    //from total number of knuts back to coins
    knats2money(t, &g, &s, &k); //calling the knats2money function

    //printing the result
    printf("%d %d %d\n", g, s, k);

    return 0;
}