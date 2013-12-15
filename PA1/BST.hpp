#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */
  virtual ~BST() {
      BST<Data>::deleteAll(root);
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */
  virtual bool insert(const Data& item) {
	  BSTNode<Data> *tmpNode = findFatherIfNotExist(item);
	  if (!tmpNode)
	  {
		  root = new BSTNode<Data>(item);
		  isize = 1;
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
			  newNode->parent = tmpNode;
			  if (newNode->data < tmpNode->data)
			  {
				  tmpNode->left = newNode;
			  }
			  else
			  {
				  tmpNode->right = newNode;
			  }
			  isize++;
			  return true;
		  }
	  }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */
  iterator find(const Data& item) const {
	  BSTNode<Data> *tmpNode = findFatherIfNotExist(item);
	  if (tmpNode && tmpNode->data == item)
	  {
		  return typename BST<Data>::iterator(tmpNode);
	  }
	  else
	  {
		  return typename BST<Data>::iterator(0);
	  }
  }

  
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
	  return isize;
  }

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
	  return isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */
  iterator begin() const {
	  return typename BST<Data>::iterator(BST<Data>::first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */
  void inorder(BSTNode<Data>* n) const {
    if(n==0) return;
    inorder(n->left);
    std::cout << *n << std::endl;
    inorder(n->right);
  }

  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  // do a postorder traversal, deleting nodes
  static void deleteAll(BSTNode<Data>* n) {
    if (0 == n) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }

  //do a search for item. Return a pointer pointing to the item if exists.
  //if not, return a BSTNode pointer pointing to the future father if the item is to be inserted.
  //if the BST is empty, return 0
  //this method is for not to call one more find() in the insert()
  BSTNode<Data>* findFatherIfNotExist(const Data& item) const{
	  BSTNode<Data> *tmpNode = root;
	  while (tmpNode)
	  {
		  if (tmpNode->data < item) {
			  if (tmpNode->right == 0)
			  {
				  break;
			  }
			  else
			  {
				  tmpNode = tmpNode->right;
			  }
		  }
		  else
		  {
			  if (tmpNode->data == item)
			  {
				  break;
			  }
			  else
			  {
				  if (tmpNode->left == 0)
				  {
					  break;
				  }
				  else
				  {
					  tmpNode = tmpNode->left;
				  }
			  }
		  }
	  }
	  return tmpNode;
  }


 };


#endif //BST_HPP
