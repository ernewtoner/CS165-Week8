/*********************************************************************
 ** Author: Eric Newton
 ** Date: 11/16/2017
 ** Description: Implementation of sets using a template class.
 *********************************************************************/
#ifndef VALSET_HPP
#define VALSET_HPP

#include <vector>

using std::vector;

template <class T>

class ValSet
{
private:
  T* ptrToArray; // Points to a dynamically allocated array of T that holds the values that are part of the set
  int arraySize; // Needs to be updated whenever add() is called
  int numValues; // Holds the number of values that are currently part of the set - needs to be updated in the add() and remove() methods
public:
  ValSet(); 
  ValSet(const ValSet &obj); 
  ~ValSet();
  
  int size(); // Return the number of values currently in the ValSet
  bool isEmpty(); // Returns true if the ValSet contains no values, false otherwise
  bool contains(T) const; // Returns true if the ValSet contains value T, false otherwise
  void add(T);
  void remove(T);
  vector<T> getAsVector();
  
  ValSet<T>& operator=(const ValSet<T> &right);
  ValSet<T> operator+(const ValSet<T> &right);
  ValSet<T> operator*(const ValSet &right);
  ValSet<T> operator/(const ValSet &right);
};

// Default constructor
// Initalizes ptrToArray to an array of size 10, arraySize to 10, and numValues to 0
template <class T>
ValSet<T>::ValSet()
{ 
  ptrToArray = new T[10];
  arraySize = 10;
  numValues = 0;
}

// Copy constructor that initializes ptrToArray, arraySize, and numValues to the values of the inputted obj
template <class T>
ValSet<T>::ValSet(const ValSet &obj)
{
  // Initalizes ptrToArray to the same array size as obj
  ptrToArray = new T[obj.arraySize];

  // Copies over obj's array values
  for (int i=0; i < obj.numValues; i++)
    ptrToArray[i] = obj.ptrToArray[i];

  // Also copies obj's arraySize and numValues variables
  arraySize = obj.arraySize;
  numValues = obj.numValues;
}

// Destructor that deallocates the dynamically allocated array
template <class T>
ValSet<T>::~ValSet()
{
  delete [] ptrToArray;
  ptrToArray = nullptr;
}

// an overloaded assignment operator that initializes the pointer data member to point to an array of the same size as the one being copied, copies over the array values, copies the values for the size of the array and the number of values in the set, and returns a reference to the object pointed to by the this pointer
template <class T>
ValSet<T>& ValSet<T>::operator=(const ValSet &right)
{
  // Initalizes ptrToArray to the same array size as obj
  ptrToArray = new T[right.arraySize];

  // Copies over right's array values
  for (int i=0; i < right.numValues; i++)
    ptrToArray[i] = right.ptrToArray[i];

  // Also copies right's arraySize and numValues variables
  arraySize = right.arraySize;
  numValues = right.numValues;

  return *this;
}

// an overloaded + operator that returns a new ValSet that is the union of its two operands (contains all and only those values that were in either ValSet)
template <class T>
ValSet<T> ValSet<T>::operator+(const ValSet &right)
{
  ValSet<T> newValSet;

  // Iterate through this object's array and add its elments to newValSet
  for (int i=0; i < numValues; i++)
    newValSet.add(ptrToArray[i]);

  // Iterate through the right object's array and add its elements to newValSet
  // add() will automatically not add duplicates
  for (int i=0; i < right.numValues; i++)
    newValSet.add(right.ptrToArray[i]);

  return newValSet;
}

// an overloaded * operator that returns a new ValSet that is the intersection of its two operands (contains all and only those values that were in both ValSets)
template <class T>
ValSet<T> ValSet<T>::operator*(const ValSet &right)
{
  ValSet<T> newValSet;

  // Iterate through this object's array
  for (int i=0; i < numValues; i++) {
    // If the right object also contains this value
    if (right.contains(ptrToArray[i]))
      // Then add it to newValSet
      newValSet.add(ptrToArray[i]);
  }

  return newValSet;
}

// an overloaded / operator that returns a new ValSet that is the symmetric difference of its two operands (contains all and only those values that were in one ValSet or the other, but not both)
template <class T>
ValSet<T> ValSet<T>::operator/(const ValSet &right)
{
  ValSet<T> newValSet;
  
  // Iterate through this object's array
  for (int i=0; i < numValues; i++) {
    // If the right object also contains this value
    if (right.contains(ptrToArray[i]))
      // Then don't add it to newValSet
      continue;
    else
      // Otherwise add it to newValSet
      newValSet.add(ptrToArray[i]);
  }

  // Iterate through the right object's array
  for (int i=0; i < right.numValues; i++) {
    // If this object also contains right's value
    if (contains(right.ptrToArray[i]))
      // Then don't add it to newValSet
      continue;
    else
      // Otherwise add it to newValSet
      newValSet.add(right.ptrToArray[i]);
  }

  return newValSet;
}

// Return the number of values currently in the ValSet
template <class T>
int ValSet<T>::size()
{
  return numValues;
}

// Returns true if the ValSet contains no values, false otherwise
template <class T>
bool ValSet<T>::isEmpty()
{
  if (numValues == 0)
    return true;
  else
    return false;
}

// Returns true if the ValSet contains T value val, false otherwise
template <class T>
bool ValSet<T>::contains(T valToFind) const
{
  for (int i = 0; i < numValues; i++) {
    if (ptrToArray[i] == valToFind)
      return true;
  }
  
  return false;
}

// the add() method should take a parameter of type T and add that value to the ValSet (if that value is not already in the ValSet) - if the array is currently full, size is doubled and then the value is added
template <class T>
void ValSet<T>::add(T val)
{
  // If the ValSet doesn't already contain val
  if(contains(val) == false)
    {
    ////// Then if the array is full, first double the size of the array
    if (arraySize == numValues) {
      // Copy over the old array to tmpArray
      T* tmpArray = new T[arraySize];
      for (int i=0; i < numValues; i++)
	tmpArray[i] = ptrToArray[i];

      // Delete old array
      delete [] ptrToArray;
      ptrToArray = nullptr;

      // Create a new ptrToArray with arraySize * 2, then copy over the old array's contents
      ptrToArray = new T[(arraySize*2)];
      for (int i=0; i < numValues; i++)
	ptrToArray[i] = tmpArray[i];

      // Delete temp array
      delete [] tmpArray;
      tmpArray = nullptr;

      // Set arraySize to double its previous value
      arraySize *= 2;
    }
    //////
      
    // Then add the value, numValues will be the correct index after the last value in the array
    ptrToArray[numValues] = val;

    // Increment numValues by one
    numValues++;
  } 
}

// the remove() method should take a parameter of type T and remove it from the ValSet (if that value is in the ValSet) by shifting over all of the subsequent elements of the array
template <class T>
void ValSet<T>::remove(T val)
{
  // The index the value we want to remove is at
  int index;
  
  // If the ValSet contains the inputted value
  if (contains(val)) {
    // Find the index in the array of that value
    for (int i =0; i < numValues; i++) {
      if(ptrToArray[i] == val)
	index = i;
    }

    // Move over subsequent elements to one place before their current index
    for (int i = index; i < (numValues-1); i++)
      ptrToArray[i] = ptrToArray[(i+1)];

    // Decrement numValues by one since we've removed an element
    numValues--;
  }
}

// the getAsVector method should return a vector (of type T) that contains all of the values in the ValSet and only those values.  Order doesn't matter.
template <class T>
vector<T> ValSet<T>::getAsVector()
{
  vector<T> vect;
  
  for (int i =0; i < numValues; i++)
    vect.push_back(ptrToArray[i]);

  return vect;
}

#endif
