#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <cstdlib>
#include <ctime>

/* Created by Yan Zhang A53050564, Chaoteng Liu A53055394*/

template <typename Data>
class RST : public BST<Data> {
    
public:    
    //derived method. Insert node to a treap
    virtual bool insert(const Data& item) {
        BSTNode<Data> *tmpNode = BST<Data>::findFatherIfNotExist(item);
        if (!tmpNode)
        {
            BST<Data>::root = new BSTNode<Data>(item);
            BST<Data>::root->priority = rand();     //set random priority to root
            BST<Data>::isize = 1;
            return true;
        }
        else
        {
            if (tmpNode->data == item)
            {
                return false;
            }
            else
            {
                BSTNode<Data> *newNode = new BSTNode<Data>(item);

                newNode->priority = rand();     //set random priority to leaf node
                newNode->parent = tmpNode;
                if (newNode->data < tmpNode->data)
                {
                    tmpNode->left = newNode;
                }
                else
                {
                    tmpNode->right = newNode;
                }
                BST<Data>::isize++;
                
                rotateNode(newNode);
                return true;
            }
        }
    }
private:
    //do the rotation according to the shape of the treap
    void rotateNode(BSTNode<Data> *node)
    {
        while (node->parent != 0 && node->priority > node->parent->priority) {
            BSTNode<Data> *parent = node->parent;
            if (parent->left == node) {
                rightRotate(parent);
            }
            else {
                leftRotate(parent);
            }
        }
    }
    
    //left rotate to maintain the treap
    void leftRotate(BSTNode<Data> *node)
    {
        BSTNode<Data> *child = node->right;
        BSTNode<Data> *parent = node->parent;
        
        //Be careful: Many nodes might be null
        if (parent == 0) {
            child->parent = 0;
            BST<Data>::root = child;
        }
        else {
            if (parent->left == node) {
                parent->left = child;
                child->parent = parent;
            }
            else {
                parent->right = child;
                child->parent = parent;
            }
        }
        
        node->right = child->left;
        if (child->left != 0) {
            child->left->parent = node;
        }
        
        node->parent = child;
        child->left = node;
    }
    
    //right rotate to maintain the treap
    void rightRotate(BSTNode<Data> *node)
    {
        BSTNode<Data> *child = node->left;
        BSTNode<Data> *parent = node->parent;
        
        //Be careful: Many nodes might be null
        if (parent == 0) {
            child->parent = 0;
            BST<Data>::root = child;
        }
        else {
            if (parent->left == node) {
                parent->left = child;
                child->parent = parent;
            }
            else {
                parent->right = child;
                child->parent = parent;
            }
        }
        
        node->left = child->right;
        if (child->right != 0) {
            child->right->parent = node;
        }
        
        node->parent = child;
        child->right = node;
    }
};
#endif // RST_HPP