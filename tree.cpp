#include <iostream>

template <typename T>
struct Node {
    T val;
    Node* left;
    Node* right;

    Node(T v) : val(v), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
    Node<T>* root = nullptr;
public:
    Node<T>* minNode(Node<T>* node);
    void insert(T value);
    void print();
    void inorder(Node<T>* node);
    void inorder() { inorder(root); std::cout << std::endl; }
    void preorder(Node<T>* node);
    void preorder() { preorder(root); std::cout << std::endl; }
    void postorder(Node<T>* node);
    void postorder() { postorder(root); std::cout << std::endl; }
    bool find(Node<T>* node, T value);
    bool find(T value) { return find(root, value);}
    T min(Node<T>* node);
    T min() {return min(root);}
    T max(Node<T>* node);
    T max() {return max(root);}
    Node<T>* next(Node<T>* node, T value);
    Node<T>* next(T value) { return next(root, value);}
    Node<T>* prev(Node<T>* node, T value);
    Node<T>* prev(T value) { return prev(root, value);}
    Node<T>* minValueNode(Node<T>* node);
    Node<T>* erase(Node<T>* node, T value);
    Node<T>* erase(T value) { return erase(root, value);}
};

template <typename T>
Node<T>* BST<T>::minNode(Node<T>* node) {
   if(node->left) {
        return minNode(node->left);
   }
}

template <typename T>
void BST<T>::insert(T value) {    //rec
    if (root == nullptr) {
        root = new Node<T>(value);
        return;
    }

    Node<T>* node = root;
    while (true) {
        if (value < node->val) {
            if (node->left == nullptr) {
                node->left = new Node<T>(value);
                return;
            }
            node = node->left;
        } else {
            if (node->right == nullptr) {
                node->right = new Node<T>(value);
                return;
            }
            node = node->right;
        }
    }
}


template <typename T>
void BST<T>::print() {//del
    inorder(root);
}

template <typename T>
void BST<T>::inorder(Node<T>* node) {
    if (!node) {
        return;
    }
    inorder(node->left);
    std::cout << node->val << '|';
    inorder(node->right);
}

template <typename T>
void BST<T>::preorder(Node<T>* node) {
    if (!node) {
        return;
    }
    std::cout << node->val << '|';
    inorder(node->left);    //in->pre
    inorder(node->right);
}

template <typename T>
void BST<T>::postorder(Node<T>* node) {
    if (!node) {
        return;
    }
    inorder(node->left);    //in->post
    inorder(node->right);
    std::cout << node->val << '|';
    
}

template <typename T>
bool BST<T>::find(Node<T>* node, T value) {
    if (!node) {
        return false;
    }
    if(node->val == value) {
        return true;
    } else if(node->val > value) {
        return find(node->left, value);
    } else {
        return find(node->right, value);
    }

}

template <typename T>
T BST<T>::min(Node<T>* node) {
    //if (!node->left) {
    //    return node->val;
    //} else {
    //    return min(node->left);
    //}
    return !node->left ? node->val : min(node->left);
}

template <typename T>
T BST<T>::max(Node<T>* node) {
    //if (!node->right) {
    //    return node->val;
    //} else {
    //    return max(node->right);
    //}
    return !node->right ? node->val : max(node->right);
}

template <typename T>
Node<T>* BST<T>::next(Node<T>* node, T value) {    //add parent pointer in Node and rec
    Node<T>* succ = nullptr;
    while (node) {
        if (value < node->val) {
            succ = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return succ;
}

template <typename T>
Node<T>* BST<T>::prev(Node<T>* node, T value) {
    Node<T>* succ = nullptr;
    while (node) {
        if (value > node->val) {
            succ = node;
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return succ;
}

template <typename T>
Node<T>* BST<T>::minValueNode(Node<T>* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

template <typename T>
Node<T>* BST<T>::erase(Node<T>* node,T value) { // new logic for parent
    if (!node) return nullptr;

    if (value < node->val)
        node->left = erase(node->left, value);
    else if (value > node->val)
        node->right = erase(node->right, value);
    else {
        // Узел найден
        if (!node->left) {
            Node<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            Node<T>* temp = node->left;
            delete node;
            return temp;
        }
        // Узел с двумя детьми
        Node<T>* temp = minValueNode(node->right); // inorder successor
        node->val = temp->val;
        node->right = erase(node->right, temp->val); // удалить successor
    }
    return node;
}

int main() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);
    tree.insert(1);
    tree.insert(-4);
    tree.inorder();
    tree.postorder();
    tree.preorder();
    std::cout << tree.find(6) << std::endl;
    std::cout << tree.min() << std::endl;
    std::cout << tree.max() << std::endl;
    std::cout << tree.next(5)->val << std::endl;
    std::cout << tree.prev(5)->val << std::endl;
    tree.erase(3);
    tree.inorder();
    return 0;
}
