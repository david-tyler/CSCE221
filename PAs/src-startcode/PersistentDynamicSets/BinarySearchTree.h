#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream>    
#include <vector>
#include <stack>
using namespace std;


template <typename Comparable>
class BinarySearchTree
{
private:  // this private BinaryNode is within BST
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        bool status;     // status = 0 if the node belongs to the tree with root r1 (it can also be in the tree with root r2); 
        //status = 1 means that the node only belongs to the tree with root r2

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt , bool st)
            : element( theElement ), left( lt ), right( rt ), status( st ) 
        { 
        }
    };

    BinaryNode *r1;    //r1 is the root of the BST for the persistent dynamic set
    BinaryNode *r2;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * if st=0, insert an element from the persistent dynamic set; st=1,otherwise
     */
    void insert( const Comparable & x, BinaryNode * & t, bool st)
    {
      // impplement here
      if(t == nullptr)
      {
        t = new BinaryNode(x, nullptr, nullptr, st);
      }
      else
      {
        if(t->status == 0 && st == 1)
        {
          t = new BinaryNode(t->element, t->left, t->right, st);
        }
        if(x< t->element)
        {
          insert(x, t->left, st);
        }
        else if(x > t->element)
        {
          insert(x, t->right, st);
        }
        else
        {
          return;
        }
      }
      
    }


    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * this function is only for the elements not in the persistent dynamic set
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
      //implement here
      if(t == nullptr)
      {
        return;
      }
      if(x < t->element)// recurse until we get into the correct subtree
      {
        remove(x, t->left);
      }
      else if(x > t->element)
      {
        remove(x, t->right);
      }
      else
      {
        if(t->status == 1 && t->element == x)
        {
          BinaryNode* temp = nullptr;
          if(t->left == nullptr && t->right == nullptr) //no child
          {
            temp = nullptr;
            return;
          }
          else if(t->right != nullptr && t->left == nullptr && t->right->status == 1) //only right child exists
          {
            temp = t->right;
          }
          else if(t->left != nullptr && t->right == nullptr && t->left->status == 1)//only left child exists
          {
            temp = t->left;
          }
          else if (t->left != nullptr && t->right != nullptr) //both children exist
          {
            
            temp = search(findMin(t), t);
            t->element = temp->element;
            remove(temp->element, t->right);

          }
          if(temp != nullptr)
          {
            while(temp->right != nullptr && temp->status == 1)
            {
              temp = temp->right;
            }
          }
          delete t;
          t = temp;
          
        }
      }
      
    }



    /**
     * Internal method to make subtree empty.
     * if st = 1, 't' is a node in the tree with root r2; otherwise, 
     * 't' is a node in the tree with root r1 
     * think about how to deal with 't' if 't' is a common node of the two
     * trees
     */
    void makeEmpty( BinaryNode * & t, bool st )
    {
      //implement here
      if(t == nullptr)
      {
        return;
      }
      
      makeEmpty(t->left, st); //traverse down the right subtree
      makeEmpty(t->right, st); //traverse down the left subtree
      if(t->status == st)//if the statuses match when called simply delete
      {
        delete t;
        t = nullptr;
      }
    }

    /**
     * Internal method to clone subtree.
     * if st = 1, t is a node in the BST with root r1;
     * if st = 0, otherwise
     */
    BinaryNode * clone( BinaryNode *t, bool st ) const
    {
      //implement here
      if(t == nullptr)
      {
        return nullptr;
      }
      BinaryNode* temp = new BinaryNode(t->element,nullptr,nullptr,st);
      if(st == 0)
      {
        temp->right = clone(t->right, st);
        temp->left = clone(t->left, st);
      }
      else if(st ==1)
      {
        if(t->left != nullptr)
        {
          if(contains(t->left->element,r1) && t->left->status == 0)
          {
            temp->left = search(t->left->element,r1);
          }
          else
          {
            temp->left = clone(t->left,st);
          }
        }
        if(t->right != nullptr)
        {
          if(contains(t->right->element,r1) && t->right->status == 0)
          {
            temp->right = search(t->right->element,r1);
          }
          else
          {
            temp->right = clone(t->right,st);
          }
        }
        return temp;
      }
      return temp;
    }
public:
    BinarySearchTree( ) :r1( NULL ), r2( NULL )
    {
    }

    BinarySearchTree( const BinarySearchTree & rhs ) 
    {
        *this = rhs;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( BinaryNode * t ) const
    {
      //implement here
      if(t == nullptr)
      {
        throw UnderflowException();
        
      }
      else
      {
        BinaryNode* temp = t;
        while(temp->left != nullptr) //traverse down to the leftmost node and return its valuse
        {
          temp = temp->left;
        }
        return temp->element;
      }
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( BinaryNode *t ) const
    {
      //implement here
      if(t == nullptr)
      {
        throw UnderflowException();
        
      }
      else
      {
        BinaryNode* temp = t;
        while(temp->right != nullptr) //traverse down to the rightmost node and return its valuse
        {
          temp = temp->right;
        }
        return temp->element;
      }
    }

    /**
     * Returns true if x is found in the subtree with root t.
     */
	 bool contains( const Comparable & x, BinaryNode *t ) const 
   { 
     //implement here
     if(t == nullptr)//if element was not found return false
     {
      return false;
     }
     if(t->element == x)
     {
      return true;
     }
     if(x < t->element)
     {
      return contains(x, t->left);//traverse left subtree if x is greater than t's element
     }
     else if(x > t->element)
     {
      return contains(x, t->right);//traverse right subtree if x is less than t's element
     }
     return false;
   }

  /**
   * returns the node with element = x in the subtree with root t
   * to make sure that x is always here, call contains(x, t) first
   */

  BinaryNode * search( const Comparable & x, BinaryNode *t ) const
  {
    //implement here
    if(t == nullptr)
    {
      return nullptr;
    }
    if(t->element == x)
    {
      return t;
    }
    else if(contains(x, t))
    {
      if(x> t->element)
      {
       return search(x, t->right);
      }
      else if(x<  t->element)
      {
       return search(x, t->left);
      }
      
    }
    return nullptr;
  } 


    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return r1 == NULL;
    }

    /**
     * Make the tree logically empty.
     * remove all items
     * pay attention to the common nodes in r1 and r2
     */
    void makeEmpty( )
    {
        makeEmpty( r2, 1 );
        makeEmpty( r1, 0);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     * if st =0, insert into the tree with root r1; if st=1, insert into the
     * tree with root r2
     */
    void insert ( const Comparable & x, bool st)
    {
      //implement here
      if(st == 0)
      {
        insert(x, r1, st);
      }
      else if(st == 1)
      {
        if(r2 == nullptr)
        {
          r2 = new BinaryNode(r1->element, r1->left, r1->right, st);//copy persistent dynamic set's root
        }
        insert(x, r2, st);
      }

    } 

    /**
     * Remove x from the tree with root r2. Nothing is done if x is not found
     * or if x is from the persistent dynamic set.
     */
    void remove( const Comparable & x )
    {
      //implement here
      remove(x, r2);
    }

    /**
     * Deep copy.
     * notice the common nodes in both trees
     */

    const BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            r1 = clone( rhs.r1, 0 );
            r2 = clone( rhs.r2, 1);
        }
        return *this;
    }

    /* in-order tree walk and the result is stored in v
     * the root is r
     */

   void inOrder ( vector <BinaryNode*> &v , BinaryNode * r)
   {
     //implement here
     if(r != nullptr)
     {
      inOrder(v, r->left);
      v.push_back(r);
      inOrder(v, r->right);
     }
   }


  /* this function is to test
   * please do not change
   */
  void printTree( )     // Print tree in sorted order
  {
    vector <BinaryNode*> v1, v2;

    inOrder (v1, r1);   //inorder traverse
    inOrder (v2, r2);  //inorder traverse

   cout << "print BST for persistent dynamic set   " << endl;

   int i, j;
   for ( i = 0; i < v1.size(); i++)
   {
     cout <<  v1.at (i) -> element << "  ";
   }
   cout << endl;


  cout << "print BST for the whole input set   " << endl;

  for ( i = 0; i < v2.size(); i++)
  {
      cout << v2.at (i) -> element << "  ";
  }
  cout << endl;
 
  i=0; j=0;

  // output the common nodes with the same address in both trees
  // a common node in both trees must have the same address 
  cout << "Common nodes: ";
  while ( i < v1.size() )
  {
    if ( v1.at(i) -> element == v2.at(j) -> element )
    {
      if ( v1.at(i) == v2.at(j) )   // if the address are equal
      {
       cout << v1.at(i) -> element << "  "; 
      }

       i++; j++;
    }
    else if ( v2.at(j) -> element < v1.at(i) -> element )
      j++;
  }
  cout << endl;
  
 }

};


#endif
