#include <math.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#ifdef _WIN32
#define cl "cls"
#define wait system("pause");
#else
#define wait                                  \
    printf("Press Enter key to continue..."); \
    fgetc(stdin);                             \
    fflush(stdin);
#define cl "clear"
#endif
#define ll long long
using namespace std;
struct element {
    int r, c, v = 0;
};
struct Matrix {
    char name[100] = "\0";
    element m[100];
};
Matrix arr[10000];
bool operator<(element a, element b) {
    return (a.r == b.r) ? (a.c < b.c) : (a.r < b.r);
}
void printMartix(Matrix a) {
    if (a.name[0] == '\0') return;
    // printf("%d %d %d\n", a.m[0].r, a.m[0].c, a.m[0].v);
    int big = 0;
    for (int i = 1; i <= a.m[0].v; i++) {
        big = max(big, a.m[i].v);
    }
    int cnt = 0;
    while (big) {
        cnt++;
        big /= 10;
    }

    for (int i = 0; i < a.m[0].r; i++) {
        for (int j = 0; j < a.m[0].c; j++) {
            int exist = 0;
            for (int k = 1; k <= a.m[0].v; k++) {
                if (a.m[k].r == i && a.m[k].c == j) {
                    int cnow = 0;
                    int tmp = a.m[k].v;
                    while (tmp) {
                        cnow++;
                        tmp /= 10;
                    }
                    for (int sp = 0; sp < cnt - cnow; sp++) {
                        printf(" ");
                    }
                    printf("%d ", a.m[k].v);
                    exist = 1;
                    break;
                }
            }
            if (!exist) {
                for (int sp = 0; sp < cnt - 1; sp++) printf(" ");
                printf("0 ");
            }
        }
        printf("\n");
    }
}
Matrix init(int s) {
    Matrix I;
    I.name[0] = 'i';
    I.name[1] = 'n';
    I.name[2] = 'i';
    I.name[3] = 't';
    I.name[4] = '\0';
    I.m[0].r = s;
    I.m[0].c = s;
    I.m[0].v = s;
    for (int i = 1; i <= s; ++i) {
        I.m[i].r = i - 1;
        I.m[i].c = i - 1;
        I.m[i].v = 1;
    }
}
Matrix submatrix(Matrix a, int r, int c) {
    int big = 0;
    for (int i = 1; i <= a.m[0].v; i++) {
        if (a.m[i].r != r && a.m[i].c != c) big = max(big, a.m[i].v);
    }
    int cnt = 0;
    while (big) {
        cnt++;
        big /= 10;
    }

    for (int i = 0; i < a.m[0].r; i++) {
        for (int j = 0; j < a.m[0].c; j++) {
            if (i != r && j != c) {
                int exist = 0;
                for (int k = 1; k <= a.m[0].v; k++) {
                    if (a.m[k].r == i && a.m[k].c == j) {
                        int cnow = 0;
                        int tmp = a.m[k].v;
                        while (tmp) {
                            cnow++;
                            tmp /= 10;
                        }
                        for (int i = 0; i < cnt - cnow; i++) {
                            printf(" ");
                        }

                        printf("%d ", a.m[k].v);
                        exist = 1;
                        break;
                    }
                }
                if (!exist) {
                    for (int sp = 0; sp < cnt - 1; sp++) printf(" ");
                    printf("0 ");
                }
            }
        }
        printf("\n");
    }
}
Matrix operator*(Matrix a, Matrix b) {
    Matrix ret;
    ret = init(1);
    if (a.m[0].c != b.m[0].r) {
        printf("first Matrix's column must be equal second Matrix's row\n");
        ret.name[0] = '\0';
        return ret;
    }
    ret.m[0].v = 0;
    strcpy(ret.name, a.name);
    strcat(ret.name, b.name);
    ret.m[0].r = a.m[0].r;
    ret.m[0].c = b.m[0].c;
    for (int i = 1; i <= a.m[0].v; ++i) {
        for (int j = 1; j <= b.m[0].v; ++j) {
            if (a.m[i].c == b.m[j].r) {
                int exist = 0;
                for (int k = 1; k <= ret.m[0].v; ++k) {
                    if (ret.m[k].r == a.m[i].r && ret.m[k].c == b.m[j].c) {
                        ret.m[k].v += a.m[i].v * b.m[j].v;
                        exist = 1;
                        break;
                    }
                }
                if (!exist) {
                    ret.m[ret.m[0].v + 1].r = a.m[i].r;
                    ret.m[ret.m[0].v + 1].c = b.m[j].c;
                    ret.m[ret.m[0].v + 1].v = a.m[i].v * b.m[j].v;
                    ++ret.m[0].v;
                }
                // printMartix(ret);
                // printf("\n");
            }
        }
    }
    sort(ret.m + 1, ret.m + 1 + ret.m[0].v);
    return ret;
}
Matrix merge(Matrix a, Matrix b) {
    Matrix ret;
    ret.m[0].v = 0;
    strcpy(ret.name, a.name);
    strcat(ret.name, b.name);
    if (a.m[0].r != b.m[0].r || a.m[0].c != b.m[0].c) {
        printf(
            "first Matrix's column and row must be equal second Matrix's "
            "column and row\n");
        ret.name[0] = '\0';
        return ret;
    }
    ret.m[0].r = a.m[0].r;
    ret.m[0].c = a.m[0].c;
    for (int i = 1; i <= a.m[0].v; ++i) {
        for (int j = 1; j <= b.m[0].v; ++j) {
            if (a.m[i].r == b.m[j].r && a.m[i].c == b.m[j].c) {
                if (a.m[i].v * b.m[i].v) {
                    ++ret.m[0].v;
                    ret.m[ret.m[0].v].r = a.m[i].r;
                    ret.m[ret.m[0].v].c = a.m[i].c;
                    ret.m[ret.m[0].v].v = a.m[i].v * b.m[i].v;
                }
                break;
            }
        }
    }

    sort(ret.m + 1, ret.m + 1 + ret.m[0].v);
    return ret;
}
Matrix reverse(Matrix a) {
    Matrix ret;
    strcpy(ret.name, a.name);
    int *row_terms, *startposition;
    row_terms = (int *)calloc(a.m[0].c, sizeof(int));
    // memset(row_terms, 0, a.m[0].c);
    startposition = (int *)calloc(a.m[0].c, sizeof(int));
    // memset(startposition, 0, a.m[0].c);
    ret.m[0].c = a.m[0].r;
    ret.m[0].r = a.m[0].c;
    ret.m[0].v = a.m[0].v;
    for (int i = 1; i <= a.m[0].v; i++) {
        row_terms[a.m[i].c]++;
    }
    startposition[0] = 1;
    for (int i = 1; i <= a.m[0].c; i++) {
        startposition[i] = startposition[i - 1] + row_terms[i - 1];
    }
    for (int i = 1; i <= a.m[0].v; i++) {
        element tmp;
        tmp.r = a.m[i].c;
        tmp.c = a.m[i].r;
        tmp.v = a.m[i].v;
        ret.m[startposition[a.m[i].c]++] = tmp;
    }
    sort(ret.m + 1, ret.m + 1 + ret.m[0].v);
    free(row_terms);
    free(startposition);
    return ret;
}
Matrix power(Matrix a, int n) {
    if (a.m[0].r != a.m[0].c) {
        printf("Matrix's column be equal row\n");
        Matrix ret;
        ret.name[0] = '\0';
        return ret;
    }
    // printf("%d:\n", n);
    if (!n) return init(a.m[0].r);
    if (n == 1) return a;
    Matrix tmp = power(a, n >> 1);
    tmp = tmp * tmp;
    if (n % 2) tmp = tmp * a;
    // printMartix(tmp);
    return tmp;
}
int check(char *name, int length) {
    for (int i = 0; i < length; i++) {
        if (!strcmp(arr[i].name, name)) {
            return 1;
        }
    }
    return 0;
}
int index(char *name, int length) {
    if (check(name, length)) {
        for (int i = 0; i < length; i++) {
            if (!strcmp(arr[i].name, name)) {
                return i;
            }
        }
    }
    return -1;
}
int main() {
    system(cl);
    int n;
    int length = 0;
    char name[100];
    char name1[100];
    char name2[100];
    int exist = 0;
    int step = 0;
    while (1) {
        printf("0.exit\n");
        printf("1.input a new Martix\n");
        printf("2.show a Martix\n");
        printf("3.show a subMartix\n");
        printf("4.show a reverse Matrix\n");
        printf("5.show two Matrix element-wise product\n");
        printf("6.show two Matrix time\n");
        printf("7.show Matrix power\n");
        printf("8.show all Matrix's name\n");
        printf("what function do you want to do?");

        scanf("%d", &step);
        switch (step) {
            case 0:
                system(cl);
                return 0;
            case 1:
                printf("waht Matrix name?");
                scanf("%s", name);
                if (!check(name, length)) {
                    strcpy(arr[length].name, name);
                    int r, c;
                    printf("how many row in this Matrix?");
                    scanf("%d", &arr[length].m[0].r);
                    printf("how many column in this Matrix?");
                    scanf("%d", &arr[length].m[0].c);
                    for (int i = 0; i < arr[length].m[0].r; i++) {
                        for (int j = 0; j < arr[length].m[0].c; j++) {
                            int v;
                            scanf("%d", &v);
                            if (v) {
                                arr[length].m[0].v++;
                                arr[length].m[arr[length].m[0].v].v = v;
                                arr[length].m[arr[length].m[0].v].r = i;
                                arr[length].m[arr[length].m[0].v].c = j;
                            }
                        }
                    }
                    length++;
                } else {
                    printf("there have the same name Matrix\n");
                }
                break;
            case 2:
                printf("Which Matrix you want to print\n");
                scanf("%s", name);
                if (!check(name, length)) {
                    printf("There is no this Matrix\n");
                } else
                    printMartix(arr[index(name, length)]);
                break;
            case 3:
                printf("Which Matrix you want to print\n");
                scanf("%s", name);
                if (check(name, length)) {
                    int r, c;
                    printf("Which row you DON'T want to print\n");
                    scanf("%d", &r);
                    printf("Which column you DON'T want to print\n");
                    scanf("%d", &c);
                    submatrix(arr[index(name, length)], r, c);
                } else
                    printf("There is no this Matrix\n");

                break;
            case 4:
                printf("Which Matrix you want to reverse\n");
                scanf("%s", name);
                if (check(name, length)) {
                    printMartix(reverse(arr[index(name, length)]));
                } else
                    printf("There is no this Matrix\n");
                break;
            case 5:
                printf(
                    "Which two Matrix you want to do element-wise product\n");
                printf("first Martix:");
                scanf("%s", name1);
                if (check(name1, length)) {
                    printMartix(arr[index(name1, length)]);
                } else {
                    printf("the Matrix name %s is not exist\n", name1);
                    break;
                }
                printf("second Matrix:");
                scanf("%s", name2);
                if (check(name2, length)) {
                    printMartix(arr[index(name2, length)]);
                } else {
                    printf("the Matrix name %s is not exist\n", name2);
                    break;
                }
                printf("element-wise Matrix:\n");
                printMartix(merge(arr[index(name1, length)],
                                  arr[index(name2, length)]));
                break;
            case 6:
                printf("Which two Matrix you want to do time\n");
                printf("first Martix:");
                scanf("%s", name1);
                if (check(name1, length)) {
                    printMartix(arr[index(name1, length)]);
                } else {
                    printf("the Matrix name %s is not exist\n", name1);
                    break;
                }
                printf("second Matrix:");
                scanf("%s", name2);
                if (check(name2, length)) {
                    printMartix(arr[index(name2, length)]);
                } else {
                    printf("the Matrix name %s is not exist\n", name2);
                    break;
                }
                printf("time Matrix:\n");
                printMartix(arr[index(name1, length)] *
                            arr[index(name2, length)]);
                break;
            case 7:
                printf("Which Matrix you want to do power\n");
                scanf("%s", name);
                if (check(name, length)) {
                    printMartix(arr[index(name, length)]);
                } else {
                    printf("There is no Matrix name %s\n", name);
                    break;
                }
                printf("input the power\n");
                int k;
                scanf("%d", &k);
                if (k < 0) {
                    printf("the power must >= 0\n");
                    break;
                }
                printf("%s^%d:\n", name, k);
                if (arr[index(name, length)].m[0].r ==
                    arr[index(name, length)].m[0].c)
                    printMartix(power(arr[index(name, length)], k));
                else
                    printf("%s can't do the power\n", name);
                break;
            case 8:
                for (int i = 0; i < length; i++) {
                    printf("%s\n", arr[i].name);
                }
                break;
            default:
                printf("Error, you should input 0~8\n");
                break;
        }
        wait system(cl);
    }
}