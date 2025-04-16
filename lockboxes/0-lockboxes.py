def canUnlockAll(boxes):
  if not boxes or not isinstance(boxes, list):
    return False
  
  # Using empty set to keep track of which boxes we've opened (by index) and give fast lookup without duplicate
  opened = set()
  
  # Using the stack LIFO to explore boxes, and start with the box 0 which is unlocked
  stack = [0]
  
  while stack:
    current_box = stack.pop()
    if current_box not in opened:
      opened.add(current_box)
      for key in boxes[current_box]:
        if 0 <= key < len(boxes):
          stack.append(key)

  return len(opened) == len(boxes)
  
  