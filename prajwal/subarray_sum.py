from typing import List

class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        """
        LeetCode 560: Subarray Sum Equals K
        
        Using Prefix Sum and Hash Map pattern
        Time Complexity: O(n)
        Space Complexity: O(n)
        """
        count = 0
        current_sum = 0
        
        # Dictionary to store prefix sums and their frequencies.
        # Initialize with prefix sum 0 having frequency 1 to account 
        # for a subarray starting from index 0 that equals target.
        prefix_sums = {0: 1}
        
        for num in nums:
            current_sum += num
            
            # If (current_sum - k) exists in our hashmap, it means there are 
            # sub-arrays ending at the current iteration which sum up to k.
            if current_sum - k in prefix_sums:
                count += prefix_sums[current_sum - k]
                
            # Add current prefix sum to the hashmap
            prefix_sums[current_sum] = prefix_sums.get(current_sum, 0) + 1
            
        return count


if __name__ == "__main__":
    sol = Solution()
    print("Test [1,1,1] with k=2: ", sol.subarraySum([1,1,1], 2)) # Expected output: 2
    print("Test [1,2,3] with k=3: ", sol.subarraySum([1,2,3], 3)) # Expected output: 2
