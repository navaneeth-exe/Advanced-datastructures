#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
int countZeroSumSubarrays(int arr[], int n) {
    int prefixSum = 0;
    int count = 0;
    int hash[2001] = {0}; 
    int offset = 1000;
    hash[offset] = 1;
    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        if (hash[prefixSum + offset] > 0) {
            count += hash[prefixSum + offset];
        }
        hash[prefixSum + offset]++;
    }
    return count;
}
int main() {
    int arr[] = {3, 4, -7, 1, 3, -4, -2, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = countZeroSumSubarrays(arr, n);
    printf("Total zero-sum subarrays: %d\n", result);
    return 0;
}
