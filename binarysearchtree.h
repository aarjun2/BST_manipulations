// BinarySearchTree class
// Creates a BST to store values
// Uses BinaryNode which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "binarynode.h"
using namespace std;
template<class ItemType>
class BinarySearchTree {
public:
    // constructor, empty tree
    BinarySearchTree<ItemType>() {
        rootPtr = nullptr;
    }
    // constructor, tree with root
    explicit BinarySearchTree<ItemType>(const ItemType& rootItem) {
        BinaryNode<ItemType>* new_node = new BinaryNode<ItemType>;
        new_node->setItem(rootItem);
        rootPtr = new_node;
    }
    BinaryNode<ItemType>* copy_helper(BinaryNode<ItemType>* r) {
        if (r == nullptr) {
            return nullptr;
        }
        BinaryNode<ItemType>* dummy = new BinaryNode<ItemType>;
        dummy->setItem(r->getItem());
        dummy->setLeftChildPtr(copy_helper(r->getLeftChildPtr()));
        dummy->setRightChildPtr(copy_helper(r->getRightChildPtr()));
        return dummy;
    }
    // copy constructor
    BinarySearchTree<ItemType>(const BinarySearchTree<ItemType>& bst) {
        this->rootPtr = copy_helper(bst.rootPtr);
    }
    // destructor
    virtual ~BinarySearchTree<ItemType>() {
        clear();
    }
    // true if no nodes
    bool isEmpty() const {
        return (rootPtr == nullptr);
    }
    // 0 if empty, 1 if only root, otherwise
    // max height of subtrees + 1
    int getHeight() const {
        BinaryNode<ItemType>* temp = rootPtr;
        int height = findHeight(temp);
        if (height == 0) return 0;
        return height+1;// to account for root node being level one
    }
    int findHeight(BinaryNode<ItemType>* rootNode) const {
        if (rootNode == nullptr)
            return -1;
        else {
            // Find Height of left subtree and then right subtree
            // Return greater height value of left or right subtree (plus 1)
            int leftHeight = findHeight(rootNode->getLeftChildPtr());
            int rightHeight = findHeight(rootNode->getRightChildPtr());
            return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
        }
    }
    // number of nodes and data in tree
    int getNumberOfNodes() const {
        BinaryNode<ItemType>* temp = rootPtr;
        int counter = count_nodes_rec(temp);
        return counter;
    }
    int count_nodes_rec(BinaryNode<ItemType>* root) const
    {
        static int count = 0;
        if (root != NULL)
        {
            count_nodes_rec(root->getLeftChildPtr());
            count++;
            count_nodes_rec(root->getRightChildPtr());
        }
        return count;
    }
    // add a new item
    // return true if succesasfull
    // false if item already in tree or some other reason to fail
    bool add(const ItemType& item) {
        BinaryNode<ItemType>* new_node = new BinaryNode<ItemType>;
        new_node->setItem(item);
        new_node->setLeftChildPtr(nullptr);
        new_node->setRightChildPtr(nullptr);
        rootPtr = placeNode(rootPtr, new_node);
        return !(rootPtr == nullptr);
    }
    // true if item is in tree
    bool contains(const ItemType& item) const {
        BinaryNode<ItemType>* temp = rootPtr;
        BinaryNode<ItemType>* n_to_find = findNode(temp, item);
        return n_to_find == nullptr ? 0 : 1;
    }
    // dispaly a sideways ascii representation of tree
    void displaySideways() const {
        sideways(rootPtr, 0);
    }
    // inorder traversal: left-root-right
    // takes a function that takes a single parameter of ItemType
    // the function can modify the data in tree, but the
    // tree structure is not changed
    void inorderTraverse(void visit(ItemType&)) const {
        BinaryNode<ItemType>* temp = rootPtr;
        inorder_recur(temp);
    }
    void inorder_recur(BinaryNode<ItemType>* r) const{
        if (r == nullptr) return;
        inorder_recur(r->getLeftChildPtr());
        visit(r->getItem());
        inorder_recur(r->getRightChildPtr());
    }
    void visit(ItemType x) const {
        cout << x;
    }
    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree
    void rebalance() {
        vector<ItemType> n;
        store_to_array(rootPtr, n);
        rootPtr = read_helper(n,0,n.size()-1);
    }
    void store_to_array(BinaryNode<ItemType>* r, vector<ItemType>& v) {//using vector accepted by professor
        if (r == nullptr) return;
        store_to_array(r->getLeftChildPtr(), v);
        v.push_back(r->getItem());
        store_to_array(r->getRightChildPtr(), v);
    }
    //READ HELPER FOR BOTH ARRAY AND VECTOR ARE CORRECT, EXCEPT IN EXAMPLE
    // RIGHT NUMBER IS TAKEN WHEN CHOOSING MIDDLE FOR EVEN NUMBERS, MINE TAKES LEFT
    //ACCEPTED BY PROFESSOR
    BinaryNode<ItemType>* read_helper(vector<ItemType>& v, int start, int end)
    {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;//binary search algorithm to find the middle in each subarray
        BinaryNode<ItemType>* temp = new_create(v[mid]);
        temp->setLeftChildPtr(read_helper(v, start, mid - 1));
        temp->setRightChildPtr(read_helper(v, mid + 1, end));
        return temp;
    }
    // delete all nodes in tree and set root to nullptr
    void clear() {
        clear_helper(rootPtr);
        rootPtr = nullptr;
    }
    void clear_helper(BinaryNode<ItemType>* root) {
        if (root == nullptr) return;
        clear_helper(root->getLeftChildPtr());
        clear_helper(root->getRightChildPtr());
        delete root;
    }
    // given an array of length n
    // create this tree to have all items in that array
    // with the minimum height
    bool readTree(ItemType arr[], int n) {
        rootPtr = read_helper(arr, 0, n-1);
        return !(rootPtr == nullptr);
    }
    BinaryNode<ItemType>* new_create(ItemType& item) {
        BinaryNode<ItemType>* new_node = new BinaryNode<ItemType>;
        new_node->setItem(item);
        new_node->setLeftChildPtr(nullptr);
        new_node->setRightChildPtr(nullptr);
        return new_node;
    }
    BinaryNode<ItemType>* read_helper(ItemType arr[], int start, int end)
    {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;//binary search algorithm to find the middle in each subarray
        BinaryNode<ItemType>* temp = new_create(arr[mid]);
        temp->setLeftChildPtr(read_helper(arr, start, mid - 1));
        temp->setRightChildPtr(read_helper(arr, mid + 1, end));
        return temp;
    }
    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BinarySearchTree<ItemType>& other) const {
        return equal_rec(rootPtr, other.rootPtr);
    }
    bool equal_rec(BinaryNode<ItemType>* n_1, BinaryNode<ItemType>* n_2) const {
        if (n_1 == nullptr && n_2 == nullptr) {
            return true;
        }
        else if (n_1 == nullptr || n_2 == nullptr) {
            return false;
        }
        else {
            if (n_1->getItem() == n_2->getItem() && equal_rec(n_1->getLeftChildPtr(), n_2->getLeftChildPtr()) && equal_rec(n_1->getRightChildPtr(), n_2->getRightChildPtr())) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    // not == to each other
    bool operator!=(const BinarySearchTree<ItemType>& other) const {
        return !(*this == other);
    }
    //performance function implemented in case 9, better space complexity
    //than recursive search
    bool iterative_search(const ItemType& item) const {
        BinaryNode<ItemType>* temp = rootPtr;
        bool ans = i_helper(temp, item);
        return ans;
    }
    bool i_helper(BinaryNode<ItemType>* r, const ItemType& target) const {
        while (r != nullptr) {
            if (target > r->getItem()) {
                r = r->getRightChildPtr();
            }
            else if (target < r->getItem()) {
                r = r->getLeftChildPtr();
            }
            else {
                cout << "Item found";
                return true;
            }
        }
        return false;
    }
private:
    // root of the tree
    BinaryNode<ItemType>* rootPtr{ nullptr };
    // add a new node, helper function for add
    BinaryNode<ItemType>* placeNode(BinaryNode<ItemType>* subTreePtr,
        BinaryNode<ItemType>* newNodePtr) {
        if (subTreePtr == nullptr) {
            subTreePtr = newNodePtr;
            return subTreePtr;
        }
        else if (newNodePtr->getItem() < subTreePtr->getItem()) {
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
        }
        else if (newNodePtr->getItem() > subTreePtr->getItem()) {
            subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));
        }
        else {
            cout << "duplicate val" << endl;
            return subTreePtr;
        }
        return subTreePtr;
    }
    // find the node with given vale, helper function for contains
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* subTreePtr, const
        ItemType& target) const {
        if (subTreePtr == nullptr) {
            return nullptr;
        }
        if (target < subTreePtr->getItem()) {
            return findNode(subTreePtr->getLeftChildPtr(), target);
        }
        else if (target > subTreePtr->getItem()) {
            return findNode(subTreePtr->getRightChildPtr(), target);
        }
        else {
            return subTreePtr;
        }
    }
    // helper function for displaySideways to work recursively
    void sideways(BinaryNode<ItemType>* current, int level) const {
        if (current != NULL) {
            level++;
            sideways(current->getRightChildPtr(), level);
            // indent for readability, 4 spaces per depth level
            for (int i = level; i >= 0; i--) {
                cout << "    ";
            }
            cout << current->getItem() << endl;        // display information of object
            sideways(current->getLeftChildPtr(), level);
        }
    }
};

#endif // BINARYSEARCHTREE_H
