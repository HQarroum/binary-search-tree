#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <functional>
#include "iterators/dfs_iterator.hpp"

namespace bst {
  
  /**
   * @brief A helper function to invoke a function
   * for each given argument.
   * @tparam d the callable to call.
   * @tparam args a variadic list of arguments.
   * @return the result of the callable.
   */
  template<class F, class...Args>
  F for_each_arg(F f, Args&&...args) {
    (f(std::forward<Args>(args)),...);
    return f;
  }

  /**
   * @brief Describes the direction binding that can
   * exist between two nodes.
   */
  enum direction_t {
    LEFT,
    RIGHT
  };

  /**
   * @brief Type definition for the comparator function
   * implementation used to compare nodes together.
   */
  template <typename T>
  using comparator_t = std::function<int(const T&, const T&)>;

  /**
   * @brief Describes the options that can be passed to the
   * binary-search tree.
   */
  template <typename T>
  struct options_t {
    comparator_t<T> comparator;
  };

  /**
   * @brief Describes a binary-search tree node
   * attributes.
   */
  template <typename T>
  struct node_t {

    /**
     * @brief Node constructor.
     * @param data The data to be stored in the node.
     */
    node_t(const T& data) :
      data{data}, left{nullptr}, right{nullptr}, parent{nullptr}, tree{nullptr} {}

    /**
     * @brief Node move constructor.
     * @param data The data to be moved to the node.
     */
    node_t(const T&& data) :
      data{std::move(data)}, left{nullptr}, right{nullptr}, parent{nullptr}, tree{nullptr} {}

    T           data;
    node_t<T>*  left;
    node_t<T>*  right;
    node_t<T>*  parent;
    tree_t<T>*  tree;
  };

  template <typename T>
  struct tree_t {

    friend class dfs_iterator_t<T>;

    /**
     * @brief Construct a new binary search tree object.
     * @param options the options to associate to the tree.
     */
    tree_t(): root{nullptr}, size_of_tree{0} {
      this->options = (options_t<T>) {
        .comparator = [] (const T& a, const T& b) -> int {
          return (a - b);
        }
      };
    }

    /**
     * @brief Construct a new binary search tree object.
     * @param options the options to associate to the tree.
     */
    tree_t(const options_t<T>& options): root{nullptr}, size_of_tree{0}, options{options} {}
    
    /**
     * Copy-constructor is deleted.
     */
    tree_t(const tree_t&) = delete;

    /**
     * Assignment operator is deleted. 
     */
    tree_t& operator=(const tree_t&) = delete;

    template <class... Args>
    void insert(Args... args) {
      for_each_arg([&] (const T& arg) { this->insert(arg); }, args...);
    }

    /**
     * @brief Inserts the given `data` in the binary-search tree.
     * @param data a reference to the data to insert in the binary-search tree.
     * @return a pointer to the created node that wraps the given data.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    const node_t<T>* insert(const T& data) {
      auto node = new node_t<T>(data);

      // The tree is empty.
      if (!this->size_of_tree) {
        this->size_of_tree = 1;
        node->tree         = this;
        return (this->root = node);
      }

      // Otherwise, we recursively traverse the tree to find
      // the right position for the new node.
      return (insert(this->root, node));
    }

    /**
     * @brief Removes the node associated with the given `data` from the binary-search tree.
     * @param data the data to remove from the binary-search tree.
     */
    void remove(const T& data) {
      
    }
    
    /**
     * @brief Clears the given subtree.
     * @param node the root of the subtree to clear.
     */
    void clear(node_t<T>* node) {
      if (!node) return;

      // Recursively clear the left subtree.
      clear(node->left);
      clear(node->right);

      // Detaching the node from its parent.
      if (node->parent && node->parent->left == node)
        node->parent->left = nullptr;
      if (node->parent && node->parent->right == node)
        node->parent->right = nullptr;

      // Decremeneting the size of the tree.
      this->size_of_tree--;

      // If the node is the root, we need to assign
      // the root to a null pointer type.
      if (this->root == node) {
        this->root = nullptr;
      }
    }
    
    /**
     * @brief Clears the binary-search tree.
     * @return the number of nodes removed from the tree.
     */
    void clear() {
      this->clear(this->root);
    }

    /**
     * @brief Recursively traverse the subtree to find
     * the node associated with the given `data`.
     * @param node the node to start the traversal from.
     * @param data the data to find in the given subtree.
     * @return a pointer to the found node, or NULL if the node
     * was not found.
     * @note Complexity is O(log(n)) on average, O(n) in the worst case.
     */
    const node_t<T>* find(const node_t<T>* node, const T& data) const {
      /* Ensure that the node and the given data are valid. */
      if (!node || !node->data || !data) {
        return (nullptr);
      }

      /* Comparing the value associated with the nodes. */
      auto result = this->options.comparator(data, node->data);

      if (result < 0) {
        return (find(node->left, data));
      } else if (result > 0) {
        return (find(node->right, data));
      } else {
        return (node);
      }
    }

    /**
     * @brief A method finding the node associated with `data`
     * in the binary-search tree.
     * @param data a reference to the data to look up.
     * @return a pointer to the node containing the data, or NULL if the node
     * was not found.
     * @note Complexity is O(log(n)) on average, O(n) in the worst case.
     */
    const node_t<T>* find(const T& data) const {
      return (this->find(this->root, data));
    }

    /**
     * @brief Recursively traverse the given subtree to find
     * the node associated with the smallest value.
     * @param node the node to start the traversal from.
     * @return a pointer to the node associated with the smallest value.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    const node_t<T>* min(const node_t<T>* node) const {
      while (node && node->left != NULL)
        node = node->left;
      return (node);
    } 

    /**
     * @brief Recursively traverse the binary-search tree to find
     * the node associated with the smallest value.
     * @return a pointer to the node associated with the smallest value.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    const node_t<T>* min() const {
      return (this->min(this->root));
    }

    /**
     * @brief Recursively traverse the given subtree to find
     * the node associated with the biggest value.
     * @param node the node to start the traversal from.
     * @return a pointer to the node associated with the biggest value.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    const node_t<T>* max(const node_t<T>* node) const {
      while (node && node->right != NULL)
        node = node->right;
      return (node);
    }
    
    /**
     * @brief Recursively traverse the binary-search tree to find
     * the node associated with the biggest value.
     * @return a pointer to the node associated with the biggest value.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    const node_t<T>* max() const {
      return (this->max(this->root));
    }

    /**
     * @return the number of nodes contained by the
     * binary search tree.
     */
    size_t size() const {
      return (this->size_of_tree);
    }

    /**
     * @return a string representation of the binary-search tree.
     * @param node the node to start the traversal from.
     * @param result the string to append the result to.
     * @param prefix the prefix to use for each line.
     * @note Complexity is O(n) on average, O(n) on the worst case.
     */
    const std::string to_string(const node_t<T>* node, std::string result = "", std::string prefix = "") const {
      if (!node) {
        // We reached the end of a subtree.
        return (result);
      }
      // Concatenate the prefix with the current node's data.
      result += prefix + "├──" + std::to_string(node->data) + "\n";
      // Whether the current node is the left child of its parent.
      bool isRight = node->parent && node->parent->right == node;
      // A separator to display between the current node's children.
      std::string separator = isRight ? "│  " : "   ";
      // Recursively display the left children.
      result = to_string(node->right, result, prefix + separator);
      // Recursively display the left children.
      result = to_string(node->left, result, prefix + separator);
      return (result);
    }
    
    /**
     * @return a string representation of the binary-search tree.
     */
    const std::string to_string() const {
      return (this->to_string(this->root));
    }

    /**
     * @brief Outputs a string representation of the binary-search tree
     * to the given stream.
     * @param stream the stream to output the string representation to.
     * @param tree the binary-search tree to output.
     * @return a reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& stream, const tree_t<T>& tree) {
      stream << tree.to_string();
      return (stream);
    }

    typedef dfs_iterator_t<T> const_iterator;
    typedef const_iterator iterator;
    
    typename tree_t<T>::const_iterator begin() const {
      return (dfs_iterator_t<T>(this->min(), this));
    }

    typename tree_t<T>::const_iterator end() const {
      return (dfs_iterator_t<T>(nullptr, this));
    }

    private:
      node_t<T>* root;
      size_t size_of_tree;
      options_t<T> options;

      /**
       * @brief A helper function to attach a node to another node.
       * @param node the node to attach the new node to.
       * @param new_node the new node to attach.
       * @param direction whether the new node should be attached to the left or right.
       * @return a pointer to the newly attached node.
       * @note Complexity is O(log(n)) on average, O(n) on the worst case.
       */
      node_t<T>* attach(node_t<T>* node, node_t<T>* new_node, direction_t direction) {
        if (direction == LEFT) {
          node->left = new_node;
        } else {
          node->right = new_node;
        }
        new_node->parent = node;
        new_node->tree = this;
        this->size_of_tree++;
        return (new_node);
      }

      /**
       * @brief Inserts a new node into the given subtree.
       * @param node the root of the subtree to insert the node into.
       * @param new_node the new node to insert.
       * @return a pointer to the newly inserted node.
       * @note Complexity is O(log(n)) on average, O(n) on the worst case.
       */
      node_t<T>* insert(node_t<T>* node, node_t<T>* new_node) {
        auto result = this->options.comparator(new_node->data, node->data);

        if (result < 0) {
          if (node->left) {
            return (this->insert(node->left, new_node));
          } else {
            return (this->attach(node, new_node, LEFT));
          }
        } else if (result > 0) {
          if (node->right) {
            return (this->insert(node->right, new_node));
          } else {
            return (this->attach(node, new_node, RIGHT));
          }
        } else {
          return (node);
        }
      }
  };
};

#endif // BINARY_SEARCH_TREE_HPP
