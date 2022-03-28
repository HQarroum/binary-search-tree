import { ITree } from '../tree';
import { Node } from '../node';

/**
 * A depth-first-search iterator implementation.
 */
export class DfsIterator<T> implements Iterator<Node<T>> {
  private tree: ITree<T>;
  private node: Node<T> | null;
  private iterations: number;

  /**
   * Iterator constructor.
   * @param tree the tree to iterate over.
   */
  constructor(tree: ITree<T>) {
    this.tree = tree;
    this.node = this.tree.root();
    this.iterations = 0;
  }

  /**
   * @returns the next node in the tree.
   */
  public next(): IteratorResult<Node<T>> {
    if (!this.tree.size()) {
      // The tree is empty.
      return ({ done: true, value: null });
    }

    if (!this.node) {
      // There are no next node.
      return ({ done: true, value: null });
    }

    if (this.iterations == 0) {
      // Initializing the node to the smallest node
      // in the binary search tree.
      this.node = this.tree.min();
    } else {
      if (this.node.right) {
        this.node = this.tree.min(this.node.right);
      } else {
        let current = this.node.parent;

        while (current && this.node === current.right) {
          this.node = current;
          current = current.parent;
        }
        this.node = current;
      }
    }

    if (!this.node) {
      return ({ done: true, value: null });
    }
    
    this.iterations++;
    return ({ done: false, value: this.node });
  }
}