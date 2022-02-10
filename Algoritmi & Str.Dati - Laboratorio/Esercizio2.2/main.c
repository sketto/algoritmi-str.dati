#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define RED 1
#define BLACK 0

int randSeed = 200;

struct treeNode
{

    int key;
    struct treeNode *parent;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
};

struct tree
{

    int cardinality;
    struct treeNode *root;
};

struct treeNodeRB
{

    int key;
    int color;
    struct treeNodeRB *parent;
    struct treeNodeRB *leftChild;
    struct treeNodeRB *rightChild;
};

struct treeRB
{

    int cardinality;
    struct treeNodeRB *root;
};

void printBstTree(struct tree *t)
{
    printf("\nROOT key: %d\n", t->root->key);

    if (t->root->leftChild != NULL)
    {
        printf("\nleft sub-tree\n");
        struct treeNode *child = t->root->leftChild;
        printf("%d\n", child->key);

        while (child->leftChild != NULL)
        {
            child = child->leftChild;
            printf("%d\n", child->key);
        }
    }
    if (t->root->rightChild != NULL)
    {
        printf("\nright sub-tree\n");
        struct treeNode *child = t->root->rightChild;
        printf("%d\n", child->key);

        while (child->rightChild != NULL)
        {
            child = child->rightChild;
            printf("%d\n", child->key);
        }
    }

    // if (t->root->rightChild != NULL)
    // {
    //     printf("-->%d\n", t->root->rightChild->key);
    // }
}

void bstTreeInsert(struct tree *t, struct treeNode *z)
{
    struct treeNode *y = NULL;
    struct treeNode *x = t->root;

    while (x != NULL)
    {
        y = x;

        if (z->key <= x->key)
        {
            x = x->leftChild;
        }
        else
        {
            x = x->rightChild;
        }
    }

    z->parent = y;

    if (y == NULL)
    {
        t->root = z;
    }

    if (y != NULL && z->key <= y->key)
    {
        y->leftChild = z;
    }

    if (y != NULL && z->key > y->key)
    {
        y->rightChild = z;
    }
}

struct treeNode *getRandomNode()
{

    struct treeNode *node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;

    node->key = rand() % randSeed;

    return node;
}

struct treeNode *bstTreeSearch(struct treeNode *x, int key)
{
    if (x == NULL || x->key == key)
    {
        return x;
    }

    if (key <= x->key)
    {
        return bstTreeSearch(x->leftChild, key);
    }
    else
    {
        return bstTreeSearch(x->rightChild, key);
    }
}

void bstTreeTransplant(struct tree *t, struct treeNode *u, struct treeNode *v)
{
    if (u->parent == NULL)
    {
        t->root = v;
    }

    if (u->parent != NULL && u == u->parent->leftChild)
    {
        u->parent->leftChild = v;
    }

    if (u->parent != NULL && u == u->parent->rightChild)
    {
        u->parent->rightChild = v;
    }

    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

struct treeNode *bstTreeMinimum(struct treeNode *x)
{
    if (x->leftChild == NULL)
    {
        return x;
    }

    return bstTreeMinimum(x->leftChild);
}

void bstTreeDelete(struct tree *t, struct treeNode *z)
{
    if (z->leftChild == NULL)
    {
        bstTreeTransplant(t, z, z->rightChild);
    }

    if (z->leftChild != NULL && z->rightChild == NULL)
    {
        bstTreeTransplant(t, z, z->leftChild);
    }

    if (z->leftChild != NULL && z->rightChild != NULL)
    {
        struct treeNode *y = bstTreeMinimum(z->rightChild);

        if (y->parent != z)
        {
            bstTreeTransplant(t, y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parent = y;
        }

        bstTreeTransplant(t, z, y);
        y->leftChild = z->leftChild;
        y->leftChild->parent = y;
    }

    free(z);
}

void deleteTree(struct treeNode *node)
{
    if (node->leftChild)
    {
        deleteTree(node->leftChild);
        free(node->leftChild);
    }
    if (node->rightChild)
    {
        deleteTree(node->rightChild);
        free(node->rightChild);
    }
}

void empty(struct tree *t)
{
    if (t->root != NULL)
    {
        deleteTree(t->root);
    }

    free(t);
}

void treeRightRotate(struct treeRB *t, struct treeNodeRB *x)
{

    struct treeNodeRB *y = x->leftChild;
    x->leftChild = y->rightChild;

    if (y->rightChild != NULL)
    {
        y->rightChild->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL)
    {
        t->root = y;
    }

    if (x->parent != NULL && x == x->parent->leftChild)
    {
        x->parent->leftChild = y;
    }

    if (x->parent != NULL && x == x->parent->rightChild)
    {
        x->parent->rightChild = y;
    }

    y->rightChild = x;
    x->parent = y;
}

void treeLeftRotate(struct treeRB *t, struct treeNodeRB *x)
{
    struct treeNodeRB *y = x->rightChild;
    x->rightChild = y->leftChild;

    if (y->leftChild != NULL)
    {
        y->leftChild->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL)
    {
        t->root = y;
    }

    if (x->parent != NULL && x == x->parent->leftChild)
    {
        x->parent->leftChild = y;
    }

    if (x->parent != NULL && x == x->parent->rightChild)
    {
        x->parent->rightChild = y;
    }

    y->leftChild = x;
    x->parent = y;
}

void rbtTreeInsertFixUpLeft(struct treeRB *t, struct treeNodeRB *z)
{
    struct treeNodeRB *y = z->parent->parent->rightChild;

    // CASO 1
    if (y->color == RED)
    {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
    }
    else
    {

        // CASO 3
        if (z == z->parent->rightChild)
        {
            z = z->parent;
            treeLeftRotate(t, z);
        }

        // CASO 2
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        treeRightRotate(t, z->parent->parent);
    }
}

void rbtTreeInsertFixUpRight(struct treeRB *t, struct treeNodeRB *z)
{
    struct treeNodeRB *y = z->parent->parent->leftChild;

    // CASO 1
    if (y->color == RED)
    {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
    }
    else
    {

        // CASO 3
        if (z == z->parent->leftChild)
        {
            z = z->parent;
            treeRightRotate(t, z);
        }

        // CASO 2
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        treeLeftRotate(t, z->parent->parent);
    }
}

void rbtTreeInsertFixUp(struct treeRB *t, struct treeNodeRB *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->leftChild)
        {
            rbtTreeInsertFixUpLeft(t, z);
        }
        else
        {

            rbtTreeInsertFixUpRight(t, z);
        }

        t->root->color = BLACK;
    }
}

void rbtTreeInsert(struct treeRB *t, struct treeNodeRB *z)
{
    struct treeNode *y = NULL;
    struct treeNode *x = t->root;

    while (x != NULL)
    {
        y = x;

        if (z->key < x->key)
        {
            x = x->leftChild;
        }
        else
        {
            x = x->rightChild;
        }
    }

    z->parent = y;

    if (y == NULL)
    {
        t->root = z;
    }

    if (y != NULL && z->key <= y->key)
    {
        y->leftChild = z;
    }

    if (y != NULL && z->key > y->key)
    {
        y->rightChild = z;
    }

    z->leftChild = NULL;
    z->rightChild = NULL;
    z->color = RED;

    rbtTreeInsertFixUp(t, z);
}

double singleExperiment(int maxKeys, int maxSearch, int maxDelete, int maxInstances)
{

    clock_t t_tot = 0;
    int i, j;

    for (i = 0; i < maxInstances; i++)
    {
        // initialize(T)
        struct tree *t = (struct tree *)malloc(sizeof(struct tree));
        t->root = NULL;

        clock_t t_start, t_end, t_elapsed;

        t_start = clock();

        for (j = 0; j < maxKeys; j++)
        {
            bstTreeInsert(t, getRandomNode());
        }

        for (j = 0; j < maxSearch; j++)
        {
            bstTreeSearch(t->root, getRandomNode()->key);
        }

        for (j = 0; j < maxDelete; j++)
        {
            bstTreeDelete(t, getRandomNode());
        }

        t_end = clock();

        t_elapsed = t_end - t_start;

        t_tot = t_tot + t_elapsed;

        // empty()
        empty(t);
    }

    return (double)t_tot / (double)maxKeys;
}

void experiment(int minKeys, int maxKeys)
{

    int maxInstances = 5;
    int step = 10;
    int percentageSearch = 60;
    int keys, maxSearch, maxDelete;

    for (keys = minKeys; keys <= maxKeys; keys += step)
    {
        srand(randSeed);
        maxSearch = keys * percentageSearch / 100;
        maxDelete = keys - maxSearch;
        clock_t time = singleExperiment(keys, maxSearch, maxDelete, maxInstances);

        printf("\ntime: %ld", (long int)time);
        randSeed++;
    }
}

int main()
{

    experiment(1, 50);

    // struct tree t;
    // t.root = NULL;
    // t.cardinality = 0;

    // int i;

    // int array[] = {3, 9, 1, 2, 22, 12, 98, 54, 31, 0};

    // for (i = 0; i < 10; i++)
    // {
    //     struct treeNode *node = (struct treeNode *)malloc(sizeof(struct treeNode));
    //     node->leftChild = NULL;
    //     node->rightChild = NULL;
    //     node->parent = NULL;
    //     node->key = array[i];
    //     bstTreeInsert(&t, node);
    //     t.cardinality++;
    //     printf("\ni: %d\n", i);
    // }

    // printBstTree(&t);
    // printf("\n%d\n", t.root->key);
    // printf("\n%d\n", t.root->leftChild->key);
    // printf("\n%d\n", t.root->rightChild->key);

    return 0;
}