class NumberContainers:

    def __init__ (self):
        self.index_val = {}
        self.result = {}

    def change (self, index : int, number : int) -> None:
        if index in self.index_val:
            prevNum = self.index_val [index]
            if prevNum == number:
                return
        self.index_val [index] = number
        if number not in self.result:
            self.result [number] = []
        heapq.heappush (self.result [number], index)

    def find (self, number : int) -> int:
        if number not in self.result:
            return -1
        while self.result [number] and self.index_val [self.result [number] [0]] != number:
            heapq.heappop (self.result [number])
        return self.result [number] [0] if self.result [number] else -1


# Your NumberContainers object will be instantiated and called as such:
# obj = NumberContainers()
# obj.change(index,number)
# param_2 = obj.find(number)