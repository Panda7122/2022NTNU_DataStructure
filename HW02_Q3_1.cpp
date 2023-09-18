#include <bits/stdc++.h>
#define MAX_degree 101
using namespace std;
struct polynomial {
    int degree;
    int coef[MAX_degree] = {0};
};
int coeff1(polynomial a, int p) { return a.coef[p]; }
int main() {
    polynomial poly;
    printf("Max degree:");
    scanf("%d", &poly.degree);
    for (int i = 0; i <= poly.degree; ++i) {
        printf("coef[%d]:", i);
        scanf("%d", &poly.coef[i]);
    }
    int p;
    printf("Which term you want to search?");
    scanf("%d", &p);
    printf("the coefficient of %d term is %d", p, coeff1(poly, p));
}