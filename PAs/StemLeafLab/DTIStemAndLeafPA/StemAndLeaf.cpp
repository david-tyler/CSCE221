#include <iostream>
#include "StemAndLeaf.h"
using namespace std;

int StemAndLeaf::getLeafUnit() const { 
  return this->leafUnit;
}


void StemAndLeaf::setLeafUnit(int leafUnit) {
  this->leafUnit = leafUnit;
}

int StemAndLeaf::getStemUnit() const { 
  return this->stemUnit;
}

void StemAndLeaf::setStemUnit(int stemUnit) {
  this->stemUnit = stemUnit;

} 

StemAndLeaf::StemAndLeaf() {
  leafUnit = 0;
  stemUnit = 0;
  head = nullptr;
  tail = nullptr;
}

StemAndLeaf::~StemAndLeaf() {
  leafUnit = 0;
  stemUnit = 0;
  Stem* current = head;
  while(current != nullptr)
  {
    Stem* temp = current->next;
    delete current;
    current = temp;
  }
  

}

void StemAndLeaf::addTerm(int term) {
  int tens = term / stemUnit;//stem value
  int ones = term % stemUnit;//leaf value
  bool added = false;
  

  Stem* temp = head;
  Stem* prev = head;
  
  if(temp == nullptr)
  {
    Stem* newTerm = new Stem();
    newTerm->value = tens;
    newTerm->insert(ones);

    head = newTerm;
    tail = newTerm;
    head->next = nullptr;
    added = true;
  }
  else
  {
    while(temp != nullptr)
    {
      if(temp->value == tens)
      {
        temp->insert(ones);
        added = true;
        break;
      }
      else if(tens < temp->value)//make stem and insert leaf then just break, we are inserting before
      {
        if(temp == head)
        {
          Stem* newTerm = new Stem();
          newTerm->value = tens;
          newTerm->insert(ones);
          
          newTerm->next = head;
          head = newTerm;
          added = true;
          break;
        }
        else
        {
          Stem* newTerm = new Stem();
          newTerm->value = tens;
          newTerm->insert(ones);

          prev->next = newTerm;
          newTerm->next = temp;
          added = true;
          break;
        }
      }

      if(temp == head)
      {
        temp = temp->next;
      }
      else
      {
        temp = temp->next;
        prev = prev->next;
      }
    }
  }
  if(added == false) //reached end no value is greater than
  {
    Stem* newTerm = new Stem();
    newTerm->value = tens;
    newTerm->insert(ones);
    added = true;
    prev->next = newTerm;
    newTerm->next = nullptr;
    tail = newTerm;
    
  }
}

bool StemAndLeaf::removeTerm(int term) {
  int tens = term / stemUnit;//stem value
  int ones = term % stemUnit;//leaf value

  Stem* temp = head;
  Stem* prev = head;
  while(temp != nullptr)
  {
    if(temp == head)
    {
      if(temp->value == tens)//stem found now remove leaf first before removing stem
      {
        temp->remove(ones);
        if(temp->frequency == 0)// if frequency is now zero after removing leaf just remove stem
        {
          head = head->next;
          return true;
        }
        return true;
      }
    }
    else
    {
      if(temp->value == tens)//stem found now remove leaf first before removing stem
      {
        temp->remove(ones);
        temp->frequency--;
        if(temp->frequency < 1)// if frequency is now zero after removing leaf just remove stem
        {
          prev->next = temp->next;
          return true;
        }
        return true;
      }
    }
    
    if(temp == head)
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
std::ostream &operator << (std::ostream &out, const StemAndLeaf &x) {
	// needs to go through the StemAndLeaf, one stem, then all leaves, then back to the next stem and it's leaves, and continue
    Stem * CURSTEM_ptr = x.head;
    while ( CURSTEM_ptr != nullptr )
    {
      out << *CURSTEM_ptr; 
      CURSTEM_ptr = CURSTEM_ptr -> next;
    }
    
	return out;
}

