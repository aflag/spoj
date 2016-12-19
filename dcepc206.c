#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

struct tree {
    struct tree *left;
    struct tree *right;
    int64_t value;
    int64_t replicas;
    int64_t sum;
};

struct tree nodes[100000];
int64_t tree_pointer = 0;

int free_tree() {
    tree_pointer = 0;
}

struct tree* alloc_tree() {
    return &nodes[tree_pointer++];
}

#define MKTREE(t, v) do { \
    t = alloc_tree(); \
    t->left = NULL; \
    t->right = NULL; \
    t->value = v; \
    t->sum = 0; \
    t->replicas = 1; \
} while(0)

int64_t insert(struct tree* t, int64_t value) {
    struct tree *current = t;
    int64_t s = 0;
    while (1) {
        if (current->value == value) {
            current->replicas++;
            return current->sum + s;
        } else if (current->value < value) {
            s += current->value*current->replicas + current->sum;
            if (!current->right) {
                MKTREE(current->right, value);
                return s;
            } else {
                current = current->right;
            }
        } else {
            current->sum += value;
            if (!current->left) {
                MKTREE(current->left, value);
                return s;
            } else {
                current = current->left;
            }
        }
    }
}

int64_t solve(int64_t stairs[], int size) {
    int i;
    int64_t total = 0, tmp;
    struct tree *t;
    MKTREE(t, stairs[0]);

    for (i = 1; i < size; i++) {
        total += insert(t, stairs[i]);
    }

    free_tree();

    return total;
}

int main(void) {
    int i, t;
    int tests;
    int steps;
    int64_t stairs[100000];

    scanf("%d", &tests);
    for (t = 0; t < tests; t++) {
        scanf("%d", &steps);
        for (i = 0; i < steps; i++) {
            scanf("%" PRIu64, &stairs[i]);
        }
        printf("%" PRIu64 "\n", solve(stairs, steps));
    }
}
