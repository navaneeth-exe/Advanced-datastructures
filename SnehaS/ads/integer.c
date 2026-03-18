#include <stdio.h>
#include <stdlib.h>


#define MAX 1000

int countZeroSum(int arr[], int n) {
    int count = 0, sum = 0;

    int freq[2 * MAX + 1] = {0}; 
    int offset = MAX;

    freq[offset] = 1; 

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (freq[sum + offset] > 0)
            count += freq[sum + offset];

        freq[sum + offset]++;
    }

    return count;
}

int main() {
    int n;

    printf("Enter size: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int result = countZeroSum(arr, n);

    printf("Total zero-sum subarrays: %d\n", result);

    return 0;
}
