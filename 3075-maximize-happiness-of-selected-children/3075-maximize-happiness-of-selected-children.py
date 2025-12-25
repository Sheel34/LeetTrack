class Solution:
    def maximumHappinessSum (self, happiness : List [int], k : int) -> int:
        happiness.sort (reverse = True)
        totalJoy = 0
        for turn in range (k):
            currentJoy = happiness [turn] - turn
            if currentJoy <= 0:
                break
            totalJoy += currentJoy
        return totalJoy