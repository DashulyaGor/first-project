#include <stdio.h>
#define GALEON 17 //1 galleon = 17 sickles
#define SICKLE 29 //1 sickle = 29 knuts

int main(){
    int g, s, k, g1, s1, k1, g2, s2, k2;
    int t1, t2, t; // total in knuts in purse 1, purse 2, purse result

    scanf("%d%d%d\n%d%d%d", &g1, &s1, &k1, &g2, &s2, &k2);

    // converting everything to knuts
    t1 = (g1 * GALEON + s1) * SICKLE + k1; //purse 1
    t2 = (g2 * GALEON + s2) * SICKLE + k2; //purse 2

    // counting the amount
    t = t1 + t2; //purse result

    // converting t back to knuts, sickles, galleons
    s = t / SICKLE; //We'll put aside sickles from the pile of knuts (in a big pile)
    k = t % SICKLE; //The remaining knuts are sent to your wallet
    g = s / GALEON; //Let's put aside the galleons from the pile of sickles
    s = s % GALEON; //The remaining sickles go to your wallet
    
    printf("%d %d %d\n", g, s, k);
    return 0;
}