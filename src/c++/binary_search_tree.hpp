#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <functional>

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
   * @brief Type definition for the comparator function
   * implementation used to compare nodes together.
   */
  template <typename T>
  using comparator_t = std::function<void(const T&, const T&)>;

  /**
   * @brief Describes the options that can be passed to the
   * binary-search tree.
   */
  template <typename T>
  struct options_t {
    comparator_t<T> comparator;
  };

  template <typename T>
  class tree_t;

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
    node_t() : data(T()) {
      this->left   = nullptr;
      this->right  = nullptr;
      this->parent = nullptr;
      this->tree   = nullptr;
    }

    /**
     * @brief Node constructor.
     * @param data The data to be stored in the node.
     */
    node_t(const T* data) : data(data) {
      this->left   = nullptr;
      this->right  = nullptr;
      this->parent = nullptr;
      this->tree   = nullptr;
    }

    T*     data;
    node_t<T>*  left;
    node_t<T>*  right;
    node_t<T>*  parent;
    tree_t<T>*  tree;
  };

  template <typename T>
  class tree_t {

    public:

      /**
       * @brief Construct a new binary search tree object.
       * @param options the options to associate to the tree.
       */
      tree_t()
        : root_(),
          size_(0) {
        this->options_ = {
          .comparator = [] (const T& a, const T& b) {
            return (a < b);
          }
        };
      }

      /**
       * @brief Construct a new binary search tree object.
       * @param options the options to associate to the tree.
       */
      tree_t(const options_t<T>& options)
        : root_(),
          size_(0),
          options_(options) {}
      
      /**
       * @brief Binary search tree destructor.
       */
      ~tree_t() {
        
      }

      node_t<T> attach(node_t<T>* node, node_t<T>* new_node, direction_t direction) {
        if (direction == LEFT) {
          node.left = new_node;
        } else {
          node.right = new_node;
        }
        new_node.parent = node;
        new_node.tree = node.tree;
        new_node.tree->size++;
        return (new_node);
      }

      node_t<T> insert_in(node_t<T>* node, const node_t<T>* data) {
        int result = this->options_.comparator(data, node.data);

        if (result < 0) {
          if (node.left) {
            return (insert_in(node.left, data));
          } else {
            return (attach(node, data, LEFT));
          }
        } else if (result > 0) {
          if (node->right) {
            return (insert_in(node.right, data));
          } else {
            return (attach(node, data, RIGHT));
          }
        } else {
          return (NULL);
        }
      }

      /**
       * @brief Insert a new node in the tree.
       * @param data the data to insert.
       * @return the node inserted.
       */
      node_t<T> insert(const T* data) {
        node_t<T> node = node_t<T>(data);

        /* The tree is empty. */
        if (!this->size_) {
          this->size_ = 1;
          node.tree = this;
          return (root_.data = data);
        }
        return (this->insert_in(&root_, node));
      }

      /**
       * @brief Removes the node associated with the given `data` from the binary-search tree.
       * @param data the data to remove from the binary-search tree.
       */
      void remove(const T& data) {

      }
      
      /**
       * @brief Clears the binary-search tree.
       * @return the number of nodes removed from the tree.
       */
      size_t clear() {
        return (0);
      }

      const node_t<T>* find(const T& data) const {
        return (nullptr);
      }

      const node_t<T>* min() const {
        return (nullptr);
      }

      const node_t<T>* max() const {
        return (nullptr);
      }

      size_t size() const {
        return (this->size_);
      }

    private:
      node_t<T> root_;
      size_t size_;
      options_t<T> options_;
  };
};

#endif // BINARY_SEARCH_TREE_HPP
