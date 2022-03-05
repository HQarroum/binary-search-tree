#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <optional>
#include <iterator>

namespace bst {
  
  /**
   * @brief Describes the direction binding that can
   * exist between two nodes.
   */
  enum direction_t {
    LEFT,
    RIGHT
  };  

  /**
   * @brief Describes the options that can be passed to the
   * binary-search tree.
   */
  template <typename T>
  struct options_t {

    /**
     * @brief Type definition for the comparator function
     * implementation used to compare values together.
     */
    using comparator_t = std::function<int(const T&, const T&)>;

    /**
     * @brief Type definition for the to_string function
     * implementation used to transform values into strings.
     */
    using to_string_t = std::function<std::string(const T&)>;

    /**
     * @brief The binary search tree options.
     * @param c the comparator function.
     * @param s the stringifier function.
     */
    options_t(comparator_t c, to_string_t s)
      : comparator(c), stringifier(s) {}
    
    /**
     * @brief Compares two values.
     * @param lhs the first value to compare.
     * @param rhs the second value to compare.
     * @return the result of the comparison.
     */
    int compare(const T& lhs, const T& rhs) const {
      return (comparator(lhs, rhs));
    }

    /**
     * @brief Transforms a value into a string.
     * @param value the value to transform.
     * @return the resulting string.
     */
    std::string to_string(const T& value) const {
      return (stringifier(value));
    }
    
    private:
      comparator_t comparator;
      to_string_t  stringifier;
  };

  /**
   * Forward declaration of the depth-first-search iterator.
   */
  template <typename T>
  class dfs_iterator_t;

  /**
   * Forward declaration of the node.
   */
  template <typename T>
  struct node_t;

  /**
   * @brief Definition of the binary search tree.
   */
  template <typename T, typename DefaultIterator = dfs_iterator_t<T>>
  struct tree_t {

    /**
     * The default iterator has access to the binary-search tree
     * implementation.
     */
    friend DefaultIterator;

    /**
     * Defining the default iterator at the tree level.
     */
    using const_iterator = DefaultIterator;
    using iterator = const_iterator;

    /**
     * @brief Construct a new binary search tree object.
     * @param options the options to associate to the tree.
     */
    tree_t(): root{nullptr}, size_of_tree{0}, options(
      [] (const T& a, const T& b) -> int {
        return (a - b);
      },
      [] (const T& value) -> std::string {
        return (std::to_string(value));
      }) {}

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

    /**
     * @brief Binary-search tree destructor.
     */
    ~tree_t() {
      this->clear();
    }

    /**
     * @brief Inserts a set of values provided by the iterator
     * in the binary-search tree.
     * @param begin the iterator to the beginning of the iterable.
     * @param end the iterator to the end of the iterable.
     */
    template<typename Iterator>
    void insert(Iterator begin, Iterator end) {
      for (Iterator it = begin; it != end; ++it) {
        this->insert(*it);
      }
    }

    /**
     * @brief Inserts a set of values provided as variadic arguments
     * in the binary search tree.
     * @param args the values to insert in the tree.
     */
    template <class... Args>
    void insert(Args... args) {
      auto callable = [&] (const T& arg) { this->insert(arg); };
      (callable(std::forward<Args>(args)),...);
    }

    /**
     * @brief Inserts the given `data` in the binary-search tree.
     * @param data a reference to the data to insert in the binary-search tree.
     * @return a pointer to the created node that wraps the given data.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    const node_t<T>* insert(const T& data) {
      // The tree is empty.
      if (!this->size_of_tree) {
        auto new_node      = new node_t<T>(data);
        new_node->tree     = this;
        this->size_of_tree = 1;
        return (this->root = new_node);
      }

      // Otherwise, we recursively traverse the tree to find
      // the right position for the new node.
      return (insert(this->root, data));
    }

    /**
     * @brief Removes a set of values provided by the iterator
     * from the binary-search tree.
     * @param begin the iterator to the beginning of the iterable.
     * @param end the iterator to the end of the iterable.
     */
    template<typename Iterator>
    void remove(Iterator begin, Iterator end) {
      for (Iterator it = begin; it != end; ++it) {
        this->remove(*it);
      }
    }

    /**
     * @brief Removes a set of values provided as variadic arguments
     * from the binary search tree.
     * @param args the values to remove from the tree.
     * @note Complexity is O(nlog(n)) on average, O(n2) on the worst case.
     */
    template <class... Args>
    void remove(Args... args) {
      auto callable = [&] (const T& arg) { this->remove(arg); };
      (callable(std::forward<Args>(args)),...);
    }

    /**
     * @brief Removes the node associated with the given `data` from the binary-search tree
     * starting from the given subtree.
     * @param node the subtree to walk the tree from. 
     * @param data the data to remove from the binary-search tree.
     * @return a pointer to the successor node, or a NULL value
     * if there is no successor.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    node_t<T>* remove(node_t<T>* node, const T& data) {
      if (!node)
        return (nullptr);
      
      // Comparing the value associated with the nodes.
      int result = this->options.compare(data, node->value());
      
      if (result < 0)
        node->left = remove(node->left, data);
      else if (result > 0)
        node->right = remove(node->right, data);
      else {
        // The node doesn't have any children.
        if (!node->left && !node->right) {
          // If the node is the root, we need to set the root to nullptr.
          if (this->root == node) this->root = nullptr;
          delete node;
          this->size_of_tree--;
          return (nullptr);
        // The node has one child.
        } else if (!node->left || !node->right) {
          // Finding the child node.
          auto successor = node->right ? node->right : node->left;
          // Setting the new parent of the child node.
          successor->parent = node->parent;
          // If the node is the root, the child node becomes the new root.
          if (this->root == node) this->root = successor;
          delete node;
          this->size_of_tree--;
          return (successor);
        // The node has two children.
        } else {
          const auto successor = min(node->right);
          node->data = successor->data;
          node->right = remove(node->right, successor->data);
        }
      }
      return (node);
    }

    /**
     * @brief Removes the node associated with the given `data` from the binary-search tree.
     * @param data the data to remove from the binary-search tree.
     * @note Complexity is O(log(n)) on average, O(n) on the worst case.
     */
    void remove(const T& data) {
      remove(this->root, data);
    }
    
    /**
     * @brief Clears the given subtree.
     * @param node the root of the subtree to clear.
     * @note Complexity is O(n) on average.
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
      delete node;
    }
    
    /**
     * @brief Clears the binary-search tree.
     * @return the number of nodes removed from the tree.
     * @note Complexity is O(n) on average.
     */
    void clear() {
      this->clear(this->root);
    }

    /**
     * @brief Looks-up the binary-search tree for the nodes
     * associated with the given iterator.
     * @param begin the iterator to the beginning of the iterable.
     * @param end the iterator to the end of the iterable.
     * @return a vector of optional pointers to the found nodes.
     */
    template<typename Iterator>
    auto find(Iterator begin, Iterator end) {
      std::vector<std::optional<const node_t<T>*>> nodes;

      for (Iterator it = begin; it != end; ++it) {
        nodes.push_back(find(*it));
      }
      return (nodes);
    }

    /**
     * @brief Looks-up the binary-search tree for the nodes
     * associated with the given variadic arguments.
     * @param args the values to search for in the tree.
     * @return an array of optional pointers to the found nodes.
     */
    template <class... Args, std::enable_if_t<(sizeof...(Args) >= 2)>* = nullptr>
    auto find(Args... args) {
      size_t idx = 0;
      std::array<
        std::optional<const node_t<T>*>, sizeof...(Args)
      > nodes = {};

      // The callable function inserts the results
      // of the find operation into the array.
      auto callable = [&] (const T& arg) {
        nodes[idx++] = this->find(arg);
      };

      (callable(std::forward<Args>(args)),...);
      return (nodes);
    }

    /**
     * @brief Recursively traverse the subtree to find
     * the node associated with the given `data`.
     * @param node the node to start the traversal from.
     * @param data the data to find in the given subtree.
     * @return an optional pointer to the found node.
     * @note Complexity is O(log(n)) on average, O(n) in the worst case.
     */
    std::optional<const node_t<T>*> find(const node_t<T>* node, const T& data) const {
      /* Ensure that the node and the given data are valid. */
      if (!node) {
        return {};
      }

      /* Comparing the value associated with the nodes. */
      auto result = this->options.compare(data, node->value());

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
    std::optional<const node_t<T>*> find(const T& data) const {
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
      while (node && node->left != nullptr)
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
      while (node && node->right != nullptr)
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
      result += prefix + "├──" + this->options.to_string(node->value()) + "\n";
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
    
    /**
     * @return an iterator to the first node in the binary-search tree.
     * @note Uses the depth-first search iterator by default.
     */
    const_iterator begin() const {
      return (DefaultIterator(this->min(), this));
    }

    /**
     * @return an iterator to the last node in the binary-search tree.
     * @note Uses the depth-first search iterator by default.
     */
    const_iterator end() const {
      return (DefaultIterator(nullptr, this));
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
      node_t<T>* attach(node_t<T>* node, const T& data, direction_t direction) {
        auto new_node = new node_t<T>(data);

        direction == LEFT ? node->left = new_node : node->right = new_node;
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
      node_t<T>* insert(node_t<T>* node, const T& data) {
        // Comparing the new node's value with the current node's value.
        auto result = this->options.compare(data, node->value());

        if (result < 0) {
          return (node->left ? insert(node->left, data) : attach(node, data, LEFT));
        } else if (result > 0) {
          return (node->right ? insert(node->right, data) : attach(node, data, RIGHT));
        } else {
          return (NULL);
        }
      }
  };

  // Definition of the depth-first search iterator.
  template <typename T>
  class dfs_iterator_t : public std::iterator<std::bidirectional_iterator_tag, T> {

    // Iterator members.
    const node_t<T>* ptr;
    const tree_t<T>* tree;

    public:

      /**
       * @brief Construct a new depth-first iterator.
       * @param node the node to start the iteration from.
       * @param tree the tree to iterate over.
       */
      dfs_iterator_t(const node_t<T>* node, const tree_t<T>* tree): ptr{node}, tree{tree} {}

      /**
       * @brief Construct a new depth-first iterator.
       */
      dfs_iterator_t(): ptr{nullptr}, tree{nullptr} {}

      /**
       * @brief Compares two iterators for equality.
       * @param other the iterator to compare with.
       * @return true if the iterators are equal, false otherwise.
       */
      bool operator==(const dfs_iterator_t& other) const {
        return (this->tree == other.tree && this->ptr == other.ptr);
      }

      /**
       * @brief Compares two iterators for inequality.
       * @param other the iterator to compare with.
       * @return true if the iterators are not equal, false otherwise.
       */
      bool operator!=(const dfs_iterator_t& other) const {
        return (this->tree != other.tree || this->ptr != other.ptr);
      }

      /**
       * @brief De-references the iterator.
       * @return the value of the node currently iterated over.
       * If the iteration ended, an exception is thrown.
       */
      const T& operator*() const {
        if (!this->ptr) {
            throw std::out_of_range("Iterator is out of range");
        }
        return (this->ptr->value());
      }
  
      /**
       * @brief Increments the iterator.
       * @return a reference to the iterator.
       */
      dfs_iterator_t& operator++() {
        if (this->ptr == nullptr) {
          // Initialize the node pointer to the root node of the tree.
          this->ptr = this->tree->root;
          // If the tree is empty, we raise an exception.
          if (!this->ptr) {
            throw std::out_of_range("Iterator is out of range");
          }
          // Initializing the node to the smallest node
          // in the binary search tree.
          this->ptr = this->tree->min(this->ptr);
        } else {
          // If a right node exist, we iterate right,
          // and we iterate again to the node with the smallest value.
          if (this->ptr->right) {
            this->ptr = this->tree->min(this->ptr->right);
          } else {
            auto node = this->ptr->parent;
            // If no right node exists, we iterate upwards until
            // we find a node with a left node.
            while (node && this->ptr == node->right) {
              this->ptr = node;
              node = node->parent;
            }
            this->ptr = node;
          }
        }
        return (*this);
      }

      /**
       * @brief Postfix increment operator.
       * @return a copy of the iterator before incrementing it.
       */
      dfs_iterator_t operator++(int) {
        dfs_iterator_t<T> tmp = *this;
        ++(*this);
        return (tmp);
      }

      /**
       * @brief Decrements the iterator.
       * @return a reference to the iterator.
       */
      dfs_iterator_t& operator--() {
        if (this->ptr == nullptr) {
          // Initialize the node pointer to the root node of the tree.
          this->ptr = this->tree->root;
          // If the tree is empty, we raise an exception.
          if (!this->ptr) {
            throw std::out_of_range("Iterator is out of range");
          }
          // Initializing the node to the biggest node
          // in the binary search tree.
          this->ptr = this->tree->max(this->ptr);
        } else {
          // If a left node exist, we iterate left,
          // and we iterate until we find the node with
          // the biggest value in the left subtree.
          if (this->ptr->left) {
            this->ptr = this->tree->max(this->ptr->left);
          } else {
            auto node = this->ptr->parent;
            // If no left node exists, we iterate upwards until
            // we find a node with a right node.
            while (node && this->ptr == node->left) {
              this->ptr = node;
              node = node->parent;
            }
            this->ptr = node;
          }
        }
        return (*this);
      }

      /**
       * @brief Postfix decrement operator.
       * @return a copy of the iterator before decrementing it.
       */
      dfs_iterator_t operator--(int) {
        dfs_iterator_t<T> tmp = *this;
        --(*this);
        return (tmp);
      }
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

    /**
     * @return a reference to the data stored by the node.
     */
    const T& value() const {
      return (this->data);
    }

    T          data;
    node_t<T>* left;
    node_t<T>* right;
    node_t<T>* parent;
    tree_t<T>* tree;
  };
};

#endif // BINARY_SEARCH_TREE
