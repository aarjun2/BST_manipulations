// BinaryNode to help with BinarySearchTree class
// Uses template so that ItemType can be any type
// getLeftChildPtr and setLeftChildPtr used to get/set child nodes
// getItem/setItem used to set the data stored in this node
// BinarySearchTree requires <, > relationships to be defined for ItemType
// << for  BinaryNode is defined to print the ItemType as [BN: item ]
// binarynode.cpp file is included at the bottom of the .h file
// binarynode.cpp is part of the template, cannot be compiled separately
#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <iostream>
template<class ItemType>
class BinaryNode {
    // operator<<
    // Has to be defined in .h and not in cpp since it is not in
    // BinaryNode<ItemType>:: class
    friend std::ostream& operator<<(std::ostream& out, const BinaryNode<ItemType>&
        bn) {
        out << "[BN: " << bn.item << "]";
        return out;
    }
public:
    // default constructor
    BinaryNode<ItemType>() {

    }
    // constructor setting the data to be stored
    explicit BinaryNode<ItemType>(const ItemType& item) {
    }
    // destructor to cleanup
    virtual ~BinaryNode<ItemType>() {
        // If suffering from memory leaks, uncomment next line
        // std::cout << "Deleting " << *this << std::endl;
    }
    // true if no children, both left and right child ptrs are nullptr
    bool isLeaf() const {
        return leftPtr == nullptr && rightPtr == nullptr;
    }
    // get left child, possibly nullptr
    BinaryNode<ItemType>* getLeftChildPtr() const {
        return leftPtr;
    }
    // set the left child ptr
    void setLeftChildPtr(BinaryNode<ItemType>* childPtr) {
        leftPtr = childPtr;
    }
    // get right child, possibly nullptr
    BinaryNode<ItemType>* getRightChildPtr() const {
        return rightPtr;
    }
    // set the right child ptr
    void setRightChildPtr(BinaryNode<ItemType>* childPtr) {
        rightPtr = childPtr;
    }
    // return the item stored
    ItemType getItem() const {
        return item;
    }
    // set the item stored to a new value
    void setItem(const ItemType& item) {
        this->item = item;
    }
private:
    // the data that will be stored
    ItemType item;
    // left child
    BinaryNode<ItemType>* leftPtr{ nullptr };
    // right child
    BinaryNode<ItemType>* rightPtr{ nullptr };
};

#endif // BINARYNODE_H
