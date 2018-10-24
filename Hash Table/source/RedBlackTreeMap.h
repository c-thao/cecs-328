#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

template<typename TKey, typename TValue>
class RedBlackTreeMap {
private:
   class Node {
   public:
      TKey mKey;
      TValue mValue;
      // A weak_ptr does not contribute to a shared_ptr's reference count.
      // This avoids having circular references.
      std::weak_ptr<typename Node> mParent;
      std::shared_ptr<Node> mLeft;
      std::shared_ptr<Node> mRight;
      bool mIsRed;

      Node(const TKey &key, const TValue &value, bool isRed) 
         : mKey(key), mValue(value), mIsRed(isRed), mParent(), 
           mLeft(NIL_NODE), mRight(NIL_NODE) {
      }

   };

   std::shared_ptr<Node> mRoot;
   int mCount;
   static std::shared_ptr<Node> NIL_NODE;

   Node* bstFind(const TKey &key, Node *currentNode) {
      // TODO: write this method. Given a key to find and a node to start at,
      // proceed left/right from the current node until finding a node whose 
      // key is equal to the given key.
      // Hint: from a std::shared_ptr<Node> value, you can get a raw Node* using the 
      // .get() function, as in:
      // Node *temp = currentNode->mLeft.get();
      // Use < and > to compare the keys of nodes to determine left/right.
	   if (currentNode != nullptr) {
		   if (currentNode->mKey == key) {
			   return currentNode;
		   }
		   if (currentNode->mKey > key) {
			   if (currentNode->mLeft != nullptr) {
				   return bstFind(key, currentNode->mLeft.get());
			   }
		   }
		   if (currentNode->mRight != nullptr) {
			   return bstFind(key, currentNode->mRight.get());
		   }
		   
	   }
      return nullptr;
   }

   std::shared_ptr<Node> getGrandparent(Node *n) {
      // TODO: return the grandparent of n
	   if (n != nullptr) {
		   if (n->mParent.lock().get() != nullptr) {
			   if (n->mParent.lock()->mParent.lock().get() !=nullptr) {
				   return n->mParent.lock()->mParent.lock();
			   }
		   }
	   }
      return nullptr;
   }

   // Gets the uncle (parent's sibling) of n.
   std::shared_ptr<Node> getUncle(Node *n) {
	  std::shared_ptr<Node> g = getGrandparent(n);
      // TODO: return the uncle of n
	   if (n != nullptr) {
		   if (n->mParent.lock().get() != nullptr) {
			   if (g != nullptr) {
				   if (n->mParent.lock()->mKey > g->mKey) {
					   if (g->mLeft.get() != nullptr) {
						   return g->mLeft;
					   }
				   }
				   else if (g->mRight.get() != nullptr) {
					   return g->mRight;
				   }
			   }
		   }
	   }
      return nullptr;
   }

   // Rotate the tree right at the given node.
   void rotateRight(std::shared_ptr<Node> n) {
	   std::shared_ptr<Node> r = n->mRight, p = n->mParent.lock(),
		   g = getGrandparent(n.get());

	  p->mLeft = r;   // parent's left updated to n's right
	  r->mParent = p; // n's right's parent is updated
	  n->mRight = p;  // n's right linked to parent

	  if (p == mRoot) {        // check if parent is root
		  mRoot = n;           // make n root
		  n->mIsRed;           // n is black
		  n->mParent.reset();  // remove any of n's parent
	  }
	  else if (g != nullptr) { // check if n's grandparent is valid
		  if (p->mKey > g->mKey) {
			  g->mRight = n;   // set n to grandparent's right
		  }
		  else {
			  g->mLeft = n;    // set n to grandparent's left
		  }
		  //g->mIsRed = !g->mIsRed; // changes grandparent's color
		  n->mParent = g;         // n's parent linked to grandparent
	  }
	  p->mParent = n;   // parent's parent linked to n
      
   }

   // Rotate the tree left at the given node.
   void rotateLeft(std::shared_ptr<Node> n) {
      // TODO: do a single left rotation (AVL tree calls this a "rr" rotation)
      // at n.
	   std::shared_ptr<Node> l = n->mLeft, p = n->mParent.lock(),
		   g = getGrandparent(n.get());

      p->mRight = l;  // parent's right get n's left
	  l->mParent = p; // n's left's parent is updated
	  n->mLeft = p;   // n's left is linked to parent

      if (p == mRoot) {       // check if parent is root
         mRoot = n;           // make n the root
		 n->mIsRed = false;   // n is black
		 n->mParent.reset();  // remove n of any parent
      }
	  else if (g != nullptr){ // check if n's grandparent is valid
		  if (p->mKey > g->mKey) {
			  g->mRight = n;  // make n right child of grandparent
		  }
		  else {
			  g->mLeft = n;  // make n left child of grandparent
		  }
		  //g->mIsRed = !g->mIsRed; // changes grandparent's color
		  n->mParent = g;         // n's parent is linked to the grandparent
	  }
	  p->mParent = n;          // update parent's parent to n
   }


   // This method is used by insert. It is complete.
   // Inserts the key/value into the BST, and returns true if the key wasn't 
   // previously in the tree.
   bool bstInsert(std::shared_ptr<Node> newNode, std::shared_ptr<Node> currentNode) {
      if (mRoot == nullptr) {
         // case 1
         mRoot = newNode;
         return true;
      }
      else {
         if (currentNode->mKey < newNode->mKey) {
            // newNode is larger; go right.
            if (currentNode->mRight != NIL_NODE)
               return bstInsert(newNode, currentNode->mRight);
            else {
               currentNode->mRight = newNode;
               newNode->mParent = currentNode;
               mCount++;
               return true;
            }
         }
         else if (currentNode->mKey > newNode->mKey) {
            if (currentNode->mLeft != NIL_NODE)
               return bstInsert(newNode, currentNode->mLeft);
            else {
               currentNode->mLeft = newNode;
               newNode->mParent = currentNode;
               mCount++;
               return true;
            }
         }
         else {
            // found a node with the given key; update value.
            currentNode->mValue = newNode->mValue;
            return false; // did NOT insert a new node.
         }
      }
   }

   // Applies rules 1-5 to check the balance of a tree with newly inserted
   // node n.  
   void checkBalance(std::shared_ptr<Node> n) {
	   std::shared_ptr<Node> unc = getUncle(n.get()),
		   gp = getGrandparent(n.get()),
		   p = n->mParent.lock();
      if (n == mRoot) {
         // case 1: n is the root
		  //cout << "\nroot is not black";
         n->mIsRed = false;
      }
	  else if (p->mIsRed == true && unc != nullptr) {
		// case 3: P and U are red
		if (unc->mIsRed == true) {
			//cout << "\nP and U are red";
			p->mIsRed = false;
			unc->mIsRed = false;
			gp->mIsRed = true;
			checkBalance(gp);
		 }
		 else if (gp != nullptr) {
			 // case 4: n is the lr or rl grandchild of G
			 if (gp->mLeft->mRight == n) {
				 //printStructure();  // before left
				 rotateLeft(n);
				 //cout << "\n";
				 //printStructure();  // after left
				 n->mIsRed = !n->mIsRed;  // changes n's color
				 gp->mIsRed = !gp->mIsRed;  // changes gp's color
				 rotateRight(n);
				 //cout << "\n";
				 //printStructure();
			 }
			 else if (gp->mRight->mLeft == n) {
				 //printStructure();  // before right
				 rotateRight(n);
				 //cout << "\n";
				 //printStructure();        // after right
				 n->mIsRed = !n->mIsRed;    // changes n's color
				 gp->mIsRed = !gp->mIsRed;  // changes gp's color
				 rotateLeft(n);
				 //cout << "\n";
				 //printStructure();
			 }
			 // case 5: n is the ll or rr grandchild of G
			 else if (gp->mRight->mRight == n) {
				 gp->mIsRed = !gp->mIsRed;  // changes g's color
				 p->mIsRed = !p->mIsRed;   // changes p's color
				 rotateLeft(p);
			 }
			 else {
				 gp->mIsRed = !gp->mIsRed;  // changes g's color
				 p->mIsRed = !p->mIsRed;   // changes p's color
				 rotateRight(p);
			 }
		 }
	  }
      // handle additional insert cases here.
      // Note that each case is mutually exclusive, EXCEPT THAT case 4 must flow
      // into case 5.
      // Also note that case 3 recursively examines the grandparent after the
      // recoloring.
   }


public:

   inline int count() const {
      return mCount;
   }

   // Inserts a key/value pair into the tree, updating the red/black balance
   // of nodes as necessary. Starts with a normal BST insert, then adjusts.
   void insert(const TKey &key, const TValue &value) {
      std::shared_ptr<Node> n = std::make_shared<Node>(key, value, true); 
      // the node starts red, with null parent, left, and right.

      // normal BST insert; n will be placed into its initial position.
      // returns false if an existing node was updated (no rebalancing needed)
      bool insertedNew = bstInsert(n, mRoot);
	  if (n->mParent.lock().get() != nullptr) {
		  //cout << "\nparent is " << n->mParent.lock()->mKey;
	  }
	  if (!insertedNew)
         return;
	  //if (mRoot != nullptr) {
		//  printStructure();
	  //}
	  // check cases 1-5 for balance.
      checkBalance(n);
   }

   TValue find(const TKey &key) {
      Node* n = bstFind(key, mRoot.get());
      if (n == nullptr || (n == NIL_NODE.get())) {
         throw std::out_of_range("Key not found");
      }
      return n->mValue;
   }

   // Returns true if the given key is in the tree.
   bool containsKey(const TKey &key) const {
      // TODO: using at most three lines of code, finish this method.
      // HINT: write the bstFind method first.
	   if (bstFind(key, mRoot) != nullptr) {
		   return true;
	   }
      return false;
   }


   // Prints a pre-order traversal of the tree's nodes, printing the key, value,
   // and color of each node.
   void printStructure() {
      // TODO: a pre-order traversal. Will need recursion.
	   print(mRoot);
   }

   void print(std::shared_ptr<Node> n) {
	   if (n != NIL_NODE) {
		   cout << "\n" << n->mKey << " : " << n->mValue;
		   /*if (n->mParent.lock() != nullptr) {
			   std::cout << " parent " << n->mParent.lock()->mKey;
		   }
		   else {
			   std::cout << " no parent";
		   }*/
		   (n->mIsRed) ? cout << "(Red)" : cout << "(Black)";
		   print(n->mLeft);
		   print(n->mRight);
	   }
   }


};

template<typename TK, typename TV>  
std::shared_ptr<typename RedBlackTreeMap<TK, TV>::Node> RedBlackTreeMap<TK, TV>::NIL_NODE =
   std::make_shared<typename RedBlackTreeMap<TK, TV>::Node>(TK(), TV(), false);