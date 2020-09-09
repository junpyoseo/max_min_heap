// ============================================================================
// File: clist.h
// ============================================================================
// Header file for the CList
// ============================================================================
#ifndef DYNAMIC_CLIST_HEADER
#define DYNAMIC_CLIST_HEADER


// type definitions
enum    CListExceptionType  { CLIST_FULL,
                              CLIST_EMPTY,
                              CLIST_ERROR,
                              CLIST_SUCCESS,
                              CLIST_INVALID_INDEX,
                              CLIST_DNE
                            };

// constant(s)
const   int     MAX_ITEMS = 5;


// exception class for CList
class CListException
{
public:
    // constructor
    CListException(CListExceptionType   exceptType)
            : m_exceptType(exceptType) {}

    // member function
    CListExceptionType GetException() const {return m_exceptType;}

private:
    CListExceptionType  m_exceptType;
};



// CList Class declaration
template <class ListItemType>
class   CList
{
public:
    // constructor(s) and destructor
    CList();
    CList(const CList   &object);
    virtual ~CList();

    // member functions
    void            DestroyList();
    ListItemType    GetItem(int  index) const throw (CListException);
    int             GetNumItems() const;
    void            Insert(const ListItemType  &newItem) throw (CListException);
    bool            IsEmpty() const;
    bool            IsFull() const;
    void            Remove(const ListItemType  &value) throw (CListException);
    void            SetListSize(int num);
    void            Clear();


    // helper functions (new functions)
    void            CListDisplay(void) const;
    void            CopyCMaxMinHeapConstructorHelper(const CList &otherObj);
    void            Swap(int target, int source);


    // overloaded operator(s)
    CList<ListItemType>&      operator=(const CList &rhs);
    ListItemType&             operator[](const int index);



private:
    // data members
    int             m_currSize; // current allocated array size from HEAP
    int             m_numItems; // current number of items
    ListItemType    *m_items;   // head pointer to items

    // member functions
    int         MoveItems(int  index, char  direction);
    int         CopyList(const CList &otherList);
    bool        ItemExists(int &index, const ListItemType &item) throw (CListException);
};


// include implementation file since it is a template

// #include    "clist.tpp"
#endif // DYNAMIC_CLIST_HEADER


// ==== CList::CList (Default) ================================================
//
// This is the default constructor that initializes the variable m_numItems.
//
// ============================================================================
template <class ListItemType>
CList<ListItemType>::CList(): m_currSize(MAX_ITEMS), m_numItems(0),
m_items (new ListItemType[m_currSize])
{
}
// end of CList::CList(Default Constructor)

// ==== CList::CList (Copy) ===================================================
//
// This is the copy constructor.
//
// ============================================================================
template <class ListItemType>
CList<ListItemType>::CList(const CList   &object)
{
    m_items = new ListItemType[object.m_currSize];

    //update variables
    m_numItems = object.m_numItems;
    m_currSize = object.m_currSize;

    // copy the elements of the array
    for (int i = 0; i < m_currSize ; i++)
    {
        m_items[i] = object.m_items[i];
    }
}
// end of "CList::CList" (copy constructor)

// ==== CList::~CList (Destructor) ============================================
//
// This is the destructor, which calls the DestroyList function.
//
// ============================================================================
template <class ListItemType>
CList<ListItemType>::~CList()
{
    DestroyList();
}
// end of "CList::~CList()" destructor

// ==== CList::DestroyList ====================================================
//
// This function resets the lists by assigning 0 to m_numItems
//
// Input:
//      void
//
// Output:
//      void
//
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::DestroyList()
{
    m_numItems = 0;
    m_currSize = 0;

    delete []m_items;

}
// end of CList::DestoryList()


// ==== CList::GetItem ==================================================
//
// This function retrieves the value of an item at a particular location.
//
// The function throws error codes from the class CListException
//
// Input:
//      index   -- the index location for the target item (zero-based).
//
// Output:
//      item    -- a ListItemType object.
//
// ============================================================================
template <class ListItemType>
ListItemType CList<ListItemType>::GetItem(int  index) const throw (CListException)
{
    // case #1: Empty List
    if (IsEmpty())
    {
        throw CListException(CLIST_EMPTY);
    }
    // case #2: out of boundary (array)
    if ((index < 0 ) || (index > (m_numItems - 1 )))
    {
        throw CListException(CLIST_INVALID_INDEX);
    }
    // case #3: return the element to the caller
    return m_items[index];
}
// end of CList::GetItem()


// ==== CList::GetNumItems ====================================================
//
// This function retrieves the number of items in the list.
//
// Input:
//      void
//
// Output:
//      A int value.
//
// ============================================================================
template <class ListItemType>
int CList<ListItemType>::GetNumItems() const
{
    return (m_numItems);
} // end of CList::GetNumItems

// ==== CList::Insert =========================================================
//
// This function inserts an item at the end of the list. If the list is full,
// the function will throw an error.
//
// Input:
//      newItem     -- a const reference to the new item to insert into the list
//
// Output:
//      void
//
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::Insert(const ListItemType  &newItem) throw (CListException)
{
    // case #1: the list is full
    if (IsFull())
    {
        // throw an exception

        throw CListException(CLIST_FULL);
    }


    // case #2: the list is not full
    // add the item at the end of the list
    m_items[m_numItems] = newItem;

    m_numItems++;

}
// end of CList::Insert()

// ==== CList::IsEmpty ========================================================
//
// This function returns a boolean value if the list is empty.
//
// Input:
//      void
//
// Output:
//      A boolean value. True if list is empty, false otherwise.
//
// ============================================================================
template <class ListItemType>
bool CList<ListItemType>::IsEmpty() const
{
    return (m_numItems == 0);
}
// end of CList::IsEmpty

// ==== CList::IsFull =========================================================
//
// This function returns a boolean value if the list is full.
//
// Input:
//      void
//
// Output:
//      A boolean value. True if list is full, false otherwise.
//
// ============================================================================
template <class ListItemType>
bool CList<ListItemType>::IsFull() const
{
    return (m_numItems == m_currSize);
} // end of CList::IsFull()


// ==== CList::Remove =========================================================
//
// This function removes an item from the list.
//
// If the target item is at the end of the list, the locations of the
// other list items are unaffected.
//
// If the target item is before the end of the list, all elements after
// the target location are moved towards the front of the array one
// position to fill in the gap.
//
// The function throws error codes from the class CListException
//
// Input:
//      value       -- a const reference to an item to remove from the list
//
// Output:
//      void
//
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::Remove(const ListItemType  &value) throw (CListException)
{
    int index;
    bool funcStatus;

    // check if the item exists
    try
    {
        funcStatus = CList::ItemExists(index, value);
    }

    // rethrow the exception(case#1: Empty List)
    catch (CListException &CListExceptionObject)
    {
        throw;
    }
    // throw the exception(case #2: DNE)
    if (funcStatus == false)
    {
        // exception should be handled
        throw CListException(CLIST_DNE);

    }

    // case #3: found an item
    // case #3 - (1) move items
     if ((index > -1) && (index < (m_numItems -1)))
     {
        MoveItems(index, 'F');
     }
    // adjust the counter


    --m_numItems;

}
// end of CList::Remove()

// ==== CList::SetListSize ====================================================
// This function resizes the memory from the HEAP
//
// Input:
//      num         [IN]    - An integer to increase or decrease the memory
//
// Output:
//      void
//
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::SetListSize(int num)
{
    // create a pointer to hold new list size
    ListItemType *newItems = new ListItemType[num];
    int i = 0; // counter
    int stopVal;

    // check if the list is getting smaller or larger to appropriate resize
    stopVal = (m_numItems > num) ? num : m_numItems;

    for ( i = 0; i < stopVal; i++)
    {
        newItems[i] = m_items[i];
    }
    // update data members
    m_currSize = num;
    m_numItems = stopVal;

    // delete old pointer and update
    delete [] m_items;
    m_items = newItems;

}// end of CList::SetListSize()


// ==== CList::Clear ==========================================================
// This function clears the entries by resetting the number of m_numItems to 0
// and setting m_currSize to default value (MAX_ITEMS);
//
// Input:
//      void
//
// Output:
//      void
//
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::Clear()
{
    // set m_numItems to zero
    m_numItems = 0;
    // call the resizing function to the default value
    SetListSize(MAX_ITEMS);
}
// end of CList::Clear()

// ==== CList::operator= ======================================================
// This is the overloaded assignment operator, copying the parameter's list to
// the calling object.
//
// Input:
//      rhs         -- a reference to a source CList object
//
// Output:
//      A reference to the calling object.
//
// ============================================================================
template <class ListItemType>
CList<ListItemType>& CList<ListItemType>::operator=(const CList &rhs)
{
    // case #1 self assigning guard
    // check the case assigning the object to itself
    if (this == &rhs)
    {
        return *this;
    }

    // copy the object
    this -> CopyList(rhs);

    return *this;
}
// end of CList::operator=()


// ==== CList::operator[] =====================================================
// This is the overloaded subscript operator, accessing the data from the array
//
// Input:
//      rhs         -- a reference to a source CList object
//
// Output:
//      A reference to the calling object.
//
// ============================================================================
template<class ListItemType>
ListItemType& CList<ListItemType>::operator[](const int index)
{
    if ((index < 0 ) || (index > (m_numItems - 1 )))
    {
        throw CListException(CLIST_INVALID_INDEX);
    }

    return m_items[index];
}
// end of CList::operator[]()

// ==== CList::MoveItems ======================================================
//
// This function moves the elements of the list forward or backward one
// position.
//
// If an item is inserted before the last element in the list, the
// trailing elements must be moved towards the back of the array by one
// position.
//
// If a list item is removed from the middle of the list, the trailing elements
// must be moved towards the front of the array one position to close the gap.
//
// The caller of this function only needs to indicate the location where an
// element will go or have to removed, and the direction to move the elements
// (towards the F>ront or B>ack of the array).
//
// NOTE: This function assumes that the caller has already verified the
// validity of the index parameter.
//
// Input:
//      index           -- the index location for the target item (zero-based).
//
//      direction       -- the direction to move the trailing elements.
//                         A char value of 'F' moves the elements to the front.
//                         A char value of 'B' moves the elements to the back.
//
// Output:
//      An integer reporting the number of items moved.
//
// ============================================================================
template <class ListItemType>
int CList<ListItemType>::MoveItems(int  index, char  direction)
{
    int finalLocation;
    int shiftSize;
    int currLocation;
    bool stopIndicator = true;
    int counter = 0;

    // initialize the source and destination index values
    if (direction == 'B')
    {
        currLocation = m_numItems - 1;
        finalLocation = m_numItems;
        shiftSize = -1; // move from higher to lower addresses
    }
    else // move forward
    {
        currLocation = index + 1;
        finalLocation = index;
        shiftSize = 1; // move from lower to higher addresses
    }

    // adjust elements
    do
    {
        m_items[finalLocation] = m_items[currLocation];
        finalLocation += shiftSize;
        currLocation += shiftSize;
        counter++;

        if (direction == 'B')
        {
            if((currLocation < index) || (finalLocation < 1))
            {
               stopIndicator = false;
            }
        }
        else // Move forward
        {
            if (currLocation >= m_numItems)
            {
                stopIndicator = false;
            }
        }
    } while (stopIndicator);

    return counter;
}

// end of CList::MoveItems()

// ==== CList::CopyList =======================================================
//
// This function copies the contents of one CList object to another CList
// object.  If the destination object already contains a list, then that list
// is first released.
//
// Input:
//      otherList   -- a const reference to an existing CList object
//
// Output:
//      The total number of items copied from the source object to the
//      destination object.
//
// ============================================================================
template <class ListItemType>
int CList<ListItemType>::CopyList(const CList &otherList)
{
    // delete the pre-exsiting data and allocate space
    delete [] m_items;
    m_items = new ListItemType[otherList.m_currSize];

    // update variables
    m_numItems = otherList.m_numItems;
    m_currSize = otherList.m_currSize;

    for ( int i = 0; i < m_numItems; i++)
    {
        m_items[i] = otherList.m_items[i];
    }

    return m_numItems;
}
// end of CList::CopyList()

// ==== CList::ItemExists =====================================================
//
// This function checks if an item exists in the list. If the list is empty
// index will have a value of -1 and the function will throw an exception. If
// the item was not found, a false is returned.  If the item was found, the
// location in the list (index) is updated and a true is returned.
//
// Input:
//      index   -- the reference index location for the target item
//                 (zero-based). Will update correct index location when it
//                 returns to the caller
//
//      item    -- a reference to a ListItemType object.
//
// Output:
//      bool (true when found, false otherwise)
//
// ============================================================================
template <class ListItemType>
bool CList<ListItemType>::ItemExists(int &index, const ListItemType &item)
throw (CListException)
{
    // case #1: Empty List
    if (IsEmpty())
    {
        index = -1;
        throw CListException(CLIST_EMPTY);
    }

    // case #2: found the item
    for (int i = 0; i < m_numItems; ++i)
    {
        if (m_items[i] == item)
        {
            index = i;
            return true;
        }
    }

    // case #3: the item is not found
    return false;
}
// end of CList:ItemExists()

// =============================================================================
// Utility functions
// =============================================================================

// ==== CopyCMaxMinHeapConstructorHelper =======================================
//
// This function is a utility function helping CMaxMinHeap, the child class
// the function copies the contents of one CList object to another CList
// object. Unlike CList::Copy, it does not release the memory because it only
// helps initializing the CList object for the subclass
//
// Input:
//      otherList   -- a const reference to an existing CList object
//
// Output:
//      The total number of items copied from the source object to the
//      destination object.
//
// ============================================================================
template<class ListItemType>
void CList<ListItemType>::CopyCMaxMinHeapConstructorHelper(const CList &otherObj)
{
    // allocate space
    m_items = new ListItemType[otherObj.m_currSize];

    // update variables
    m_numItems = otherObj.m_numItems;
    m_currSize = otherObj.m_currSize;

    // copy each elements
    for ( int i = 0; i < m_numItems; i++)
    {
        m_items[i] = otherObj.m_items[i];
    }

}
// end of CList::CopyCMaxMinHEapConstructorHelper()


// ==== Swap ==================================================================
//
// This function swaps elements using only indexes to help the child class to
// swap CList object elements with indexes only
// Input:
//      int target  -- an index value for the target location
//      int source -- an index value for the source location
//
// Output:
//      the function swaps the elements of the CList objects.
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::Swap(int target, int source)
{
    // Swap the elements
    ListItemType temp = m_items[target];
    m_items[target] = m_items[source];
    m_items[source] = temp;

}
// end of CList::Swap()


// ==== CListDisplay ========================================================
//
// The function displays each element of the CList object
//
// Input:
//      void
// Output:
//      The function displays each element of the CList object
//
// ============================================================================
template <class ListItemType>
void CList<ListItemType>::CListDisplay(void) const
{
    // display each element
    for (int i = 0; i < m_numItems; i++)
    {
        std::cout << m_items[i] << " ";
    }
}
// end of CList::CListDisplay()


