#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define RED 1
#define BLACK 0
#define DEBUG_ENABLED 0

int SEED = 200;

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

struct treeNodeRB T_Nil_rbtNode;           // defining the T_Nil node
struct treeNodeRB *t_nil = &T_Nil_rbtNode; // using it as the sentinel
void init_TNIL()
{
    // t_nil = (struct treeNodeRB *)malloc(sizeof(struct treeNodeRB));
    t_nil->color = BLACK;
    t_nil->parent = t_nil;
    t_nil->leftChild = t_nil;
    t_nil->rightChild = t_nil;
};

struct treeRB
{

    int cardinality;
    struct treeNodeRB *root;
};

// struct treeNodeRBT *createRoot()
// {
//     struct treeNodeRB *temp = (struct treeNodeRB *)malloc(sizeof(struct treeNodeRB));
//     temp->key = rand() % SEED;
//     temp->color = BLACK;
//     temp->leftChild = TNIL();
//     temp->rightChild = TNIL();
//     temp->parent = TNIL();

//     return temp;
// };

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

void printRBTTree(struct treeRB *t)
{
    printf("\nROOT key: %d\n", t->root->key);

    if (t->root->leftChild != t_nil)
    {
        printf("\nleft sub-tree\n");
        struct treeNodeRB *child = t->root->leftChild;
        printf("%d\n", child->key);

        while (child->leftChild != t_nil)
        {
            child = child->leftChild;
            printf("%d\n", child->key);
        }
    }
    if (t->root->rightChild != t_nil)
    {
        printf("\nright sub-tree\n");
        struct treeNodeRB *child = t->root->rightChild;
        printf("%d\n", child->key);

        while (child->rightChild != t_nil)
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

    node->key = rand() % SEED;

    return node;
}

struct treeNodeRB *getRandomNodeRBT()
{
    struct treeNodeRB *node = (struct treeNodeRB *)malloc(sizeof(struct treeNodeRB));
    node->leftChild = t_nil;
    node->rightChild = t_nil;
    node->parent = t_nil;
    node->color = RED;

    node->key = rand() % SEED;
    // fprintf(stderr, "\nrandom node: %d, %d, %d, %d %d\n", node->color, node->key, node->leftChild, node->parent, node->rightChild);
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

struct treeNodeRB *rbtTreeSearch(struct treeNodeRB *x, int key)
{
    if (x == t_nil || x->key == key)
    {
        return x;
    }

    if (key <= x->key)
    {
        return rbtTreeSearch(x->leftChild, key);
    }
    else
    {
        return rbtTreeSearch(x->rightChild, key);
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

void deleteTreeRB(struct treeNodeRB *node)
{
    if (node->leftChild)
    {
        deleteTreeRB(node->leftChild);
        free(node->leftChild);
    }
    if (node->rightChild)
    {
        deleteTreeRB(node->rightChild);
        free(node->rightChild);
    }
}

void rbTransplant()
{
}

void rbtTreeDelete(struct treeRB *t, struct treeNodeRB *z)
{

    struct treeNodeRB *y;

    if (z->leftChild == NULL)
    {
        // bstTreeTransplant(t, z, z->rightChild);
    }

    if (z->leftChild != NULL && z->rightChild == NULL)
    {
        // bstTreeTransplant(t, z, z->leftChild);
    }

    if (z->leftChild != NULL && z->rightChild != NULL)
    {
        // struct treeNodeRB *y = bstTreeMinimum(z->rightChild);

        if (y->parent != z)
        {
            // bstTreeTransplant(t, y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parent = y;
        }

        // bstTreeTransplant(t, z, y);
        y->leftChild = z->leftChild;
        y->leftChild->parent = y;
    }

    free(z);
}

void empty(struct tree *t)
{
    if (t->root != NULL)
    {
        deleteTree(t->root);
    }

    free(t);
}

// void emptyRB(struct treeRB *t)
// {

//     // if (t->root != NULL)
//     // {
//     //     deleteTreeRB(t->root);
//     // }

//     free(t);
// }

void treeRightRotate(struct treeRB *t, struct treeNodeRB *x)
{

    // struct treeNodeRB *t_nil = TNIL();

    struct treeNodeRB *y = x->leftChild;
    x->leftChild = y->rightChild;

    if (y->rightChild != t_nil)
    {
        y->rightChild->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == t_nil)
    {
        t->root = y;
    }

    if (x->parent != t_nil && x == x->parent->leftChild)
    {
        x->parent->leftChild = y;
    }

    if (x->parent != t_nil && x == x->parent->rightChild)
    {
        x->parent->rightChild = y;
    }

    y->rightChild = x;
    x->parent = y;
}

void treeLeftRotate(struct treeRB *t, struct treeNodeRB *x)
{
    // struct treeNodeRB *t_nil = TNIL();
    struct treeNodeRB *y = x->rightChild;
    x->rightChild = y->leftChild;

    if (y->leftChild != t_nil)
    {
        y->leftChild->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == t_nil)
    {
        t->root = y;
    }

    if (x->parent != t_nil && x == x->parent->leftChild)
    {
        x->parent->leftChild = y;
    }

    if (x->parent != t_nil && x == x->parent->rightChild)
    {
        x->parent->rightChild = y;
    }

    y->leftChild = x;
    x->parent = y;
}

void rbtTreeInsertFixUpLeft(struct treeRB *t, struct treeNodeRB *z)
{
#if DEBUG_ENABLED
    fprintf(stderr, "\nrbtTreeInsertFixUpLeft\n");
#endif

    struct treeNodeRB *y = z->parent->parent->rightChild;

    // CASO 1
    if (y != NULL && y->color == RED)
    {
#if DEBUG_ENABLED
        fprintf(stderr, "\ncaso1\n");
#endif
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
#if DEBUG_ENABLED
            fprintf(stderr, "\ncaso3\n");
#endif
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
#if DEBUG_ENABLED
    fprintf(stderr, "\rbtTreeInsertFixUpRight\n");
#endif
    struct treeNodeRB *y = z->parent->parent->leftChild;
    // fprintf(stderr, "\ny->color:%d\n", y->color);
    //  CASO 1
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

    while (z != t->root && z->parent->color == RED)
    {
#if DEBUG_ENABLED

        fprintf(stderr, "\nqui\n");
        fprintf(stderr, "\nz->parent->color: %d\n", z->parent->color);
#endif
        // fprintf(stderr, "\nz->parent->parent: %d\n", z->parent->parent->key);
        //  fprintf(stderr, "\nz->parent->parent->leftChild: %d\n", z->parent->parent->leftChild);

        if (z->parent == z->parent->parent->leftChild)
        {
#if DEBUG_ENABLED

            fprintf(stderr, "\nqui2\n");
#endif
            rbtTreeInsertFixUpLeft(t, z);
        }
        else
        {
#if DEBUG_ENABLED

            fprintf(stderr, "\nqui3\n");
#endif
            rbtTreeInsertFixUpRight(t, z);
        }

#if DEBUG_ENABLED

        fprintf(stderr, "\nqui4\n");
#endif
        t->root->color = BLACK;
    }
}

void rbtTreeInsert(struct treeRB *t, struct treeNodeRB *z)
{
// fprintf(stderr, "\nprint root:\n");
// printRBTNode(t->root);
#if DEBUG_ENABLED

    fprintf(stderr, "\nrbtTreeInsert z:\n");
    printRBTNode(z);
#endif
    // struct treeNodeRB *t_nil = TNIL();
    struct treeNodeRB *y = t_nil;
    struct treeNodeRB *x = t->root;

    while (x != t_nil)
    {
#if DEBUG_ENABLED

        fprintf(stderr, "\ndebug1\n");
#endif
        y = x;
#if DEBUG_ENABLED
        fprintf(stderr, "\n*x: %p\n", x);

        fprintf(stderr, "\nprint x:\n");

        printRBTNode(x);
#endif

        if (z->key < x->key)
        {
#if DEBUG_ENABLED

            fprintf(stderr, "\ndebug3\n");
#endif
            x = x->leftChild;
        }
        else
        {

#if DEBUG_ENABLED

            fprintf(stderr, "\ndebug4\n");
#endif
            x = x->rightChild;
        }
    }

    z->parent = y;

    if (y == t_nil)
    {
        t->root = z;
    }

    if (y != t_nil && z->key < y->key)
    {
        y->leftChild = z;
    }

    if (y != t_nil && z->key >= y->key)
    {
        y->rightChild = z;
    }

    //    z->leftChild = t_nil;
    //  z->rightChild = t_nil;
    // z->color = RED;
    // fprintf(stderr, "\ncolore root: %d\n", t->root->color);
    //  sleep(10);
    rbtTreeInsertFixUp(t, z);
}

void inorderTraversal(struct treeNode *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->leftChild);
        fprintf(stderr, "%d ", root->key);
        inorderTraversal(root->rightChild);
    }
}

void inorderTraversalRBT(struct treeNodeRB *root)
{
    fprintf(stderr, "\n--------inorderTraversalRBT------\n");
    if (root != t_nil)
    {
        inorderTraversalRBT(root->leftChild);
        fprintf(stderr, "%d ", root->key);
        inorderTraversalRBT(root->rightChild);
    }

    fprintf(stderr, "\n--------------\n");
}

void printRBTNode(struct treeNodeRB *node)
{
    if (node == t_nil)
    {
        return;
    }

    fprintf(stderr, "\n------------\n");
    if (&(node->key))
    {
        fprintf(stderr, "\nKEY: %d\n", node->key);
    }
    if (&(node->color))
    {
        fprintf(stderr, "\nCOLOR: %d\n", node->color);
    }
    fprintf(stderr, "\n------------\n");
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

        // empty
        free(t);
    }

    return (double)t_tot / (double)maxKeys;
}

double singleExperimentRBT(int maxKeys, int maxSearch, int maxDelete, int maxInstances)
{

#if DEBUG_ENABLED
    fprintf(stderr, "\nstart singleExperimentRBT\n");
#endif
    clock_t t_tot = 0;
    int i, j;

    for (i = 0; i < maxInstances; i++)
    {

#if DEBUG_ENABLED
        fprintf(stderr, "\nsingleExperimentRBT iteration: %d\n", i);
#endif
        // init_TNIL();
        //  initialize(T)
        struct treeRB *t = (struct treeRB *)malloc(sizeof(struct treeRB));
        // create the root node
        init_TNIL();
        struct treeNodeRB *rootNode = getRandomNodeRBT();
        rootNode->color = BLACK;
        t->root = rootNode;

        clock_t t_start,
            t_end, t_elapsed;

        t_start = clock();

        for (j = 0; j < maxKeys; j++)
        {

            // struct treeNodeRB *newNode = getRandomNodeRBT();
            // fprintf(stderr, "\nnewNode->key: %d\n", newNode->key);

            rbtTreeInsert(t, getRandomNodeRBT());
        }

        for (j = 0; j < maxSearch; j++)
        {
            rbtTreeSearch(t->root, getRandomNodeRBT()->key);
        }

        for (j = 0; j < maxDelete; j++)
        {
            rbtTreeDelete(t, getRandomNodeRBT());
        }

        t_end = clock();

        t_elapsed = t_end - t_start;

        t_tot = t_tot + t_elapsed;

        // Empty
        free(t);
    }

    return (double)t_tot / (double)maxKeys;
}

void experiment(int minKeys, int maxKeys)
{
    fprintf(stderr, "start experiment\n");

    int maxInstances = 5;
    int step = 100;
    int percentageSearch = 60;
    int keys, maxSearch, maxDelete;

    for (keys = minKeys; keys <= maxKeys; keys += step)
    {
        srand(time(NULL));
        maxSearch = keys * percentageSearch / 100;
        maxDelete = keys - maxSearch;
        double timeBST = singleExperiment(keys, maxSearch, maxDelete, maxInstances);
        // fprintf(stderr, "%f %d\n", timeBST, keys);

        srand(time(NULL));
        double timeRBT = singleExperimentRBT(keys, maxSearch, maxDelete, maxInstances);

        fprintf(stderr, "%f %f %d\n", timeBST, timeRBT, keys);
        SEED++;
    }
}

int main()
{

    experiment(10, 10000);

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