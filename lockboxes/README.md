# 🔐 Lockboxes

This project solves the classic **Lockboxes (Keys and Boxes)** problem using Python.

## 🧠 Problem Description

You are given n number of locked boxes. Each box is numbered sequentially from 0 to n - 1 and each box may contain keys to the other boxes. 
The goal is to write a method that determines if all the boxes can be opened with the information provided:

- Prototype: def canUnlockAll(boxes)
- boxes is a list of lists.
- A key with the same number as a box opens that box
- You can assume all keys will be positive integers
- There can be keys that do not have boxes
- The first box boxes[0] is unlocked
- Return True if all boxes can be opened, else return False.

