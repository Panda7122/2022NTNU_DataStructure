#ifndef _TREE_H
#define _TREE_H
#include <iostream>

#include "list.h"
#include "queue.h"
class Tree {
   private:
    struct treeNode {
        char val;
        treeNode *left, *right;
        treeNode operator=(char b) {
            val = b;
            return *this;
        }
    };
    treeNode root;

   public:
    Tree operator=(char b) {
        this->root.val = b;
        return *this;
    }
    Tree() {
        root.val = 0;
        root.left = root.right = nullptr;
    }
    void setUp(char V) { root.val = V; }
    treeNode* Root() { return &root; }

    char* postfix(treeNode now) {
        char* ret;
        ret = new char[1000];
        ret[0] = '\0';
        // printf("%c", now.val);
        if (now.left != nullptr) {
            strcat(ret, postfix(*(now.left)));
            // printf("fl");
        }
        // else
        // printf("el");
        if (now.right != nullptr) {
            strcat(ret, postfix(*(now.right)));
            // printf("fr");
        }
        // else
        // printf("er");
        char nowv = now.val;
        char temp[2];
        temp[0] = nowv;
        temp[1] = '\0';
        strcat(ret, temp);
        return ret;
    }
    char* prefix(treeNode now) {
        // printf("%c", now.val);
        char nowv = now.val;
        char* ret;
        ret = new char[1000];
        ret[0] = nowv;
        ret[1] = '\0';
        if (now.left != nullptr) {
            char* arrl = prefix(*(now.left));
            strcat(ret, arrl);
        }
        // else
        // printf("el");
        if (now.right != nullptr) {
            char* arrr = prefix(*(now.right));
            strcat(ret, arrr);
        }
        // else
        // printf("er");
        return ret;
    }

    char* level_order() {
        char* ret;
        ret = new char[1000];
        ret[0] = '\0';
        Queue<treeNode> now;
        now.push(root);
        while (!now.empty()) {
            if (now.front().left != nullptr) {
                now.push(*(now.front().left));
            }
            if (now.front().right != nullptr) {
                now.push(*(now.front().right));
            }
            char temp[2];
            temp[0] = now.front().val;
            temp[1] = '\0';
            strcat(ret, temp);
            now.pop();
        }
        return ret;
    }
    double calculation(treeNode* now) {
        double ans = 0;
        if (now->left == nullptr && now->right == nullptr)
            return (double)(now->val - '0');
        if (now->left != nullptr) ans = calculation(now->left);
        switch (now->val) {
            case '+':
                if (now->right != nullptr) ans += calculation(now->right);
                break;
            case '-':
                if (now->right != nullptr) ans -= calculation(now->right);
                break;
            case '*':
                if (now->right != nullptr) ans *= calculation(now->right);
                break;
            case '/':
                if (now->right != nullptr) ans /= calculation(now->right);
                break;
        }
        return ans;
    }
    Tree merge(Tree a, Tree b, char sign) {
        Tree ret;
        // printf("merge: %c %c %c\n", a.Root()->val, b.Root()->val,
        //    ret.Root()->val);
        ret.Root()->left = new treeNode;
        ret.Root()->left->val = a.Root()->val;
        ret.Root()->left->left = a.Root()->left;
        ret.Root()->left->right = a.Root()->right;
        ret.Root()->right = new treeNode;
        ret.Root()->right->val = b.Root()->val;
        ret.Root()->right->left = b.Root()->left;
        ret.Root()->right->right = b.Root()->right;
        ret.Root()->val = sign;
        return ret;
    }
};
#endif