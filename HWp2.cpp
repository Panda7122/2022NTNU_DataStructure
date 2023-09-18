#include <math.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <string>
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
using namespace std;
struct term {
    double coef;
    int pow;
};
struct node {
    term v;
    node *nxt;
    node *last;
};

struct link_list {
    node *first;
    int size;
    link_list operator=(const link_list inp) {
        this->clear();
        node *tmpa = inp.first->nxt;
        for (int i = 0; i < inp.size; ++i) {
            this->push(tmpa->v.coef, tmpa->v.pow);
            tmpa = tmpa->nxt;
        }
        return *this;
    }
    void erase(node *loc) {
        node *l = loc->last;
        node *r = loc->nxt;
        l->nxt = r;
        r->last = l;
        --this->size;
        delete loc;
    }
    void clear() {
        while (this->first->last != this->first) this->erase(this->first->last);
        this->size = 0;
    }
    link_list() {
        this->first = (node *)malloc(sizeof(node));
        this->first->nxt = this->first;
        this->first->last = this->first;
        this->clear();
    }
    void insert(node *loc, term v) {
        node *l = loc;
        node *r = loc->nxt;
        node *new_node = new node;
        l->nxt = new_node;
        new_node->last = l;
        new_node->nxt = r;
        new_node->v = v;
        r->last = new_node;
        this->size++;
        return;
    }
    void push(double v, int c) {
        node *tmp;
        tmp = this->first->nxt;
        term temp;
        temp.coef = v;
        temp.pow = c;
        for (int i = 0; i < this->size; i++) {
            if (tmp->v.pow < c) {
                insert(tmp->last, temp);
                return;
            }
            if (tmp->v.pow == c) {
                tmp->v.coef += v;
                if (tmp->v.coef == 0) {
                    this->erase(tmp);
                }
                return;
            }
            tmp = tmp->nxt;
        }
        insert(tmp->last, temp);
    }
    void pop(int c) {
        node *tmp;
        tmp = this->first->nxt;
        for (int i = 0; i < this->size; i++) {
            if (tmp->v.pow == c) {
                erase(tmp);
                size--;
                return;
            }
            tmp = tmp->nxt;
        }
        return;
    }
    void print() {
        if (this->size == 0) printf("0");
        node *tmp = this->first->nxt;
        for (int i = 0; i < this->size; i++) {
            if (tmp->v.coef) {
                if (tmp->v.pow == 0) {
                    printf(" %c%c%.6g",
                           ((tmp->v.coef < 0) ? '-' : (i ? '+' : '\0')),
                           (i ? ' ' : '\0'), abs(tmp->v.coef));
                } else if (tmp->v.pow == 1) {
                    if (abs(tmp->v.coef) == 1)
                        printf(" %c%cx",
                               ((tmp->v.coef < 0) ? '-' : (i ? '+' : '\0')),
                               i ? ' ' : '\0');
                    else
                        printf(" %c%c%.6gx",
                               ((tmp->v.coef < 0) ? '-' : (i ? '+' : '\0')),
                               i ? ' ' : '\0', abs(tmp->v.coef));
                } else {
                    if (abs(tmp->v.coef == 1))
                        printf(" %c%cx^%d",
                               ((tmp->v.coef < 0) ? '-' : (i ? '+' : '\0')),
                               i ? ' ' : '\0', tmp->v.pow);
                    else
                        printf(" %c%c%.6gx^%d",
                               ((tmp->v.coef < 0) ? '-' : (i ? '+' : '\0')),
                               i ? ' ' : '\0', abs(tmp->v.coef), tmp->v.pow);
                }
            }
            tmp = tmp->nxt;
        }
        printf("\n");
        return;
    }
};
struct Polynomial {
    link_list poly;
    string name;
    Polynomial() { this->name = "empty"; }
    link_list add(Polynomial poly2) {
        link_list ret;
        ret = this->poly;
        node *tmp = poly2.poly.first->nxt;
        for (int i = 0; i < poly2.poly.size; i++) {
            ret.push(tmp->v.coef, tmp->v.pow);
            tmp = tmp->nxt;
        }
        tmp = ret.first->nxt;
        int c = ret.size;
        for (int i = 0; i < c; i++) {
            if (tmp->v.coef == 0) {
                tmp = tmp->last;
                ret.erase(tmp->nxt);
            }
            tmp = tmp->nxt;
        }
        return ret;
    }
    link_list minus(Polynomial poly2) {
        link_list ret = this->poly;
        node *tmp = poly2.poly.first->nxt;
        for (int i = 0; i < poly2.poly.size; i++) {
            ret.push(-1 * (tmp->v.coef), tmp->v.pow);
            tmp = tmp->nxt;
        }
        tmp = ret.first->nxt;
        int c = ret.size;
        for (int i = 0; i < c; i++) {
            if (tmp->v.coef == 0) {
                tmp = tmp->last;
                ret.erase(tmp->nxt);
            }
            tmp = tmp->nxt;
        }
        return ret;
    }
    link_list time(Polynomial poly2) {
        link_list ret;
        node *tmp1 = this->poly.first->nxt;
        node *tmp2 = poly2.poly.first->nxt;
        for (int i = 0; i < this->poly.size; i++) {
            tmp2 = poly2.poly.first->nxt;
            for (int j = 0; j < poly2.poly.size; j++) {
                ret.push(((tmp1->v.coef) * (tmp2->v.coef)),
                         (tmp1->v.pow) + (tmp2->v.pow));
                tmp2 = tmp2->nxt;
            }
            tmp1 = tmp1->nxt;
        }
        return ret;
    }
    Polynomial *devide(Polynomial poly2) {
        Polynomial Quotient;
        Polynomial Remainder;
        Remainder.poly = poly2.poly;
        Polynomial tmp;
        tmp.poly = poly;
        Polynomial S;
        while (Remainder.poly.first->nxt->v.pow >= tmp.poly.first->nxt->v.pow) {
            term dev;
            tmp.poly.clear();
            tmp.poly = poly;
            dev.coef =
                Remainder.poly.first->nxt->v.coef / tmp.poly.first->nxt->v.coef;
            dev.pow =
                Remainder.poly.first->nxt->v.pow - tmp.poly.first->nxt->v.pow;
            Quotient.poly.push(dev.coef, dev.pow);
            node *now;
            now = tmp.poly.first->nxt;
            for (int i = 0; i < tmp.poly.size; i++) {
                now->v.coef *= dev.coef;
                now->v.pow += dev.pow;
                now = now->nxt;
            }
            tmp.poly.erase(tmp.poly.first->nxt);
            Remainder.poly.erase(Remainder.poly.first->nxt);
            S.poly = Remainder.minus(tmp);
            Remainder = S;
            tmp.poly.clear();
            tmp.poly = poly;
        }
        Polynomial *ret;
        ret = new Polynomial[2];
        ret[0] = Quotient;
        ret[1] = Remainder;
        return ret;
    }
    void print() {
        this->poly.print();
        return;
    }
    bool print_term(int p) {
        node *tmp = this->poly.first->nxt;
        for (int i = 0; i < poly.size; i++) {
            if (tmp->v.pow == p) {
                printf("%.6g%c%c", tmp->v.coef, (tmp->v.pow != 0) ? 'x' : '\0',
                       (tmp->v.pow != 1 && tmp->v.pow != 0) ? '^' : '\0');
                if ((tmp->v.pow != 1 && tmp->v.pow != 0)) {
                    printf("%d", tmp->v.pow);
                }
                printf("\n");
                return 1;
            }
            tmp = tmp->nxt;
        }
        return 0;
    }
};
Polynomial time_term(Polynomial a, term b) {
    Polynomial A = a;
    node *tmp = A.poly.first->nxt;
    for (int i = 0; i < A.poly.size; i++) {
        tmp->v.coef *= b.coef;
        tmp->v.pow += b.pow;
        tmp = tmp->nxt;
    }
    return A;
}
int main() {
    int step;
    Polynomial arr[10000];
    int length = 0;
    string n;
    int pow[1000];
    double coef[1000];
    bool have2 = 0;
    while (1) {
        printf("0.exit\n");
        printf("1.input a new Polynomial\n");
        printf("2.show a Polynomial\n");
        printf("3.show a term of a Polynomial\n");
        printf("4.add/delete a term of a Polynomial\n");
        printf("5.add two Polynomials\n");
        printf("6.minus two Polynomials\n");
        printf("7.time two Polynomials\n");
        printf("8.devide two Polynomials(p2/p1)\n");
        printf("9 show all name of Polynomials\n");
        printf("what function do you want to do?");
        scanf("%d", &step);
        char tmp_name[1000];
        bool have = 0;
        bool have_term = 0;
        char input[10000];
        char c;
        int l = 0;
        double tmp_coef = 0;
        int tmp_power = 0;
        int cnt = 0;
        int mode = 0;
        int mathmode = 0;
        int p = 0;
        int counter = 0;
        switch (step) {
            case 0:
                wait system(cl);
                return 0;
            case 1:
                have = 0;
                l = 0;
                tmp_coef = 0;
                tmp_power = 0;
                cnt = 0;
                mode = 0;
                counter = 1;
                mathmode = 0;
                printf("What is this Polynomial's name?");
                scanf("%s", tmp_name);

                while (getchar() != '\n')
                    ;
                n = tmp_name;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        printf("there have same name Polynomial\n");
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    arr[length].name = n;
                    printf("input the Polynomial like(ax^b+cx^d...)\n");
                    while ((c = getchar()) != '\n') {
                        input[l] = c;
                        l++;
                    }
                    memset(pow, 0, sizeof(pow));
                    memset(coef, 0, sizeof(coef));
                    for (int i = 0; i < l; i++) {
                        if (input[i] == 'x' || input[i] == 'X') {
                            tmp_power = 1;
                            mathmode = 0;
                        } else if (input[i] == '+') {
                            if (tmp_coef == 0) tmp_coef = 1;
                            coef[cnt] = tmp_coef;
                            coef[cnt] /= counter;
                            pow[cnt++] = tmp_power;
                            counter = 1;
                            tmp_coef = 0;
                            tmp_power = 0;
                            mode = 0;
                            mathmode = 0;
                        } else if (input[i] == '^') {
                            mode = 1;
                            tmp_power = 0;
                        } else if (input[i] == '-') {
                            if (tmp_coef == 0) tmp_coef = 1;
                            coef[cnt] = tmp_coef;
                            coef[cnt] /= counter;
                            pow[cnt++] = tmp_power;
                            counter = 1;
                            tmp_coef = 0;
                            tmp_power = 0;
                            mode = -1;
                            mathmode = 0;
                        } else if (input[i] == '.') {
                            counter = 1;
                            mathmode = 1;
                        } else if (!(input[i] == ' ')) {
                            if (mode == 1) {
                                tmp_power *= 10;
                                tmp_power += input[i] - '0';
                            } else {
                                if (mode == -1) {
                                    tmp_coef *= 10;
                                    tmp_coef -= input[i] - '0';
                                } else if (mode == 0) {
                                    tmp_coef *= 10;
                                    tmp_coef += input[i] - '0';
                                }
                            }
                            if (mathmode) {
                                counter *= 10;
                            }
                        }
                    }
                    if (tmp_coef || tmp_power) {
                        if (tmp_coef == 0) tmp_coef = 1;
                        coef[cnt] = tmp_coef;
                        coef[cnt] /= counter;
                    }
                    if (tmp_power) {
                        pow[cnt] = tmp_power;
                    }
                    if (tmp_coef || tmp_power) ++cnt;
                    for (int i = 0; i < cnt; i++) {
                        arr[length].poly.push(coef[i], pow[i]);
                    }
                    length++;
                }
                break;
            case 2:
                have = 0;
                printf("What Polynomial you want to show?");
                scanf("%s", tmp_name);
                n = tmp_name;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        arr[i].print();
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 3:
                printf("What Polynomial you want to show?");
                scanf("%s", tmp_name);
                n = tmp_name;
                have_term = 0;
                have = 0;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        have = 1;
                        printf("Which term you want to show?");
                        scanf("%d", &p);
                        have_term = arr[i].print_term(p);
                        if (!have_term) {
                            printf("There have no this term.\n");
                            break;
                        }
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 4:
                printf("What Polynomial you want to add/delete?");
                scanf("%s", tmp_name);
                n = tmp_name;
                have = 0;
                have_term = 0;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        char choose[10];
                        printf("add or delete");
                        scanf("%s", choose);
                        if (!strcmp(choose, "add")) {
                            int v;
                            printf("which term you want to add?");
                            scanf("%d", &p);
                            printf("Coefficient?");
                            scanf("%d", &v);
                            arr[i].poly.push(v, p);
                        } else if (!strcmp(choose, "delete")) {
                            printf("which term you want to delete?");
                            scanf("%d", &p);
                            node *now_choose = arr[i].poly.first->nxt;
                            for (int j = 0; j < arr[i].poly.size; j++) {
                                if (now_choose->v.pow == p) {
                                    arr[i].poly.erase(now_choose);
                                    have_term = 1;
                                    break;
                                }
                                now_choose = now_choose->nxt;
                            }
                            if (!have_term) {
                                printf("There have no this term.\n");
                                break;
                            }
                        } else {
                            printf("Error step\n");
                        }
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 5:
                printf("First Polynomial you want to add\n");
                scanf("%s", tmp_name);
                n = tmp_name;
                have2 = 0;
                have = 0;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        printf("Second Polynomial you want to add\n");
                        scanf("%s", tmp_name);
                        n = tmp_name;
                        for (int j = 0; j < length; j++) {
                            if (n == arr[j].name) {
                                printf("   ");
                                arr[i].print();
                                printf("+) ");
                                arr[j].print();
                                printf(
                                    "=========================================="
                                    "======================================\n  "
                                    " ");
                                (arr[j].add(arr[i])).print();
                                have2 = 1;
                                break;
                            }
                        }
                        if (!have2) {
                            printf("There have no this Polynomial\n");
                        }
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 6:
                printf("First Polynomial you want to minus\n");
                scanf("%s", tmp_name);
                n = tmp_name;
                have2 = 0;
                have = 0;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        printf("Second Polynomial you want to minus\n");
                        scanf("%s", tmp_name);
                        n = tmp_name;
                        for (int j = 0; j < length; j++) {
                            if (n == arr[j].name) {
                                printf("   ");
                                arr[i].print();
                                printf("-) ");
                                arr[j].print();
                                printf(
                                    "=========================================="
                                    "======================================\n  "
                                    " ");
                                arr[i].minus(arr[j]).print();
                                have2 = 1;
                                break;
                            }
                        }
                        if (!have2) {
                            printf("There have no this Polynomial\n");
                        }
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 7:
                printf("First Polynomial you want to time\n");
                scanf("%s", tmp_name);
                n = tmp_name;
                have2 = 0;
                have = 0;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        printf("Second Polynomial you want to time\n");
                        scanf("%s", tmp_name);
                        n = tmp_name;
                        for (int j = 0; j < length; j++) {
                            if (n == arr[j].name) {
                                printf("   ");
                                arr[i].print();
                                printf("*) ");
                                arr[j].print();
                                printf(
                                    "=========================================="
                                    "======================================\n  "
                                    " ");
                                arr[j].time(arr[i]).print();
                                have2 = 1;
                                break;
                            }
                        }
                        if (!have2) {
                            printf("There have no this Polynomial\n");
                        }
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 8:
                printf("First Polynomial you want to devide\n");
                scanf("%s", tmp_name);
                n = tmp_name;
                have2 = 0;
                have = 0;
                for (int i = 0; i < length; i++) {
                    if (n == arr[i].name) {
                        printf("Second Polynomial you want to devide\n");
                        scanf("%s", tmp_name);
                        n = tmp_name;
                        for (int j = 0; j < length; j++) {
                            if (n == arr[j].name) {
                                Polynomial *devide_poly;
                                printf("   ");
                                arr[j].print();
                                printf("/) ");
                                arr[i].print();
                                printf(
                                    "=========================================="
                                    "======================================\n  "
                                    " ");
                                devide_poly = arr[i].devide(arr[j]);
                                printf(" Quotient:");
                                devide_poly[0].print();
                                printf("Remainder:");
                                devide_poly[1].print();
                                have2 = 1;
                                break;
                            }
                        }
                        if (!have2) {
                            printf("There have no this Polynomial\n");
                        }
                        have = 1;
                        break;
                    }
                }
                if (!have) {
                    printf("There have no this Polynomial\n");
                }
                break;
            case 9:
                for (int i = 0; i < length; ++i) {
                    const char *name = arr[i].name.c_str();
                    printf("%s\n", name);
                }
                break;
            default:
                printf("Error, you should input 0~9\n");
                break;
        }
        wait system(cl);
    }
}