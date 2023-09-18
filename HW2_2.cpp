#include <bits/stdc++.h>
#define MAX_TERMS 100
using namespace std;
struct polynomial {
    int coef;
    int expon;
};
int avail = 0;
int coeff1(polynomial *a, int p) {
    for (int i = 0; i < avail; ++i)
        if ((a + i)->expon == p) return (a + i)->coef;
    return 0;
}
int add(polynomial *a, polynomial *b) {}
int main() {
    polynomial terms[MAX_TERMS];
    printf("How many Terms:");
    scanf("%d", &avail);
    for (int i = 0; i < avail; ++i) {
        printf("coef:", i);
        scanf("%d", &terms[i].coef);
        printf("expon:", i);
        scanf("%d", &terms[i].expon);
    }
    int p;
    printf("Which term you want to search?");
    scanf("%d", &p);
    printf("the coefficient of %d term is %d", p, coeff1(terms, p));
}