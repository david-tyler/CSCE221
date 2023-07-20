#include <iostream>
#include "Leaf.h"
#include "Stem.h"
using namespace std;
Stem::Stem() {
  front = nullptr;
  back = nullptr;
  value = -1;
  frequency = 0;
  next = nullptr;
}

Stem::~Stem() {//fix
  Leaf* current = front;
  if(front != nullptr)
  {
    while(current != nullptr)
    {
      
      Leaf* temp = front->next;
      delete current;
      current = temp;
    }
    if(current != nullptr)
      delete current;
  }
  
  value = 0;
  frequency = 0;
}

bool Stem::insert(int value) {
  Leaf* temp = front;
  Leaf* prev = front;
  bool inserted = false;
  
  if(front == nullptr)
  {
    Leaf* newLeaf = new Leaf();
    newLeaf->count = 1;
    newLeaf->value = value;

    front = newLeaf;
    back = newLeaf;
    
    inserted = true;
    frequency++;
    
    return true;
  }
  while(temp != nullptr)
  {
    if(temp->value == value)
    {
      temp->count++;
      inserted = true;
      return true;
    }
    else if(value < temp->value)
    {
      if(temp == front)//if at front of list
      {
        Leaf* newLeaf = new Leaf();
        newLeaf->count = 1;
        newLeaf->value = value;

        newLeaf->next = temp;
        front = newLeaf;
        this->frequency++;
        inserted = true;

        
        return true;
      }
      else //not at the front
      {
        Leaf* newLeaf = new Leaf();
        newLeaf->count = 1;
        newLeaf->value = value;

        prev->next = newLeaf;
        newLeaf->next = temp;
        this->frequency++;
        inserted = true;
        
        return true;
      }
    }

    if(temp == front)
    {
      temp = temp->next;
    }
    else
    {
      temp = temp->next;
      prev = prev->next;
    }
    
  }
  //reached end of list but did not insert or smth
  if(inserted == false)
  {
    Leaf* newLeaf = new Leaf();
    newLeaf->count = 1;
    newLeaf->value = value;
    this->frequency++;

    prev->next = newLeaf;
    newLeaf->next = nullptr;
    back = newLeaf;
    
    inserted = true;
    return true;
  }

  
  return false;

  
}

// return true is a leaf is deleted 
bool Stem::remove(int target) {
  Leaf* temp = front;
  Leaf* prev = front;
  while(temp != nullptr)
  {
    if(temp->value == target)
    {
      if(temp == front)//if we have to remove the front
      {
        if(temp->count > 1)//if count is greater than 1 just decrease the count
        {
          temp->count--;
          return true;
        }
        else if(temp->count == 0)
        {
          this->frequency--;
          front = front->next;
          delete temp;
          return true;
        }
      }
      else
      {
        if(temp->count > 1)//if count is greater than 1 just decrease the count
        {
          temp->count--;
          return true;
        }
        else if(temp->count == 0)
        {
          this->frequency--;
          prev->next = temp->next;
          delete temp;
          return true;
        }
      }
    }

    if(temp == front)
    {
      temp = temp->next;
    }
    else
    {
      temp = temp->next;
      prev = prev->next;
    }


  }
  return false;
  
}

// Don't modify
std::ostream &operator << (std::ostream &out, const Stem &x) {
  out << x.value <<" | ";
  Leaf *CURLEAF_ptr = x.front;  

  while ( CURLEAF_ptr != nullptr )
  {
    out << *CURLEAF_ptr <<" ";
    CURLEAF_ptr = CURLEAF_ptr -> next;
  }
  out << std::endl;

  return out;
}

