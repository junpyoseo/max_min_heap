// File: personinfo.h
// ============================================================================
// Header file for the PersonInfo
// ============================================================================
#ifndef PERSONINFO_H
#define PERSONINFO_H


template <class T>
struct   PersonInfo
{
    // constructor
    // a set of default arguments were necessary to instantiate PersonInfo<int>
    // structure in the main function
    PersonInfo(double weight = 0, double height = 0, int age = 0,
               std::string name = "Tony Stark", T priority = 0) {
                                                m_weight = weight;
                                                m_height = height;
                                                m_age = age;
                                                m_fullName = name;
                                                m_priority = priority;
                                             }

    // data members
    double      m_weight;   // pounds
    double      m_height;   // inches
    int         m_age;      // years
    std::string m_fullName; // person's name
    T           m_priority; // priority number (the higher the # the greater
                            // the priority).
};


// overloaded stream operators
template <class T>
ostream& operator<<(ostream &outStream, const PersonInfo<T> &person)
{
    outStream << person.m_fullName << " ";

    return outStream;
}

template <class T>
istream& operator>>(istream &inStream, const PersonInfo<T> &person)
{
    double weight;
    double height;
    int age;
    std::string name;
    T priority;

    std::cout << "Enter a patient's information :\n";
    std::cout << "Weight, Height, Age, Priority Level, Full Name \n";
    inStream >> weight >> height >> age>> priority ;

    cin.ignore();
    std::getline(std::cin, name);

    person.m_weight = weight;
    person.m_height = height;
    person.m_age = age;
    person.m_priority = priority;
    person.m_fullName = name;

    return inStream;
}



// overloaded comparison operators
template<class T>
bool operator<(const PersonInfo<T> &lhs, const PersonInfo<T> &rhs)
{
    if (lhs.m_priority < rhs.m_priority)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool operator>(const PersonInfo<T> &lhs, const PersonInfo<T> &rhs)
{
    if(lhs.m_priority > rhs.m_priority)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool operator==(const PersonInfo<T> &lhs, const PersonInfo<T> &rhs)
{
    if(lhs.m_priority == rhs.m_priority)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif // PERSONINFO_H
