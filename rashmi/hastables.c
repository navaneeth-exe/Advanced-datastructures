#include <stdio.h>
#define SIZE 10
int hashTable[SIZE];
int hashFunction(int key)
{
    return key % SIZE;
}
void insert(int key)
{
    int index = hashFunction(key);
    hashTable[index] = key;
}
void display()
{
    int i;
    for(i = 0; i < SIZE; i++)
    {
        printf("Index %d : %d\n", i, hashTable[i]);
    }
}
int main()
{
    int i;
    for(i = 0; i < SIZE; i++)
        hashTable[i] = -1;
    insert(230);
    insert(431);
    insert(103);
    insert(27);
    display();
    return 0;
}