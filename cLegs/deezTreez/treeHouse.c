
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeHouse.h" 


#define DEBUG 1

int maxDepth(node *tree){
        if(tree == NULL){
                return 0;
        }
        else{
                int ldepth = maxDepth(tree->left);
                int rdepth = maxDepth(tree->right);
                if (ldepth > rdepth){
                        return ldepth+1;
                }
                else{
                        return rdepth+1;
                }
        }
}

void arrayAppend(node **prev_arr, int arr_len, node *ret_ptr){
        for(int i=0; i<arr_len; i++){
                if(prev_arr[i] == NULL){
                        prev_arr[i] = ret_ptr;
                        return;
                }
        }
}

void treePrintFullNodes(node **my_node){
        /** We only print full nodes here. **/
        if(&(*my_node)->right->val != NULL){
                printf("%s", "printing node at: ");
                printf("%p\n", *my_node);
                printf("%d\n", (*my_node)->val);
                printf("(%d ", (*my_node)->left->val);
                printf("%d)\n", (*my_node)->right->val);
        }
}

int treePrintLevelOrder(node *tree, node **queue, int queue_len){
        /** With our tree queue we get level order traversal cheap. O(n) as we visit each node once.
         *  If the input array to the tree build was pre-sorted, the level order traversal will be sorted.
         *  We could modify this to return a meaningful array, just print for now.
         **/
        for(int i=0; i<queue_len/2; i++){
                if(i==0){
                        printf("%s", "Level order: ");
                        printf("%d ", queue[0]->val);
                }
                if (&queue[i] != NULL){
                        if(queue[i]->left != NULL){
                                printf("%d ", queue[i]->left->val);
                        }
                        if(queue[i]->right != NULL){
                                printf("%d ", queue[i]->right->val);
                        }
                }
        }
        printf("%s\n", "");
        return 1;
}

node *treeAdd(int val, node *tree){
        /** Try left, try right, else return full node ptr. **/
        node *tmp = NewNode(val);
        if(tree->left == NULL){
                tree->left = tmp;
                if(DEBUG==1){
                        printf("%s", "left :");
                        printf("%p\n", tree->left);
                }
                return tree->left;
        }
        else if(tree->right == NULL){
                tree->right = tmp;
                if(DEBUG==1){
                        printf("%s", "right: ");
                        printf("%p\n", tree->right);
                }
                return tree->right;
        }
        else {
                if(DEBUG==1){printf("%s\n", "NODE FULL");}
                return tree;
        }
}

node ** treeQueue(int *array, int arr_len, node *tree){
        /** Put ints of variable length array into tree, return array of node pointers. **/
        node *previous[arr_len/2];
        int prev_len = sizeof(previous) / sizeof(previous[0]);

        memset(*(&previous), 0, sizeof(void *)*(arr_len/2));

        node **prev_mal = (node **) calloc(prev_len, sizeof(previous[0]));

        if(&(*previous)->val == NULL){
                previous[0] = tree;
        }

        for(int j=1; j<arr_len; j++){
                for(int i=0; i<prev_len; i++){
                        node *ret = treeAdd(array[j], previous[i]);

                        if(ret != previous[i]){
                                arrayAppend(previous, arr_len, ret);
                                treePrintFullNodes(&previous[i]);
                                break;
                        }
                }

                if(DEBUG==1){
                        printf("\n%s", "Populated node pointers: \n");
                        for(int k=0; k<prev_len; k++){
                                printf("%p\n", previous[k]);
                        }
                }
        }

        memcpy(prev_mal, previous, sizeof(previous));
        return prev_mal;
}

int main(){
        printf("%s\n\n", "[+] Welcome Starfighter");

        //int array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        //int array[] = {1,2,3,4,5,6,7,8,9};
        int array[] = {1,2,3,4,5};
        int arr_len = sizeof(array) / sizeof(array[0]);

        node *root = NewNode(array[0]);

        printf("%s", "root: ");
        printf("%p\n", root);

        node ** node_ptrs = treeQueue(array, arr_len, root);

        printf("\n%s", "max depth: ");
        printf("%d\n", maxDepth(root));

        treePrintLevelOrder(root, node_ptrs, arr_len);

        printf("%s\n", "");
        for(int i=0; i<arr_len/2; i++){
                printf("%s", "Freeing: ");
                printf("%p\n", node_ptrs[i]);
                memset(&node_ptrs[i], 0, sizeof(node_ptrs[i]));
                free(node_ptrs[i]);
        }
        printf("%s", "Freeing node_ptr: ");
        printf("%p\n", node_ptrs);
        free(node_ptrs);
}

