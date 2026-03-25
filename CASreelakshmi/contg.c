#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int main() {
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    long sum = 0;
    int count = 0;

    // Using fixed-size hash for demo
    // In production, use hashmap / uthash
    int hash[2*SIZE] = {0}; // for negative sums, shift by SIZE

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (sum == 0) count++;
        count += hash[sum + SIZE];

        hash[sum + SIZE]++;
    }

    printf("Total number of contiguous subarrays with sum 0: %d\n", count);
}
