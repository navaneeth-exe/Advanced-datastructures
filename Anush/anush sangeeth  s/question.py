def count_zero_sum_subarrays(arr):
    prefix_sum = 0
    count = 0
    freq = {0: 1}

    for num in arr:
        prefix_sum += num

        if prefix_sum in freq:
            count += freq[prefix_sum]
            freq[prefix_sum] += 1
        else:
            freq[prefix_sum] = 1

    return count


if __name__ == "__main__":
    arr = [3, 4, -7, 1, 2, -6, 4, -1]
    print(count_zero_sum_subarrays(arr))
