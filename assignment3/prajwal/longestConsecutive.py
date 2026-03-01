class Solution:
    def longestConsecutive(self, nums: list[int]) -> int:
        sortedNums = sorted(nums)

        if nums == []:
            return 0
        print(f"Sorted List : {sortedNums}")
        # finding longest consecutive..
        streak = 1 # to keep track of the streak of consecutive nums
        maxStreak = 1

        for i in range(1, len(sortedNums)):

            if ( sortedNums[i] == sortedNums[i-1] ): # for duplicates
                continue

            if ( sortedNums[i] == sortedNums[i-1]+1 ):
                streak+=1
            else: 
                maxStreak = max(maxStreak , streak)
                streak = 1
        
        return max(maxStreak, streak)

LeetCode = Solution()
print(LeetCode.longestConsecutive( [0,3,7,2,5,8,4,6,0,1] ))