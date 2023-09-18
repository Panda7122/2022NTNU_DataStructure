#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>

#include "list.h"
#define ll int64_t
using namespace std;
List<int32_t> graph[30];
int32_t n, m, t;
int32_t pass[30] = {0};
int32_t ans1 = 0;
int32_t ring[30] = {0};
int32_t ans3 = 2147483647;
int32_t haver = 0;
char nowchar;
void dfs(int32_t now) {
    if (pass[now]) return;
    pass[now] = 1;
    List<int32_t>::node *tmp = graph[now].first.next;
    while (tmp != &graph[now].first) {
        dfs(tmp->val);
        tmp = tmp->next;
    }
    return;
}
bool test(int now, int parent) {
    // printf("%d->%d", parent, now);
    if (pass[now]) {
        // printf(" 1\n");
        return 1;
    }
    // printf("\n");
    pass[now] = 1;
    List<int32_t>::node *tmp = graph[now].first.next;
    int32_t ret = 0;
    int32_t cnt = 0;
    while (tmp != &graph[now].first) {
        if (ring[tmp->val]) haver = 1;
        if (!ring[tmp->val] && tmp->val != parent) {
            if (test(tmp->val, now)) ret = 1;
            if (cnt) ret = 1;
            cnt++;
        }
        tmp = tmp->next;
    }
    return ret;
}
void countMin(int now, int cnt) {
    if (cnt > n / 2) return;
    if (now > n) {
        int circle = 0;
        int ans = 0;
        int compos = 0;
        memset(pass, 0, sizeof(pass));
        int pt = 0;
        for (int i = 1; i <= n; ++i) {
            if (ring[i]) ans++;
            if (!pass[i] && !ring[i]) {
                compos++;
                haver = 0;
                if (test(i, -1)) {
                    circle = 1;
                }
                if (!haver) {
                    if (pt) {
                        circle = 1;
                    } else
                        pt = 1;
                }
            }
        }
        if (!circle && compos <= cnt + 1) {
            ans3 = min(ans3, ans);
        }
        return;
    }
    ring[now] = 1;
    countMin(now + 1, cnt + 1);
    ring[now] = 0;
    countMin(now + 1, cnt);
}
int main() {
    FILE *fptr;
    fptr = fopen("test.txt", "r");
    nowchar = ' ';
    t = 0;
    while (nowchar == ' ' || nowchar == '\n') nowchar = fgetc(fptr);
    while (1) {
        t *= 10;
        t += nowchar - '0';
        nowchar = fgetc(fptr);
        if (nowchar == ' ') break;
        if (nowchar == '\n') break;
    }
    // scanf("%d", &t);
    // printf("%d\n", t);
    for (int T = 1; T <= t; ++T) {
        memset(pass, 0, sizeof(pass));
        memset(ring, 0, sizeof(ring));
        ans3 = 2147483647;
        ans1 = 0;
        n = 0;
        m = 0;
        for (int i = 0; i < 30; ++i) graph[i].clear();
        // scanf("%d%d", &n, &m);
        while (nowchar == ' ' || nowchar == '\n') nowchar = fgetc(fptr);
        while (1) {
            n *= 10;
            n += nowchar - '0';
            nowchar = fgetc(fptr);
            if (nowchar == ' ') break;
            if (nowchar == '\n') break;
        }
        while (nowchar == ' ' || nowchar == '\n') nowchar = fgetc(fptr);
        while (1) {
            // printf("%c", nowchar);
            m *= 10;
            m += nowchar - '0';
            nowchar = fgetc(fptr);
            if (nowchar == ' ') break;
            if (nowchar == '\n') break;
        }
        // printf("%d %d\n", n, m);
        for (int32_t i = 0; i < m; ++i) {
            int32_t a = 0, b = 0;
            // scanf("%d%d", &a, &b);
            while (nowchar == ' ' || nowchar == '\n') nowchar = fgetc(fptr);
            while (1) {
                a *= 10;
                a += nowchar - '0';
                nowchar = fgetc(fptr);
                if (nowchar == ' ') break;
                if (nowchar == '\n') break;
            }
            while (nowchar == ' ' || nowchar == '\n') nowchar = fgetc(fptr);
            while (1) {
                b *= 10;
                b += nowchar - '0';
                nowchar = fgetc(fptr);
                if (nowchar == ' ') break;
                if (nowchar == '\n') break;
            }
            // printf("%d %d\n", a, b);
            if (a > n || a < 1 || b > n || b < 1) {
                printf("it had to in [1, %d]", n);
                return 0;
            }
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        for (int32_t i = 1; i <= n; ++i) {
            if (!pass[i]) {
                dfs(i);
                ans1++;
            }
        }

        char inputc[1000];
        int nowc = 0;
        while (nowchar == ' ' || nowchar == '\n') nowchar = fgetc(fptr);
        while (1) {
            inputc[nowc] = nowchar;
            // printf("%c", inputc[nowc]);
            if (inputc[nowc] == '\n') {
                inputc[nowc] = '\0';
                break;
            }
            nowc++;
            nowchar = fgetc(fptr);
        }
        int cnt = 0;
        int cloc = 0;
        int ringcnt = 0;
        while (inputc[cloc] == ' ') cloc++;
        for (int i = cloc; i < nowc; ++i) {
            if (inputc[i] == ' ') {
                ring[cnt] = 1;
                ringcnt++;
                cnt = 0;
            } else {
                cnt *= 10;
                cnt += inputc[i] - '0';
            }
        }
        ringcnt++;
        ring[cnt] = 1;
        printf("Task #%d:\n", T);
        printf("%d ", ans1);
        // for (int i = 1; i <= n; ++i) {
        //     printf("%d ", ring[i]);
        // }
        int circle = 0;
        memset(pass, 0, sizeof(pass));
        int pt = 0;
        int compos = 0;
        for (int i = 1; i <= n; ++i) {
            if (!pass[i] && !ring[i]) {
                haver = 0;
                compos++;
                if (test(i, -1)) {
                    circle = 1;
                    break;
                }
                if (!haver) {
                    if (pt) {
                        circle = 1;
                        break;
                    } else
                        pt = 1;
                }
            }
        }
        if (!circle && compos <= ringcnt + 1)
            printf("Yes ");
        else
            printf("No ");
        memset(pass, 0, sizeof(pass));
        memset(ring, 0, sizeof(ring));
        countMin(1, 0);
        printf("%d\n", ans3);
    }
}