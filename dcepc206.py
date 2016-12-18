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

import sys

class BinaryTree:

    def __init__(self, v):
        self.left = None
        self.right = None
        self.value = v
        self.sum = 0

    def __repr__(self):
        return str(self)

    def __str__(self):
        return "[{} {}] ({}) ({})".format(self.value, self.sum, self.left, self.right)

    def insert(self, v):
        current = self
        tree = BinaryTree(v)
        s = 0
        while True:
            if current.value == v:
                break
            elif current.value < v:
                if current.right == None:
                    tree.sum += current.sum + current.value
                    current.right = tree
                    break
                else:
                    s += current.sum + current.value
                    current = current.right
            else:
                current.sum += v
                if current.left == None:
                    tree.sum = s
                    current.left = tree
                    break
                else:
                    current = current.left

    def find(self, v):
        current = self
        while True:
            if current.value == v:
                return current
            elif current.value < v:
                if current.right != None:
                    current = current.right
                else:
                    return None
            else:
                if current.left != None:
                    current = current.left
                else:
                    return None


def solve(stair):
    tree = BinaryTree(stair.pop(0))
    notes = []
    for step in stair:
        tree.insert(step)
        elem = tree.find(step)
        #print(step, elem.sum, tree)
        notes.append(elem.sum)
    return sum(notes)


def main():
    t = int(input())
    for i in range(t):
        size = int(input())
        stair = [int(n) for n in input().split(' ')[:size]]
        print(solve(stair))


if __name__ == "__main__":
    main()
