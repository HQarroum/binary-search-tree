import com.algorithms.trees.bst.BinarySearchTree;

fun main() {
  // Creating the binary-search tree.
  val tree = BinarySearchTree<Int>({ a: Int, b: Int -> a - b });
  
  // Inserting values.
  for (i in arrayOf(50, 70, 60, 20, 90, 10, 40, 100)) {
    tree.insert(i);
  }

  // Printing the tree.
  println(tree.toString());
}
