from node import Node

class InOrderIterator:

  def __init__(self, bst, node=None):
    self.__idx   = 0
    self.__array = self.__build_array(node if node else bst.root)
  
  def __build_array(self, node):
    if not node:
      return []
    return self.__build_array(node.left) + [node] + self.__build_array(node.right)

  def array(self):
    return self.__array

  def __iter__(self):
    return self

  def __next__(self) -> Node:
    """
    Returns the next node in the binary-search tree.
    """
    if self.__idx >= len(self.__array):
      raise StopIteration
    node = self.__array[self.__idx]
    self.__idx += 1
    return node
