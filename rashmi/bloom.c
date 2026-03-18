#include <stdio.h>
#include <string.h>
#define SIZE 20   
int bloom[SIZE] = {0};
int hash1(char *str) 
{
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
        sum = sum + str[i];
    return sum % SIZE;
}
int hash2(char *str) 
{
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
        sum = (sum * 3 + str[i]) % SIZE;
    return sum;
}
void insert(char *str) 
{
    int h1 = hash1(str);
    int h2 = hash2(str);
    bloom[h1] = 1;
    bloom[h2] = 1;
}
int search(char *str) 
{
    int h1 = hash1(str);
    int h2 = hash2(str);
    return (bloom[h1] && bloom[h2]);
}
int main() 
{
    insert("apple");
    insert("banana");
    insert("grape");
    if (search("apple"))
        printf("apple is probably present\n");
    else
        printf("apple is not present\n");
    if (search("orange"))
        printf("orange is probably present\n");
    else
        printf("orange is not present\n");
    return 0;
}