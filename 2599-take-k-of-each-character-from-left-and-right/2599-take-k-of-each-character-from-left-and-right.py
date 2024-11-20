class Solution:
    def takeCharacters (self, s : str, k : int) -> int:
        freq = [0] * 3
        size = len (s)
        
        for char in s:
            freq [ord (char) - ord ('a')] += 1
        
        left = 0
        right = 0
        
        if freq [0] < k or freq [1] < k or freq [2] < k:
            return -1
        
        for right in range (size):
            freq [ord (s [right]) - ord ('a')] -= 1
            
            if freq [0] < k or freq [1] < k or freq [2] < k:
                freq [ord (s [left]) - ord ('a')] += 1
                left += 1
        
        return size - (right - left + 1)
