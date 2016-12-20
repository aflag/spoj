#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define MAX_STEPS 100000

struct node {
    struct node *left;
    struct node *right;
    struct node *parent;
    int64_t value;
    int64_t replicas;
    int64_t sum;
    int height;
};

struct tree {
    struct node *root;
    struct node nodes[MAX_STEPS];
    int64_t pointer;
};

int clean_tree(struct tree *t) {
    t->pointer = 0;
}

struct node* alloc_node(struct tree *t) {
    return &(t->nodes[t->pointer++]);
}

struct node* mknode(struct tree *t, struct node *current, int64_t v) {
    struct node *n = alloc_node(t); \
    n->left = NULL;
    n->right = NULL;
    n->parent = current;
    n->value = v;
    n->sum = 0;
    n->replicas = 1;
    n->height = 1;
    return n;
} 

void rotate_left(struct tree* t, struct node* n) {
    struct node **root;
    if (n->parent) {
        if (n->parent->right == n) {
            root = &n->parent->right;
        } else {
            root = &n->parent->left;
        }
    } else {
        root = &t->root;
    }
    assert(n->right);
    *root = n->right;
    (*root)->parent = n->parent;
    n->right = (*root)->left;
    if (n->right) {
        n->right->parent = n;
    }
    (*root)->left = n;
    n->parent = *root;
    (*root)->sum += (n->value*n->replicas) + n->sum;

    n->height = max_height(n->left, n->right) + 1;
    (*root)->height = max_height((*root)->left, (*root)->right) + 1;
}

void rotate_right(struct tree* t, struct node* n) {
    struct node **root;
    if (n->parent) {
        if (n->parent->right == n) {
            root = &n->parent->right;
        } else {
            root = &n->parent->left;
        }
    } else {
        root = &t->root;
    }
    assert(n->left);
    n->left->parent = n->parent;
    *root = n->left;
    n->left = n->left->right;
    if (n->left) {
        n->left->parent = n;
    }
    assert(n->sum >= ((*root)->value * (*root)->replicas) - (*root)->sum);
    n->sum = n->sum - ((*root)->value * (*root)->replicas) - (*root)->sum;
    (*root)->right = n;
    n->parent = *root;

    n->height = max_height(n->left, n->right) + 1;
    (*root)->height = max_height((*root)->left, (*root)->right) + 1;
}

int get_height(struct node *n) {
    if (!n) {
        return 0;
    } else {
        return n->height;
    }
}

int max_height(struct node *a, struct node *b) {
    int ha = get_height(a);
    int hb = get_height(b);
    return ha > hb ? ha : hb;
}

void balance(struct tree* t, struct node* n, int64_t value) {
    int diff;
    while (n) {
        diff = get_height(n->left) - get_height(n->right);

        if (diff < -1 && value > n->right->value) {
            rotate_left(t, n);
        } else if (diff > 1  && value < n->left->value) {
            rotate_right(t, n);
        } else if (diff < -1 && value < n->right->value) {
            rotate_right(t, n->right);
            rotate_left(t, n);
        } else if (diff > 1 && value > n->left->value) {
            rotate_left(t, n->left);
            rotate_right(t, n);
        }

        if (!n->left && !n->right) {
            n->height = 1;
        } else {
            n->height = max_height(n->left, n->right) + 1;
        }
        n = n->parent;
    }
}

int64_t insert(struct tree* t, int64_t value) {
    int p = 0;
    struct node *current = t->root;
    int64_t s = 0;
    while (1) {
        if (current->value == value) {
            current->replicas++;
            return current->sum + s;
        } else if (current->value < value) {
            s += current->value*current->replicas + current->sum;
            if (!current->right) {
                current->right = mknode(t, current, value);
                balance(t, current, value);
                return s;
            } else {
                current = current->right;
            }
        } else {
            current->sum += value;
            if (!current->left) {
                current->left = mknode(t, current, value);
                balance(t, current, value);
                return s;
            } else {
                current = current->left;
            }
        }
    }
}

int64_t solve(struct tree *t, int64_t stairs[], int size) {
    int i;
    int64_t total = 0;
    clean_tree(t);
    t->root = mknode(t, NULL, stairs[0]);

    for (i = 1; i < size; i++) {
        total += insert(t, stairs[i]);
    }

    return total;
}

int main(void) {
    int i, t;
    int tests;
    int steps;
    int64_t stairs[MAX_STEPS];
    struct tree tree;

    scanf("%d", &tests);
    for (t = 0; t < tests; t++) {
        scanf("%d", &steps);
        for (i = 0; i < steps; i++) {
            scanf("%" PRIu64, &stairs[i]);
        }
        printf("%" PRIu64 "\n", solve(&tree, stairs, steps));
    }
}
