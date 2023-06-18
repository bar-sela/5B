//
// Created by Nachshon on 6/4/2023.
//

#include "MagicalContainer.hpp"
#include <algorithm>
#include "cmath"




MagicalContainer::~MagicalContainer() {
 for(auto pInt: this->prime_numbers){
     delete pInt;
 }
}

void MagicalContainer::addElement(int number) {
///  https://www.geeksforgeeks.org/lower_bound-in-cpp/


////returnes iterator which "points" to the first element greater then number
//// then we want to insert the element at the position in the vetcor where it is pointing at
    auto it = std::lower_bound(this->nums.begin(), this->nums.end(),number );
    this->nums.insert(it, number);

    if(isPrime(number)) {
        /// the test force us to get int and not refernece of the number -> need to allocate space for int and enter the prime vector

        int *pn = new int;
        *pn = number;
        this->prime_numbers.push_back(pn);
    }
}

int MagicalContainer::size() {
    return this->nums.size();
}

/// deleting elements from the MS
void MagicalContainer:: removeElement(int num) {
    /// erase from the int vector
    auto it = find(nums.begin(), nums.end(), num);
    if (it != nums.end()) {
        nums.erase(it);
    }
    /// In Case the the MS dosent contains num
    else
        throw std::runtime_error("the elemnt has not been found");

    /// deleteing from prime numbers and free memory
    if(isPrime(num))
        deleteFromPrimeVec(this->prime_numbers , num);


}



bool MagicalContainer::isPrime(int n) {

    ////https://www.programiz.com/cpp-programming/examples/prime-number
    bool is_prime = true;
    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        is_prime = false;
    }
    // loop to check if n is prime
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}

void MagicalContainer::deleteFromPrimeVec(vector<int *> &primeVec, int num) {
    for(int  i = 0 ; i < primeVec.size(); i ++){
        if(*primeVec[(unsigned long )i] == num) {
            delete primeVec[(unsigned long )i];
            primeVec.erase(primeVec.begin() + i);
        }
    }
}
///*************************************** AscendingIterator ***************************************

/// begin(type): Returns the appropriate iterator (ascending, cross, or prime) pointing to the first
/// element of the container based on the specified type.
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    //// creates iterator with index = 0

    return MagicalContainer::AscendingIterator(this->mc);

}

////• end(type): Returns the appropriate iterator (ascending, cross, or prime) pointing
/// one position past the last element of the container based on the specified type.

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    return MagicalContainer::AscendingIterator(this->mc, this->mc.size());
}


int MagicalContainer::AscendingIterator :: operator *(){
    return this->mc.nums[(size_t)this->index];
}

void MagicalContainer::AscendingIterator :: operator=(AscendingIterator &other) {
    if(this == &other)
        throw std::runtime_error("assigning object to itself");
     if(& this->mc != &other.mc)
         throw std::runtime_error("the iterators has Different Magical Containers!!");
  this->mc = other.mc;
  this->index = other.index;
}

/// Pre-increment operator (operator++)
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator:: operator++(){
    if(*this == this->end())
        throw  std::runtime_error("At the end already!");

    this->index++;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(AscendingIterator other) {
    return !(other> *this)&& !(*this > other);
}
    bool MagicalContainer::AscendingIterator::operator!=(AscendingIterator other) {
      return !(*this == other) ;
}

bool MagicalContainer::AscendingIterator::operator>(MagicalContainer::AscendingIterator other) const {
    return this->index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(MagicalContainer::AscendingIterator other) {
   return other > *this;
}




///***************************************  SideCrossIterator ***************************************

//// returnes iterator to the start of the MC
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return MagicalContainer::SideCrossIterator(mc);

}
//// returnes iterator to the end of the MC ,
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    /// Case : the size of the MC size is odd number
    if(this->mc.size() % 2 != 0 )
        return MagicalContainer::SideCrossIterator(mc, mc.size()/2 +1, mc.size()/2);

    /// Case : the size of the MC size is even number
    return MagicalContainer::SideCrossIterator(mc, mc.size()/2, mc.size()/2-1);


}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
    /// if its in the end :
    if(*this == this->end())
        throw std::runtime_error("At the end already!");

    /// start turn :
    if(this->fromStart)
      this->start++;
    //// last turn :
    else
      this->last-- ;

    /// prepearing for next iteration :
    this->fromStart = !this->fromStart;
    return *this ;
}

/// returnes the current element "pointed by the iterator
int MagicalContainer::SideCrossIterator::operator*() {
    if(this->fromStart)
        return mc.nums[(size_t)start];
    return mc.nums[(size_t)last];
}
//// comparison
bool MagicalContainer::SideCrossIterator::operator==( SideCrossIterator other) {
    return !(other> *this)&& !(*this > other);
}
bool MagicalContainer::SideCrossIterator::operator!=(SideCrossIterator other) {
    return !(*this == other) ;
}

void MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &other) {
   if(this == &other)
        throw std::runtime_error("assigning object to itself");
    if(& this->mc != &other.mc)
        throw std::runtime_error("the iterators has Different Magical Containers!!");
   this->mc = other.mc ;
   this->last = other.last;
   this->start = other.start;

}

bool MagicalContainer::SideCrossIterator::operator>(SideCrossIterator other) {
    return (this->start > other.start) || this->last < other.last;
}

bool MagicalContainer::SideCrossIterator::operator<(SideCrossIterator other) {
     return other > *this;
}

///***************************************  PrimeIterator ***************************************

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return MagicalContainer::PrimeIterator(this->mc, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return MagicalContainer::PrimeIterator(this->mc, this->mc.prime_numbers.size());
}

MagicalContainer::PrimeIterator & MagicalContainer::PrimeIterator::operator++() {
     if(*this == this->end())
         throw  std::runtime_error("At the end already!");

     this->index++;
     return *this;
}

int MagicalContainer::PrimeIterator::operator*() {
    return *this->mc.prime_numbers[(size_t)index];
}
bool MagicalContainer::PrimeIterator::operator>(MagicalContainer::PrimeIterator other) {
    if(this->index > other.index)
        return true;
    return false;
}
bool MagicalContainer::PrimeIterator::operator<(MagicalContainer::PrimeIterator other) {
       return other  > * this;
}
bool MagicalContainer::PrimeIterator::operator==(MagicalContainer::PrimeIterator other) {
         return !( other > *this  ) && !(*this > other) ;
}

bool MagicalContainer::PrimeIterator::operator!=(MagicalContainer::PrimeIterator other) {
    return  !(other == *this);
}

void MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator &other) {
     if(this == &other )
         throw std::runtime_error("same adress in using operator =");
    if(& this->mc != &other.mc)
        throw std::runtime_error("the iterators has Different Magical Containers!!");
     this->mc = other.mc;
     this->index = other.index;
}



