from array import array
from typing import Iterator, overload
from node import Node
from iterators.dfs import DepthFirstIterator
from iterators.bfs import BreadthFirstIterator

# A binary-search tree.
class BinarySearchTree:

  def __init__(self, **options) -> None:
    """
    The binary-search tree constructor.
    :param options: the options to use when constructing the binary-search tree.
    Providing a comparator function is mandatory to create a binary-search tree.
    A comparator is a user-provided function that returns a negative number if
    the first argument is less than the second argument, a positive number if the
    first argument is greater than the second and zero if the two arguments
    are equal.
    """
    if not 'comparator' in options:
      raise Exception('No comparator provided.')
    
    self.root = None
    self.size = 0
    self.comparator = options['comparator']
  
  def insert(self, data):
    """
    Inserts the given `data` in the binary-search tree.
    :param data: the data to insert in the binary-search tree.
    """

    # If the data is of type list, we insert each element.
    if isinstance(data, list):
      return [self.insert(data[i]) for i in range(len(data))]
    
    # Creating a new node instance holding
    # the given data.
    node = Node(data)

    # Verifying whether the binary-search tree is empty.
    if not self.root:
      self.size = 1
      self.root = node
      return self.root
    return self.__insert_at(self.root, node)

  def __insert_at(self, node, new_node):
    """
    Private method used to recursively insert a new node in
    the binary-search tree.
    :param node: The root of the subtree to insert the new node in.
    :param new_node: The new node to insert in the binary-search tree.
    """
    result = self.comparator(new_node.data, node.data)
    
    if result < 0:
      return self.__insert_at(node.left, new_node) if node.left else self.__attach(node, new_node)
    elif result > 0:
      return self.__insert_at(node.right, new_node) if node.right else self.__attach(node, new_node)
    else:
      # The binary-search tree does not accept duplicate
      # values in the tree.
      return node

  def __attach(self, node, new_node):
    """
    Private method used to attach a new node to an existing node.
    :param node: The node to attach the new node to.
    :param new_node: The new node to attach to the existing node.
    :param side: Whether to attach the new node to the left or right side of the existing node.
    """
    result = self.comparator(new_node.data, node.data)

    if result < 0:
      node.left = new_node
    else:
      node.right = new_node
    
    new_node.parent = node
    self.size += 1
    return new_node

  def find(self, data):
    """
    A helper function to find the node associated with `data`
    in the binary-search tree.
    :param data: The data used to return the associated node from the binary-search tree.
    """
    return self.find_in(self.root, data)

  def find_in(self, node, data):
    """
    A helper function to find the node associated with `data`
    in the given subtree.
    :param node: The root of the subtree to search in.
    :param data: The data used to return the associated node from the binary-search tree.
    """
    if not node or node.data == data:
      return node
    
    # Compare the data to find with the current node's data.
    result = self.comparator(data, node.data)

    # Recursively search the tree.
    return self.find_in(node.left if result < 0 else node.right, data)

  def min(self):
    """
    Computes the node with the smallest value in the binary-search tree.
    """
    return self.min_in(self.root)
  
  def min_in(self, node):
    """
    Computes the node with the smallest value in the given subtree.
    :param node: The root of the subtree to search in.
    """
    if not node or not node.left:
      return node
    return self.min_in(node.left)

  def max(self):
    """
    Computes the node with the largest value in the binary-search tree.
    """
    return self.max_in(self.root)

  def max_in(self, node):
    """
    Computes the node with the largest value in the given subtree.
    :param node: The root of the subtree to search in.
    """
    if not node or not node.right:
      return node
    return self.max_in(node.right)

  def sort(self):
    """
    Sorts the binary-search tree in ascending order.
    """
    return self.sort_in(self.root)

  def sort_in(self, node):
    """
    Sorts the given subtree in ascending order.
    :param node: The root of the subtree to sort.
    """
    if not node:
      return []
    return self.sort_in(node.left) + [node.data] + self.sort_in(node.right)

  def kth_smallest(self, k):
    """
    Computes the kth smallest value in the binary-search tree.
    :param k: The kth smallest value in the binary-search tree.
    """
    return self.kth_smallest_in(self.root, k)
  
  def kth_smallest_in(self, node, k):
    """
    Computes the kth smallest value in the given subtree.
    :param node: The root of the subtree to search in.
    :param k: The kth smallest value in the binary-search tree.
    """
    if not node:
      return None
    if k == 1:
      return node.data
    if k > 1:
      return self.kth_smallest_in(node.left, k - 1)
    return self.kth_smallest_in(node.right, k - 1)
  
  def kth_largest(self, k):
    """
    Computes the kth largest value in the binary-search tree.
    :param k: The kth largest value in the binary-search tree.
    """
    return self.kth_largest_in(self.root, k)

  def kth_largest_in(self, node, k):
    """
    Computes the kth largest value in the given subtree.
    :param node: The root of the subtree to search in.
    :param k: The kth largest value in the binary-search tree.
    """
    if not node:
      return node
    if k == 1:
      return node.data
    if k > 1:
      return self.kth_largest_in(node.right, k - 1)
    return self.kth_largest_in(node.left, k - 1)
  
  def remove(self, data):
    """
    Removes the node associated with `data` from the binary-search tree.
    :param data: The data associated with the node to remove.
    """
    return self.__remove_node(self.root, data)
  
  def __remove_node(self, node, data):
    """
    Private method used to recursively remove the node associated with `data`
    from the given subtree.
    :param node: The node to remove from the binary-search tree.
    """
    if not node:
      return node

    # Comparing the given data to the current node's data.
    result = self.comparator(data, node.data)

    if result < 0:
      node.left = self.__remove_node(node.left, data)
    elif result > 0:
      node.right = self.__remove_node(node.right, data)
    else:
      # The node doesn't have any children.
      if node.left and node.right:
        if self.root == node:
          self.root = None
        self.size -= 1
        return None
      # The node has a single child.
      elif node.left or node.right:
        successor = node.left if node.left else node.right
        successor.parent = node.parent
        if self.root == node:
          self.root = successor
        self.size -= 1
        return successor
      # The node has two children.
      else:
        successor = self.min_in(node.right)
        node.data = successor.data
        node.right = self.__remove_node(node.right, successor.data)

  def nodes(self) -> list:
    """
    Returns a list of all the nodes in the binary-search tree.
    """
    return self.nodes_in(self.root)

  def nodes_in(self, node) -> list:
    """
    Returns a list of all the nodes in the given subtree.
    :param node: The root of the subtree to search in.
    """
    return self.dfs_iterator_from(self, node).array()

  def dfs_iterator(self) -> Iterator:
    return self.dfs_iterator_from(self.root)

  def dfs_iterator_from(self, node) -> Iterator:
    return (iter(DepthFirstIterator(self, node)))

  def bfs_iterator(self) -> Iterator:
    return self.bfs_iterator_from(self.root)

  def bfs_iterator_from(self, node) -> Iterator:
    return (iter(BreadthFirstIterator(self, node)))

  def __iter__(self) -> Iterator:
    """
    Returns an iterator over the nodes in the binary-search tree.
    """
    return self.dfs_iterator()

  def __str__(self) -> str:
    """
    Returns a string representation of the binary-search tree.
    """
    return self.to_string(self.root)

  def to_string(self, node, result='', prefix=''):
    """
    Returns a string representation of the binary-search tree.
    :param node: The root of the subtree to display.
    """
    if not node:
      return result
    # Concatenate the prefix with the current node's data.
    result += f'{prefix}├──{str(node.data)}\n'
    # Whether the current node is the left child of its parent.
    isRight = node.parent and node.parent.right == node
    # A separator to display between the current node's children.
    separator = '│  ' if isRight else '   '
    # Recursively display the left children.
    result = self.to_string(node.right, result, prefix + separator)
    # Recursively display the right children.
    result = self.to_string(node.left, result, prefix + separator)
    return result

  def __repr__(self) -> str:
    return f'BinarySearchTree(comp={self.comparator}, size={self.size}, root={self.root.data if self.root else None}, nodes={list(map(lambda n: n.data, self.nodes()))})'
