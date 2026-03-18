#include <stdio.h>
#include <stdlib.h>

// Function to count zero sum subarrays
int countZeroSumSubarrays(int arr[], int n) {
    int count = 0;
    int prefixSum = 0;

    // Hash map using array (simple version)
    // For large values, use unordered_map (in C++) or better hashing
    int hash[20001] = {0};  // range -10000 to +10000
    int offset = 10000;

    hash[offset] = 1; // prefix sum 0 occurs once

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        if (hash[prefixSum + offset] > 0) {
            count += hash[prefixSum + offset];
        }

        hash[prefixSum + offset]++;
    }

    return count;
}

// Main
int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = countZeroSumSubarrays(arr, n);

    printf("Total zero-sum subarrays = %d\n", result);

    return 0;
}
