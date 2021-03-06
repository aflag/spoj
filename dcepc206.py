#!/usr/bin/env python3
# http://www.spoj.com/problems/DCEPC206/
# It's a Murder!

# Once detective Saikat was solving a murder case. While going to the crime
# scene he took the stairs and saw that a number is written on every stair. He
# found it suspicious and decides to remember all the numbers that he has seen
# till now. While remembering the numbers he found that he can find some pattern
# in those numbers. So he decides that for each number on the stairs he will note
# down the sum of all the numbers previously seen on the stairs which are smaller
# than the present number. Calculate the sum of all the numbers written on his
# notes diary.

# Input

# First line gives T, number of test cases.
# 2T lines follow.
# First line gives you the number of stairs N
# Next line gives you N numbers written on the stairs.

# Output

# For each test case output one line giving the final sum for each test case.

# Constraints

# T<=10
# 1<=N<=10^5

# All numbers will be between 0 and 10^6.

class BinaryTree:

    def __init__(self, v):
        self.left = None
        self.right = None
        self.parent = None
        self.value = v
        self.replicas = 1
        self._sum = 0

    def __repr__(self):
        return str(self)

    def __str__(self):
        return "[{} {} {}] ({}) ({})".format(self.value, self._sum, self.sum, self.left, self.right)

    @property
    def sum(self):
        total = self._sum
        current = self
        while True:
            if current.parent is None:
                return total
            parent = current.parent
            if parent.value < self.value:
                total += (parent.value*parent.replicas) + parent._sum
            current = current.parent

    def insert(self, v):
        current = self
        s = 0
        while True:
            if current.value == v:
                current.replicas += 1
                return current._sum + s
            elif current.value < v:
                s += (current.value*current.replicas) + current._sum
                if current.right is None:
                    node = BinaryTree(v)
                    node.parent = current
                    current.right = node
                    return s
                else:
                    current = current.right
            else:
                current._sum += v
                if current.left is None:
                    node = BinaryTree(v)
                    node.parent = current
                    current.left = node
                    return s
                else:
                    current = current.left


def solve(stair):
    tree = BinaryTree(stair.pop(0))
    total = 0
    for step in stair:
        total += tree.insert(step)
    return total


def main():
    t = int(input())
    for i in range(t):
        size = int(input())
        stair = [int(n) for n in input().split(' ')[:size]]
        print(solve(stair))


if __name__ == "__main__":
    main()
