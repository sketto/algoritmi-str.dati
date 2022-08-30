#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define RED 1
#define BLACK 0
#define DEBUG_ENABLED 0
#define T_PARAM 3

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

// struct treeNodeRB T_Nil_rbtNode;           // defining the T_Nil node
struct treeNodeRB *t_nil; // using it as the sentinel
void init_TNIL()
{
    t_nil = (struct treeNodeRB *)malloc(sizeof(struct treeNodeRB));
    t_nil->color = BLACK;
    t_nil->parent = NULL;
    t_nil->leftChild = NULL;
    t_nil->rightChild = NULL;
};

struct treeRB
{

    int cardinality;
    struct treeNodeRB *root;
};

struct B_tree_node
{
    int keys[2 * T_PARAM];
    int leaf;
    struct B_tree_node *parent;
    struct B_tree_node *children[2 * T_PARAM + 1];
};

struct Btree
{
    int cardinality;
    struct B_tree_node *root;
};

// void BtreeInsert(struct Btree *t, struct B_tree_node *k)
// {
//     struct B_tree_node *r = t->root;

//     if (r->keys == 2 * T_PARAM - 1)
//     {
//         struct B_tree_node *s = malloc(sizeof(struct B_tree_node *));
//         t->root = s;
//         s->leaf = 0;
//         s->keys = 0;
//         s->children = r;
//     }
// }

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

void rbtTreeTransplant(struct treeRB *t, struct treeNodeRB *u, struct treeNodeRB *v)
{
    if (u->parent == t_nil)
    {
        t->root = v;
    }
    else if (u == u->parent->leftChild)
    {
        u->parent->leftChild = v;
    }
    else if (u->parent->rightChild == v)
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
}

struct treeNodeRB *rbtTreeMinimum(struct treeNodeRB *x)
{
    if (x->leftChild == NULL)
    {
        return x;
    }

    return rbtTreeMinimum(x->leftChild);
}

void rbtTreeDeleteFixup(struct treeRB *t, struct treeNodeRB *x)
{
    struct treeNodeRB *w;
    while (x != t->root && x->color == BLACK)
    {
        if (x == x->parent->leftChild)
        {
            w = x->parent->rightChild;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;

                treeLeftRotate(t, x->parent);

                w = x->parent->rightChild;

                if (w->leftChild->color == BLACK && w->rightChild->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else if (w->rightChild->color == BLACK)
                {
                    w->leftChild->color = BLACK;
                    w->color = RED;
                    treeRightRotate(t, w);
                    w = x->parent->rightChild;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->rightChild->color = BLACK;

                treeLeftRotate(t, x->parent);
                x = t->root;
            }
        }
        else
        {
            w = x->parent->leftChild;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;

                treeLeftRotate(t, x->parent);

                w = x->parent->leftChild;

                if (w->rightChild->color == BLACK && w->leftChild->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else if (w->leftChild->color == BLACK)
                {
                    w->rightChild->color = BLACK;
                    w->color = RED;
                    treeRightRotate(t, w);
                    w = x->parent->leftChild;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->leftChild->color = BLACK;

                treeLeftRotate(t, x->parent);
                x = t->root;
            }
        }
    }

    x->color = BLACK;
}

void rbtTreeDelete(struct treeRB *t, struct treeNodeRB *z)
{

    struct treeNodeRB *y = z;
    struct treeNodeRB *x;

    int yOrigColor = y->color;

    if (z->leftChild == t_nil)
    {
        x = z->rightChild;
        rbtTreeTransplant(t, z, z->rightChild);
    }

    else if (z->rightChild == t_nil)
    {
        x = z->leftChild;
        rbtTreeTransplant(t, z, z->leftChild);
    }

    else
    {
        struct treeNodeRB *y = rbtTreeMinimum(z->rightChild);
        yOrigColor = y->color;
        x = y->rightChild;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbtTreeTransplant(t, y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parent = y;
        }

        rbtTreeTransplant(t, z, y);
        y->leftChild = z->leftChild;
        y->leftChild->parent = y;
        y->color = z->color;

        if (yOrigColor == BLACK)
        {
            rbtTreeDeleteFixup(t, x);
        }
    }

    free(z);
}

void TreeDelete(struct treeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    TreeDelete(node->leftChild);
    TreeDelete(node->rightChild);

    // printf("\nfreeing node with key: %d\n", node->key);
    free(node);
}

void rbDeleteTree(struct treeNodeRB *node)
{
    if (node == t_nil)
    {
        return;
    }
    rbDeleteTree(node->leftChild);
    rbDeleteTree(node->rightChild);
    free(node);
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

    rbtTreeInsertFixUp(t, z);
}

double singleExperiment(int maxKeys, int maxSearch, int maxDelete, int maxInstances)
{

    clock_t t_tot = 0;
    int i, j;

    for (i = 0; i < maxInstances; i++)
    {
        // initialize the BST
        struct tree *t = (struct tree *)malloc(sizeof(struct tree));
        t->root = getRandomNode();
        /////////////////////

        clock_t t_start, t_end, t_elapsed;

        t_start = clock();

        for (j = 0; j < maxKeys; j++)
        {
            bstTreeInsert(t, getRandomNode());
        }

        for (j = 0; j < maxSearch; j++)
        {
            struct treeNode *tmp = getRandomNode();
            bstTreeSearch(t->root, tmp->key);
            free(tmp);
        }

        // for (j = 0; j < maxDelete; j++)
        // {
        //     bstTreeDelete(t, getRandomNode());
        // }

        t_end = clock();

        t_elapsed = t_end - t_start;

        t_tot = t_tot + t_elapsed;

        // empty
        TreeDelete(t->root);
        free(t);
        // free(t_nil);
    }

    return (double)t_tot / (double)maxKeys;
}

double singleExperimentRBT(int maxKeys, int maxSearch, int maxDelete, int maxInstances)
{
    clock_t t_tot = 0;
    int i, j;

    for (i = 0; i < maxInstances; i++)
    {
        // initialize the RBT
        struct treeRB *t = (struct treeRB *)malloc(sizeof(struct treeRB));
        // create the root node
        init_TNIL();
        struct treeNodeRB *rootNode = getRandomNodeRBT();
        rootNode->color = BLACK;
        t->root = rootNode;
        /////////////////////

        clock_t t_start, t_end, t_elapsed;

        t_start = clock();

        for (j = 0; j < maxKeys; j++)
        {
            rbtTreeInsert(t, getRandomNodeRBT());
        }

        for (j = 0; j < maxSearch; j++)
        {
            struct treeNodeRB *tmp = getRandomNodeRBT();
            rbtTreeSearch(t->root, tmp->key);
            free(tmp);
        }

        // for (j = 0; j < maxDelete; j++)
        // {
        //     // rbtTreeDelete(t, getRandomNodeRBT());
        // }

        t_end = clock();

        t_elapsed = t_end - t_start;

        t_tot = t_tot + t_elapsed;

        // Empty
        rbDeleteTree(t->root);
        free(t);
        free(t_nil);
    }

    return (double)t_tot / (double)maxKeys;
}

void experiment(int minKeys, int maxKeys)
{
    fprintf(stderr, "start experiment\n");

    int maxInstances = 5;
    int step = 1;
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

void printInorder(struct treeNode *node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder(node->leftChild);

    /* then print the data of node */
    printf("%d ", node->key);

    /* now recur on right child */
    printInorder(node->rightChild);
}

int main()
{

    experiment(10, 100);
    // struct tree *t = (struct tree *)malloc(sizeof(struct tree));
    // t->root = getRandomNode();
    // bstTreeInsert(t, getRandomNode());
    // printInorder(t->root);
    // printf("\n");

    // struct treeNode *tmp = getRandomNode();
    // printf("tmp->key: %d\n", tmp->key);
    // bstTreeDelete(t, tmp);
    // free(tmp);
    // tmp = getRandomNode();
    // bstTreeSearch(t->root, tmp->key);
    // free(tmp);

    // printInorder(t->root);
    // TreeDelete(t->root);
    // free(t);

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