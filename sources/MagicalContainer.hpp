//
// Created by Nachshon on 6/4/2023.
//
#include <iostream>
#include <set>
#include <vector>


#ifndef CPPEX5_MAGICALCONTAINER_H
#define CPPEX5_MAGICALCONTAINER_H

namespace ariel{

};
using namespace std;



class MagicalContainer {
     vector<int> nums ;/// remember it keeps the element in assceding order
     vector<int *> prime_numbers;


public:
    MagicalContainer(){};
    void addElement(int);
    int size();
    void removeElement(int );
    static bool isPrime(int number);
    static void deleteFromPrimeVec(vector<int*> & primeVec, int num);
    ~MagicalContainer();

    class AscendingIterator {
        MagicalContainer &mc ;
        int index ;

    public:
        //// Constructors :
        explicit AscendingIterator(MagicalContainer &mc ) :mc(mc), index(0) {};  /// passing a reference to avoid multipling the set object
        AscendingIterator(MagicalContainer &mc , int index ) :mc(mc), index(index) {};  /// passing a reference to avoid multipling the set object
        AscendingIterator(AscendingIterator const &other): mc(other.mc) , index(other.index){};
        //// begin & end
        AscendingIterator begin();
        AscendingIterator end();
        /// operators
        int  operator *();
        AscendingIterator& operator ++();
        bool operator ==(MagicalContainer::AscendingIterator  other);
        bool operator !=(MagicalContainer::AscendingIterator  other);
        void operator = (MagicalContainer::AscendingIterator & other );
        bool operator >(MagicalContainer::AscendingIterator  other) const;
        bool operator < (MagicalContainer::AscendingIterator  other );
    };

    class SideCrossIterator {
        MagicalContainer &mc ;
        int start ;
        int last ;
        bool fromStart ;
    public:
        /// Constructors
        explicit SideCrossIterator(MagicalContainer &mc): mc(mc) , start(0), last(mc.size()-1),fromStart(true){};
        SideCrossIterator(MagicalContainer& container, int start , int last ) :mc(container) ,start(start) , last(last) {};
     //   SideCrossIterator(SideCrossIterator& other ): mc(other.mc) , start(other.start) , last(other.last), fromStart(other.fromStart){};
        /// begin & end
        SideCrossIterator begin();
        SideCrossIterator end();
        /// operators
        int  operator *();
        SideCrossIterator& operator ++();
        bool operator ==(MagicalContainer::SideCrossIterator  other);
        bool operator !=(MagicalContainer::SideCrossIterator other);
        void operator = (MagicalContainer::SideCrossIterator & other );
        bool operator > (MagicalContainer::SideCrossIterator  other );
        bool operator < (MagicalContainer::SideCrossIterator  other );
    };
    class PrimeIterator{
        MagicalContainer & mc ;
        int index ;
    public:
        PrimeIterator(MagicalContainer& container) : mc(container) , index(0) {};
        PrimeIterator(MagicalContainer &container , int index ) : mc(container), index(index){};
        PrimeIterator( PrimeIterator const &other ) : mc(other.mc), index(other.index){};
        PrimeIterator& operator ++();
        PrimeIterator begin();
        PrimeIterator end();
        int operator *();
        bool operator ==(MagicalContainer::PrimeIterator  other);
        bool operator !=(MagicalContainer::PrimeIterator other);
        void operator = (MagicalContainer::PrimeIterator & other );
        bool operator > (MagicalContainer::PrimeIterator  other );
        bool operator < (MagicalContainer::PrimeIterator  other );


    };


};
#endif //CPPEX5_MAGICALCONTAINER_H
