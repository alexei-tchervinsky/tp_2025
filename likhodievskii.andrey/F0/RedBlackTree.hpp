#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <stack>
#include <type_traits>
#include <vector>


template<typename...>
using void_t = void;

template<typename T, typename = void>
struct is_comparable : std::false_type {
};

template<typename T>
struct is_comparable<T, void_t<
            decltype(std::declval<T>() < std::declval<T>()),
            decltype(std::declval<T>() > std::declval<T>()),
            decltype(std::declval<T>() == std::declval<T>()),
            decltype(std::declval<T>() != std::declval<T>())
        > > : std::true_type {
};

template<typename T, typename T0 = std::enable_if_t<is_comparable<T>::value> >
class RedBlackTree {
    enum class Color { RED, BLACK };

    struct Node;

    using NodePtr = std::shared_ptr<Node>;
    using WeakNodePtr = std::weak_ptr<Node>;

    struct Node {
        T key_;
        std::size_t frequency_ = 1;
        Color color_;
        NodePtr left_;
        NodePtr right_;
        WeakNodePtr parent_;

        Node(T k, Color c, WeakNodePtr p = WeakNodePtr{}) : key_(k),
                                                            color_(c),
                                                            left_(NIL),
                                                            right_(NIL),
                                                            parent_(p) {
        }
    };

public:
    RedBlackTree(): root(NIL) {
    };

    RedBlackTree(const RedBlackTree &) = delete;

    RedBlackTree &operator=(const RedBlackTree &) = delete;

    RedBlackTree(RedBlackTree &&other) noexcept;

    RedBlackTree &operator=(RedBlackTree &&other) noexcept;

    std::size_t getFrequency(const T &arg) const;

    ~RedBlackTree() = default;


    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        explicit Iterator(NodePtr root = NIL);

        reference operator*() const;

        pointer operator->() const;

        Iterator &operator++();

        [[nodiscard]] std::size_t getFrequency() const;

        Iterator operator++(int);

        bool operator==(const Iterator &other) const;

        bool operator!=(const Iterator &other) const;

    private:
        std::stack<NodePtr> stack;

        void fillStack(NodePtr node);
    };

    Iterator begin() const {
        return Iterator(root);
    }

    Iterator end() const {
        return Iterator();
    }


    std::vector<std::pair<T, int> > getTopKFrequent(std::size_t k) const {
        std::vector<std::pair<T, int> > elements;

        for (auto it = begin(); it != end(); ++it) {
            elements.push_back(std::make_pair(*it, it.getFrequency()));
        }
        std::sort(elements.begin(), elements.end(), [](const std::pair<T, int> &a, const std::pair<T, int> &b) {
            return a.second > b.second;
        });

        if (k > elements.size()) k = elements.size();

        std::vector<std::pair<T, int> > result;
        for (size_t i = 0; i < k; ++i) {
            result.push_back(elements[i]);
        }
        return result;
    }

    bool search(const T &k) const;

    bool insert(const T &key);

    bool remove(const T &key);

    [[nodiscard]] int getNumberOfNodes() const {
        return countNodes;
    }

private:
    static NodePtr NIL;
    NodePtr root = NIL;
    std::size_t countNodes = 0;

    NodePtr getUncle(const NodePtr &node) const;

    void rotateRight(NodePtr pivot);

    void rotateLeft(NodePtr pivot);

    void fixInsert(NodePtr pivot);

    NodePtr searchNode(const T &k) const;

    void replaceSubtree(NodePtr oldNode, NodePtr newNode);

    NodePtr minimum(NodePtr subtreeRoot);

    void fixDelete(NodePtr pivot);

    static NodePtr createNIL();
};

template<typename T, typename T0>
RedBlackTree<T, T0>::RedBlackTree(RedBlackTree &&other) noexcept: root(std::move(other.root)),
                                                                  countNodes(other.countNodes) {
    other.root = NIL;
    other.countNodes = 0;
}

template<typename T, typename T0>
RedBlackTree<T, T0> &RedBlackTree<T, T0>::operator=(RedBlackTree &&other) noexcept {
    if (this != &other) {
        root = std::move(other.root);
        countNodes = other.countNodes;
        other.root = NIL;
        other.countNodes = 0;
    }
    return *this;
}

template<typename T, typename T0>
std::size_t RedBlackTree<T, T0>::getFrequency(const T &arg) const {
    auto node = searchNode(arg);
    if (node != NIL) {
        return node->frequency_;
    }
    return 0;
}

template<typename T, typename T0>
RedBlackTree<T, T0>::Iterator::Iterator(NodePtr root): stack() {
    if (root != NIL) {
        fillStack(root);
    }
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator::reference RedBlackTree<T, T0>::Iterator::operator*() const {
    if (stack.empty()) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return stack.top()->key_;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator::pointer RedBlackTree<T, T0>::Iterator::operator->() const {
    if (stack.empty()) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return &stack.top()->key_;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator &RedBlackTree<T, T0>::Iterator::operator++() {
    if (stack.empty()) {
        throw std::out_of_range("Incrementing end iterator");
    }
    NodePtr node = stack.top();
    stack.pop();
    if (node->right_ != NIL) {
        fillStack(node->right_);
    }
    return *this;
}

template<typename T, typename T0>
std::size_t RedBlackTree<T, T0>::Iterator::getFrequency() const {
    return stack.top().get()->frequency_;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::Iterator RedBlackTree<T, T0>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::Iterator::operator==(const Iterator &other) const {
    return (stack.empty() && other.stack.empty()) ||
           (!stack.empty() && !other.stack.empty() && stack.top() == other.stack.top());
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::Iterator::operator!=(const Iterator &other) const {
    return !(*this == other);
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::Iterator::fillStack(NodePtr node) {
    while (node != NIL) {
        stack.push(node);
        node = node->left_;
    }
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::search(const T &k) const {
    return searchNode(k) != NIL;
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::insert(const T &key) {
    NodePtr found = searchNode(key);
    if (found != NIL) {
        ++(found->frequency_);
        return false;
    }

    if (root == NIL) {
        root = std::make_shared<Node>(key, Color::BLACK);
        root->left_ = root->right_ = NIL;
        countNodes++;
        return true;
    }

    NodePtr currentNode = root;
    NodePtr parent = NIL;

    while (currentNode != NIL) {
        parent = currentNode;
        if (key < currentNode->key_) {
            currentNode = currentNode->left_;
        } else if (key > currentNode->key_) {
            currentNode = currentNode->right_;
        } else {
            return false;
        }
    }

    auto newNode = std::make_shared<Node>(key, Color::RED, parent);
    if (key < parent->key_) {
        parent->left_ = newNode;
    } else {
        parent->right_ = newNode;
    }

    fixInsert(newNode);
    countNodes++;
    return true;
}

template<typename T, typename T0>
bool RedBlackTree<T, T0>::remove(const T &key) {
    NodePtr node = searchNode(key);
    if (node == NIL) return false;

    NodePtr successor = NIL;
    NodePtr child = NIL;
    Color originalColor = node->color_;

    if (node->left_ == NIL) {
        child = node->right_;
        replaceSubtree(node, child);
    } else if (node->right_ == NIL) {
        child = node->left_;
        replaceSubtree(node, child);
    } else {
        successor = minimum(node->right_);
        originalColor = successor->color_;
        child = successor->right_;

        if (successor->parent_.lock() != node) {
            replaceSubtree(successor, child);
            successor->right_ = node->right_;
            successor->right_->parent_ = successor;
        }
        replaceSubtree(node, successor);
        successor->left_ = node->left_;
        successor->left_->parent_ = successor;
        successor->color_ = node->color_;
    }

    if (originalColor == Color::BLACK) {
        fixDelete(child);
    }
    countNodes--;
    return true;
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::getUncle(const NodePtr &node) const {
    auto parent = node->parent_.lock();
    if (!parent) return NIL;
    auto grandparent = parent->parent_.lock();
    if (!grandparent) return NIL;
    return (parent == grandparent->left_) ? grandparent->right_ : grandparent->left_;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::rotateLeft(NodePtr pivot) {
    if (pivot == NIL || pivot->right_ == NIL) return;
    auto child = pivot->right_;
    pivot->right_ = child->left_;

    if (pivot->right_)
        pivot->right_->parent_ = pivot;

    child->parent_ = pivot->parent_;

    if (auto parent = pivot->parent_.lock()) {
        if (parent->left_ == pivot)
            parent->left_ = child;
        else
            parent->right_ = child;
    } else {
        root = child;
    }

    child->left_ = pivot;
    pivot->parent_ = child;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::rotateRight(NodePtr pivot) {
    if (pivot == NIL || pivot->left_ == NIL) return;
    auto child = pivot->left_;
    pivot->left_ = child->right_;

    if (pivot->left_)
        pivot->left_->parent_ = pivot;

    child->parent_ = pivot->parent_;

    if (auto parent = pivot->parent_.lock()) {
        if (parent->left_ == pivot)
            parent->left_ = child;
        else
            parent->right_ = child;
    } else {
        root = child;
    }

    child->right_ = pivot;
    pivot->parent_ = child;
}


template<typename T, typename T0>
void RedBlackTree<T, T0>::fixInsert(NodePtr pivot) {
    while (pivot != root && pivot->parent_.lock()->color_ == Color::RED) {
        auto parent = pivot->parent_.lock();
        auto grandparent = parent->parent_.lock();
        NodePtr uncle = (parent == grandparent->left_) ? grandparent->right_ : grandparent->left_;

        if (uncle->color_ == Color::RED) {
            parent->color_ = Color::BLACK;
            uncle->color_ = Color::BLACK;
            grandparent->color_ = Color::RED;
            pivot = grandparent;
        } else {
            if (parent == grandparent->left_) {
                if (pivot == parent->right_) {
                    pivot = parent;
                    rotateLeft(pivot);
                    parent = pivot->parent_.lock();
                }
                parent->color_ = Color::BLACK;
                grandparent->color_ = Color::RED;
                rotateRight(grandparent);
            } else {
                if (pivot == parent->left_) {
                    pivot = parent;
                    rotateRight(pivot);
                    parent = pivot->parent_.lock();
                }
                parent->color_ = Color::BLACK;
                grandparent->color_ = Color::RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color_ = Color::BLACK;
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::searchNode(const T &k) const {
    if (root == NIL) return NIL;
    NodePtr current = root;
    while (current != NIL) {
        if (current->key_ == k) return current;
        current = (current->key_ > k) ? current->left_ : current->right_;
    }
    return NIL;
}


template<typename T, typename T0>
void RedBlackTree<T, T0>::replaceSubtree(NodePtr oldNode, NodePtr newNode) {
    if (oldNode == NIL) return;

    if (auto parent = oldNode->parent_.lock()) {
        if (oldNode == parent->left_) {
            parent->left_ = newNode;
        } else {
            parent->right_ = newNode;
        }
    } else {
        root = newNode;
    }

    if (newNode != NIL) {
        newNode->parent_ = oldNode->parent_;
    }
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::minimum(NodePtr subtreeRoot) {
    if (subtreeRoot == NIL) return NIL;
    while (subtreeRoot->left_ != NIL) {
        subtreeRoot = subtreeRoot->left_;
    }
    return subtreeRoot;
}

template<typename T, typename T0>
void RedBlackTree<T, T0>::fixDelete(NodePtr pivot) {
    while (pivot != root && pivot->color_ == Color::BLACK) {
        auto parent = pivot->parent_.lock();
        if (!parent) break;

        bool isLeftChild = (pivot == parent->left_);
        NodePtr sibling = isLeftChild ? parent->right_ : parent->left_;

        if (sibling != NIL && sibling->color_ == Color::RED) {
            sibling->color_ = Color::BLACK;
            parent->color_ = Color::RED;
            if (isLeftChild) {
                rotateLeft(parent);
                sibling = parent->right_;
            } else {
                rotateRight(parent);
                sibling = parent->left_;
            }
        }

        if ((sibling->left_ == NIL || sibling->left_->color_ == Color::BLACK) &&
            (sibling->right_ == NIL || sibling->right_->color_ == Color::BLACK)) {
            if (sibling != NIL) {
                sibling->color_ = Color::RED;
            }
            pivot = parent;
        } else {
            if (isLeftChild && (sibling->right_ == NIL || sibling->right_->color_ == Color::BLACK)) {
                if (sibling->left_ != NIL) {
                    sibling->left_->color_ = Color::BLACK;
                }
                sibling->color_ = Color::RED;
                rotateRight(sibling);
                sibling = parent->right_;
            } else if (!isLeftChild && (sibling->left_ == NIL || sibling->left_->color_ == Color::BLACK)) {
                if (sibling->right_ != NIL) {
                    sibling->right_->color_ = Color::BLACK;
                }
                sibling->color_ = Color::RED;
                rotateLeft(sibling);
                sibling = parent->left_;
            }

            sibling->color_ = parent->color_;
            parent->color_ = Color::BLACK;
            if (isLeftChild) {
                if (sibling->right_ != NIL) {
                    sibling->right_->color_ = Color::BLACK;
                }
                rotateLeft(parent);
            } else {
                if (sibling->left_ != NIL) {
                    sibling->left_->color_ = Color::BLACK;
                }
                rotateRight(parent);
            }
            pivot = root;
        }
    }
    pivot->color_ = Color::BLACK;
}

template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::createNIL() {
    auto nil = std::make_shared<Node>(T{}, Color::BLACK);
    nil->left_ = nil->right_ = nil;
    nil->parent_ = WeakNodePtr{};
    return nil;
}


template<typename T, typename T0>
typename RedBlackTree<T, T0>::NodePtr RedBlackTree<T, T0>::NIL = createNIL();

#endif //REDBLACKTREE_HPP
