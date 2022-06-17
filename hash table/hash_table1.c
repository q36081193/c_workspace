#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE    5
#define EMPTY   -1

typedef void (*FP) (int);

int hash_table[SIZE];

void print_arr(const char* msg) {
    printf("<%s> :", msg);

    for (int i = 0; i < SIZE; i++)
    {
        printf(" hash_table[%d] = %2d", i, hash_table[i]);
    }
    printf("\n");  
}

void init()
{
    int i;
    for (int i = 0; i < SIZE; i++)
    {
        hash_table[i]=-1;
    }
    
}

int hash(int val, int insert)
{
    int key = val%SIZE;
    int index = key;
    int target_val = insert ? EMPTY : val;
    while (hash_table[index]!= target_val)  
    {
        index = (index+1) % SIZE;
        if (index == key)
        {
            return 0;
        }
    }
    return (index + 1);
}

void search(int val)
{
    int result = hash(val, 0);
    
    if (result!=0)
        printf("The item %d is found in index %d\n", val, result-1);
    else
        printf("The item %d is not found in the whole hash table\n", val);
}

void del(int val)
{
    printf("The deleting item %d\n", val);
    int result = hash(val, 0);

    if (result!=0)
    {
        printf("is found in index %d\n", result-1);
        hash_table[result-1] = EMPTY;
    }    
    else
        printf("is not found\n");
}

void insert(int val)
{
    int result = hash(val, 1);
    
    if (result!=0)
    {
        printf("The item %d is inserted in index %d\n", val, (result-1));
        hash_table[(result-1)]=val;
    }    
    else
        printf("hash table is full\n");
}

void test_case(int test_case[], int arr_len, char c, FP fp)
{
    for (int i = 0; i < arr_len; i++)
    {
        (*fp)(test_case[i]);
        if (c == '+')
            print_arr("insert");
        else if (c == '-')
            print_arr("delete");
        else if (c == '?')
            print_arr("search");
    }
    return;
}

int main(int argc, char const *argv[])
{
    // initialized the whole hash table to value -1
    init();
    // test : add items to the hash table 
    int test_case_add[] = {11,14,5,3,6};
    int arr_len_add = ( sizeof(test_case_add) / sizeof(test_case_add[0]) );
    test_case(test_case_add, arr_len_add, '+', insert);
    // test : del items to the hash table 
    int test_case_del[] = {7,14};
    int arr_len_del = ( sizeof(test_case_del) / sizeof(test_case_del[0]) );
    test_case(test_case_del, arr_len_del, '-', del);
    // test : search item in the hash table 
    int test_case_search[] = {6,5,3,11,7,14};
    int arr_len_search = ( sizeof(test_case_search) / sizeof(test_case_search[0]) );
    test_case(test_case_search, arr_len_search, '?', search);

    return 0;
}
