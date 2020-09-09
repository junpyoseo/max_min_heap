// ============================================================================
// File: cmaxminheap.h
// ============================================================================
// Header file for the CMaxMinHeap class.
// ============================================================================
#ifndef CMAXMINHEAP_H
#define CMAXMINHEAP_H
#include    "clist.h"

// constants
const   int HEAP_MAX_ITEMS = MAX_ITEMS; // same value from "clist.h"
const   int MAX = 0; // Max Heap
const   int MIN = 1; // Min Heap

// enumerate list for CMaxMinHeapException class
enum    CMaxMinHeapExceptionType  { HEAP_FULL,
                                    HEAP_EMPTY,
                                    HEAP_ERROR
                                  };


// exception class for CMaxMinHeap
class CMaxMinHeapException
{
public:
    // constructor
    CMaxMinHeapException(CMaxMinHeapExceptionType   exceptType)
            : m_exceptType(exceptType) {}

    // member function
    CMaxMinHeapException GetException() const {return m_exceptType;}

private:
    CMaxMinHeapExceptionType  m_exceptType;
};

// class declaration
template <class HeapItemType>
class   CMaxMinHeap : private CList<HeapItemType>
{
public:
    // constructors and destructor
    CMaxMinHeap(int heapType = MAX, int numItems = HEAP_MAX_ITEMS);
    CMaxMinHeap(const CMaxMinHeap &otherObj);
    virtual ~CMaxMinHeap();


    // member functions
    void            DestroyHeap();
    bool            Remove(HeapItemType &item) throw (CMaxMinHeapException);
    bool            Insert(const HeapItemType  &newItem) throw (CMaxMinHeapException);
    HeapItemType    PeekTop(void) const throw (CMaxMinHeapException);


    // Helper functions
    bool            IsLeaf(int index);
    void            Display(void) const;

private:
    // data members
    int m_heapType; // heapType
    int m_numItems; // number of nodes


    // utility functions
    int GetLeftChildIndex(int parentIndex);
    int GetRightChildIndex(int parentIndex);
    int GetParentIndex(int childIndex);

    // member functions
    void    Reheapification(int  rootIndex);

};

// include implementation file since it is a template
// #include    "cmaxminheap.tpp"
#endif // CMAXMINHEAP_H

// ==== CMaxMinHeap::CMaxMinHeap (Conversion) =================================
//
// This is the default constructor that initializes the variable m_numItems,
// m_heapType, and CList objects using CList::CList default constructor
//
// ============================================================================
template <class HeapItemType>
CMaxMinHeap<HeapItemType>::CMaxMinHeap(int heapType, int numItems)
:CList<HeapItemType>(), m_heapType(heapType), m_numItems(numItems)
{
}
// end of CMaxMinHeap::CMaxMinHeap() (conversion Constructor)


// ==== CMaxMinHeap::CMaxMinHeap (Copy) =======================================
//
// This is the copy constructor that initializes the variable m_numItems,
// m_heapType, and CList objects using other CMaxMinHeap obejct
//
// ============================================================================
template <class HeapItemType>
CMaxMinHeap<HeapItemType>::CMaxMinHeap(const CMaxMinHeap &otherObj)
:m_heapType(otherObj.m_heapType), m_numItems(CList<HeapItemType>::GetNumItems())
{
    // copy CList elements
    CList<HeapItemType>::CopyCMaxMinHeapConstructorHelper();

    // Heapify down the CList object
    for (int index = CList<HeapItemType>::GetNumItems() / 2 ; index >= 0; index--)
	{
	    // call Reheapfication function
		Reheapification(index);
	}

}
// end of CMaxMinHeap::CMaxMinHeap() (copy constructor)


// ==== CMaxMinHeap::~CMaxMinHeap() ===========================================
//
// This is the destructor.
//
// ============================================================================
template <class HeapItemType>
CMaxMinHeap<HeapItemType>::~CMaxMinHeap()
{
    DestroyHeap();
}
// end of CMaxMiHeap::~CMaxMinHeap()

// ==== CMaxMinHeap::IsLeaf ===================================================
//
// This function returns a boolean value if the node is a leaf
//
// Input:
//      int index -- [IN]: any node
//
// Output:
//      A boolean value. True if the node is a leaf, false otherwise.
// ============================================================================
template<class HeapItemType>
bool CMaxMinHeap<HeapItemType>::IsLeaf(int index)
{
    // if the node is leaf, the index of the left child of the node is
    // equal to or greater than the number of nodes.
    return (GetLeftChildIndex(index) >= m_numItems);
}
// end of CMaxMinHeap::IsLeaf()


// ==== CMaxMinHeap::GetLeftChildIndex ========================================
//
// This function returns the index of the left child
//
// Input:
//      int  parentIndex -- [IN]: the node's index
//
// Output:
//      int the left child index [OUT] -- the left child index of the node
// ============================================================================
template<class HeapItemType>
int CMaxMinHeap<HeapItemType>::GetLeftChildIndex(int parentIndex)
{
    return ((parentIndex * 2 + 1));
}
// end of CMaxMinHeap::GetLeftChildIndex()


// ==== CMaxMinHeap::GetRightChildIndex =======================================
//
// This function returns the index of the right child
//
// Input:
//      int  parentIndex -- [IN]: the node's index
//
// Output:
//      int the right child index [OUT] -- the right child index of the node
// ============================================================================
template<class HeapItemType>
int CMaxMinHeap<HeapItemType>::GetRightChildIndex(int parentIndex)
{
    return ((parentIndex * 2 + 2));
}
// end of CMaxMinHeap::GetRightChildIndex()

// ==== CMaxMinHeap::GetParentIndex =========================================
//
// This function returns the index of the parent
//
// Input:
//      int  childIndex -- [IN]: the node's index
//
// Output:
//      int the parent index [OUT] -- the index of the parent of the node
// ============================================================================
template<class HeapItemType>
int CMaxMinHeap<HeapItemType>::GetParentIndex(int childIndex)
{
    return ((childIndex - 1) / 2);
}
// end of CMaxMinHeap::GetParentIndex()


// ==== CMaxMinHeap::Reheapification =========================================
//
// This function heapifys down the CList object using recursion
//
// Input:
//      int  index -- [IN]: the node's index
//
// Output:
//      void
// ============================================================================
template<class HeapItemType>
void CMaxMinHeap<HeapItemType>::Reheapification(int  index)
{
    // save the indexes for reheapication
    int leftChildIndex = GetLeftChildIndex(index);
    int rightChildIndex = GetRightChildIndex(index);

    // the first assumption( the left child is the largest)
    // because heap is a complete binary tree
    int largestIndex = leftChildIndex;

    if (m_heapType == 0) // maxHeap
    {
        if(!IsLeaf(index)) // recursion stopping point: if it is leaf, we are done
        {
        // check if the right child exists
            if (rightChildIndex < CList<HeapItemType>::GetNumItems())
            {
            //comparison 1: if there exists a right child, compare
            // the node's priority level with that of the left child
                if(  CList<HeapItemType>:: GetItem(rightChildIndex)>
                CList<HeapItemType>::GetItem(leftChildIndex))
                {
                //if the right child's priority is larger, update the largestIndex
                largestIndex = rightChildIndex;

                }
            }
            // comparison 2: if there compare the largest node with the parent
            if (CList<HeapItemType>:: GetItem(index)
                < CList<HeapItemType>::GetItem(largestIndex))
            {
                // if the parent is smaller than the largest node
                // conduct swap
                CList<HeapItemType>::Swap(index, largestIndex);
                // recursively call heapify down to the leaf
                Reheapification(largestIndex);
            }
        }
    }
    else // minHeap
    {
        int smallestIndex = largestIndex;
        if(!IsLeaf(index)) // recursion stopping point: if it is leaf, we are done
        {
            // check if the right child exists
            if (rightChildIndex < CList<HeapItemType>::GetNumItems())
            {
                //comparison 1: if there exists a right child, compare
                // the node's priority level with that of the left child
                if(  CList<HeapItemType>:: GetItem(rightChildIndex)<
                CList<HeapItemType>::GetItem(leftChildIndex))
                {
                    //if the right child's priority is smaller, update the largestIndex
                    smallestIndex = rightChildIndex;
                }
            }
            // comparison 2: if there compare the smallest node with the parent
            if (CList<HeapItemType>:: GetItem(index)
                > CList<HeapItemType>::GetItem(smallestIndex))
            {
                // if the parent is smaller than the largest node
                // conduct the Swap function
                CList<HeapItemType>::Swap(index, smallestIndex);
                // recursively call Reheapification to heapify down to the leaf
                Reheapification(smallestIndex);
            }
        }
    }

}
// end of CMaxMinHeap::ReHeapification()


// ==== CMaxMinHeap::DestroyHeap() ===========================================
//
// This function destroys
//
// Input:
//     void
//
// Output:
//      void
// ============================================================================
template <class HeapItemType>
void  CMaxMinHeap<HeapItemType>::DestroyHeap()
{
    m_heapType = 0;
    m_numItems = 0;
    CList<HeapItemType>::Clear();
}
// end of CMaxMinHeap::DestroyHeap


// ==== CMaxMinHeap::Insert() =================================================
//
// This function inserts an element into CMaxMinHeap object.
//
//
// Input:
//      const HeapItemType  &newItem -- [IN]: the address of
// constant HeapItemType element
//
// Output:
//      bool -- [OUT]: if successful, it returns true. Otherwise, it returns
// false
// ============================================================================
template <class HeapItemType>
bool CMaxMinHeap<HeapItemType>::Insert(const HeapItemType  &newItem)
throw (CMaxMinHeapException)
{
    // successful insertion indicator
    bool InsertionSuccess = false;
    try
    {
        // try to insert an element
        // by calling CList:Insert()
        CList<HeapItemType>::Insert(newItem);

    }

    // if the list is full, resize the list and insert
    catch (const CListException &exceptionType)
    {
        if(exceptionType.GetException() == CLIST_FULL)
        {
            // resize the CList object
            CList<HeapItemType>::SetListSize(m_numItems);
            // insert the new item
            CList<HeapItemType>::Insert(newItem);
        }
        else // throw other unexpected cases
        {
            throw CMaxMinHeapException(HEAP_ERROR);
        }
    }

    // Heapify Up process

    // After inserting the value at the end of CList object
    // it is necessary to heapify up

    // the newindex is the index value of the newly added item
    int newIndex = CList<HeapItemType>::GetNumItems() - 1;

    // correct location indicator
    bool correctPosition = false;

    if (m_heapType == 0) // maxHeap
    {
         // Heapify up to the head node(index == 0)
        while((newIndex > 0) && !correctPosition)
        {
            // get the parent index of the newly added item
            int parentIndex = GetParentIndex(newIndex);

            // compare the priory levels
            if (CList<HeapItemType>::GetItem(newIndex)
            > CList<HeapItemType>::GetItem(parentIndex))
            {
                // if the newly added item is larger, swap elements.
                CList<HeapItemType>::Swap(newIndex, parentIndex);
                // update the newIndex for the next iteration
                newIndex = parentIndex;

            }
            else // if the position is correct, leave as it is
            {
                correctPosition = true;
            }
        }
    }

    else // minHeap
    {
         // Heapify up to the head node(index == 0)
        while((newIndex > 0) && !correctPosition)
        {
            // get the parent index of the newly added item
            int parentIndex = GetParentIndex(newIndex);

            // compare the priory levels
            if (CList<HeapItemType>::GetItem(newIndex)
            < CList<HeapItemType>::GetItem(parentIndex))
            {
                // if the newly added item is smaller, swap elements.
                CList<HeapItemType>::Swap(newIndex, parentIndex);
                // update the newIndex for the next iteration
                newIndex = parentIndex;

            }
            else // if the position is correct, leave as it is
            {
                correctPosition = true;
            }
        }
    }
    // since we added an item
    // update the m_numItems

    m_numItems++;
    // successful addition

    InsertionSuccess = true;

    return InsertionSuccess;

}
// end of CMaxMinHeap::Insert()

// ==== CMaxMinHeap::Remove() =================================================
//
// This function removes an element from the CMaxMinHeap object.
//
//
// Input:
//      HeapItemType  &Item -- [IN]: the address of
//  HeapItemType element
//
// Output:
//      bool -- [OUT]: if successful, it returns true. Otherwise, it returns
// false
// ============================================================================
template <class HeapItemType>
bool CMaxMinHeap<HeapItemType>::Remove(HeapItemType &item)
throw (CMaxMinHeapException)
{
    // successful deletion indicator
    bool successfulDeletion = false;

    // case #1: check if the list is empty
    if(CList<HeapItemType>::IsEmpty())
    {
        // throw CMaxMinHeapException error object
        throw CMaxMinHeapException(HEAP_EMPTY);
    }
    try
    {
        // Swap the first element with the last element
        CList<HeapItemType>::Swap(0, CList<HeapItemType>::GetNumItems() - 1);
        // remove the last element
        CList<HeapItemType>::Remove(item);
        // Heapfiy down from the first element
        Reheapification(0);
    }
    catch (const CListException &exceptionType)
    {
        // case where the target value does not exist
        if (exceptionType.GetException() == CLIST_DNE)
        {
            throw CMaxMinHeapException(HEAP_ERROR);
        }
    }
    catch (...)
    {
        // other types of exceptions
        throw CMaxMinHeapException(HEAP_ERROR);
    }

    successfulDeletion = true;

    return successfulDeletion;
}
// end of CMaxMinHeap::Remove()



// ==== CMaxMinHeap::PeakTop() ================================================
//
// This function peeks the first element of the CMaxMinHeap object.
// Input:
//    void
//
// Output:
//      HeapItemType --[OUT] the first element of the CMaxMinHeap object
// ============================================================================
template <class HeapItemType>
HeapItemType    CMaxMinHeap<HeapItemType>::PeekTop(void)
const throw (CMaxMinHeapException)
{
    try
    {
        // return the first element
        return (CList<HeapItemType>::GetItem(0));
    }
    catch (const CListException &exceptionType)
    {
        if (exceptionType.GetException() == CLIST_EMPTY)
        {
            throw CMaxMinHeapException(HEAP_EMPTY);
        }
        else // other exceptions
        {
            throw CMaxMinHeapException(HEAP_ERROR);
        }
    }
}
// end of CMaxMinHeap::PeekTop


// ==== CMaxMinHeap::Display() ================================================
//
// This function displays the priority queue.
// Input:
//    void
//
// Output:
//      void
// ============================================================================
template <class HeapItemType>
void CMaxMinHeap<HeapItemType>::Display(void) const
{
    CList<HeapItemType>::CListDisplay();
}
// end of CMaxMinHeap::Display()
