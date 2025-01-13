class Solution:
    def minimumLength (self, s : str) -> int:
        char_freq = [0] * 26
        total_length = 0
        for char in s:
            char_freq [ord (char) - ord ('a')] += 1
        for freq in char_freq:
            if freq == 0:
                continue
            elif freq % 2 == 0:
                total_length += 2
            else:
                total_length += 1
        return total_length