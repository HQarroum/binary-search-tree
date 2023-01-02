from node import Node

class BreadthFirstIterator:

  def __init__(self, bst, node=None):
    self.__idx   = 0
    self.__array = self.__build_array(node if node else bst.root)
  
  def __build_array(self, node):
    """
    Returns a list of all the nodes in the given subtree in breadth-first order.
    :param node: The root of the subtree to search in.
    """
    if not node:
      return []
    queue = [node]
    result = []
    while queue:
      current = queue.pop(0)
      result.append(current)
      if current.left:
        queue.append(current.left)
      if current.right:
        queue.append(current.right)
    return result

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
