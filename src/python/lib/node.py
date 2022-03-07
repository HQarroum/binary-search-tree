# Describes a node that can be associated with
# a binary search tree.
class Node:
  def __init__(self, data):
    if not data:
      raise ValueError("Data cannot be null")
    self.data = data
    self.left = None
    self.right = None
    self.parent = None
