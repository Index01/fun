
#ifndef TREEHOUSE_H
#define TREEHOUSE_H
typedef struct node{
        int val;
        struct node *left;
        struct node *right;
}node;

struct node *NewNode(int data){
        node *root = (node *) malloc(sizeof(node));
        root->val = data;
        root->left = NULL;
        root->right = NULL;
        return root;
}

#endif

int maxDepth(node *node);
void treePrintFullNodes(node **my_node);
node *treeAdd(int val, node *tree);
node ** treeQueue(int *array, int arr_len, node *tree);

