class Solution:
    def constructDistancedSequence (self, n : int) -> List [int]:
        len_seq = 2 * n - 1
        seq = [0] * len_seq
        used = set ()

        def backtrack (i):
            if i == len_seq: return True
            if seq [i]: return backtrack (i + 1)

            for num in range (n, 0, -1):
                if num in used: continue

                next = i + num if num > 1 else i

                if next >= len_seq or seq [next] != 0: continue
                
                seq [i] = seq [next] = num
                used.add (num)

                if backtrack (i + 1):
                    return True

                seq [i] = seq [next] = 0
                used.remove (num)

            return False

        backtrack (0)
        return seq 