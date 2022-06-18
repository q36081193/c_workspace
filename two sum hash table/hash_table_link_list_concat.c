
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define TABLE_SIZE 1000 

typedef struct Node{
    int key;
    int indexs;
    struct Node *next;
} Node;

typedef struct Htable{
    Node **nodes;
} Htable;

Node *createNode(int *key, int *indexs);

Htable *create(void){
    Htable *hashtable = malloc(sizeof(Htable) * 1);

    hashtable->nodes = malloc(sizeof(Node *) * TABLE_SIZE);

    for(int i=0; i<TABLE_SIZE; i++){
        hashtable->nodes[i]=NULL;
    }

    return hashtable;
}

unsigned int hash(int* key){
    int hash_value;
    // int a = key;
    hash_value = (unsigned int) *(key) * *(key)  % TABLE_SIZE;
    return hash_value;
}

void insert(Htable *ht, int *key, int *indexs){
    unsigned int slot = hash(key);
    Node *new = ht->nodes[slot];

    if (new == NULL){
        ht->nodes[slot] = createNode(key,indexs);
        return;
    }

    Node *prev;

    while (new != NULL){
        if(new->key == *(key)){
            new->indexs = *(indexs);
            return;
        }
        prev = new;
        new = prev->next;
    }

    prev->next = createNode(key,indexs);
}

Node *createNode(int *key, int *indexs){
    Node *new = malloc(sizeof(Node) *1);
    new->key = *(key);
    new->indexs = *(indexs);
    new->next =NULL;

    return new;
}

int getIndex(Htable *ht, int *value, int index){
    unsigned int slot = hash(value);
    Node *return_node = ht->nodes[slot];
    int re_ind=-1;

    if (return_node == NULL){
        return re_ind;
    }


    while (return_node->next!=NULL){
        if ((*value ==return_node->key)){
            re_ind=return_node->indexs;
            return re_ind;
        }
        return_node=return_node->next;        
    }

    if ((*value ==return_node->key)){
            re_ind=return_node->indexs;
            return re_ind;
    }    

    return re_ind;
}

void main(){
    // int nums[]={0,3,-3,4,-1};
    // int target = -1;
    int nums[]={10,13,-3,-4};
    int target = 9;
    int size = sizeof(nums)/sizeof(nums[0]);
    int res[2];

    Htable *ht = create();
    for (int i=0; i<size; i++){
        int search_value = target-nums[i];
        int re_ind = getIndex(ht,&search_value,i);
        
        if (re_ind!=-1)
        {
            res[1]=i;
            res[0]=re_ind;
            printf("first  idx is %2d\nsecond idx is %2d\n",res[0],res[1]);    
            return;
        } 
        else
        {
            insert(ht,&nums[i],&i);
        }
    }
    // for (int i=0; i<size; i++){
    //     printf("value is %2d,index is %2d\n",ht->nodes[hash(&nums[i])]->key,ht->nodes[hash(&nums[i])]->indexs);
    // }
    // printf("value is %2d,index is %2d\n",ht->nodes[hash(&nums[2])]->next->key,ht->nodes[hash(&nums[2])]->next->indexs);

    printf("can't find any matches\n");    
}