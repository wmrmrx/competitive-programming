class Fenwick:
    def __init__(self, n: int):
        self.n = n
        self.bit = [0]*(n+1)
    def update(self, id: int, val: int):
        while id <= self.n:
            self.bit[id] += val
            id += id&-id
    def query(self, id: int) -> int:
        sum = 0
        while id > 0:
            sum += self.bit[id]
            id -= id&-id
        return sum
