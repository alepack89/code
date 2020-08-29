#ifndef _THREAD_BARRIER_H
#define _THREAD_BARRIER_H

//Include standard libraries
#include <iostream>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>

//Utilities namespace
namespace utils
{
  //Thread namespace
  namespace threads
  {
    
    //Class representing a simple thread barrier 
    //It requires the number of threads to be blocked (capacity)
    //Once a thread enters the barrier, it cannot exit it until 
    //all the others N-1 threads have entered the barrier.
    //Moreover, once full, one thread can re-enter the barrier only if all the 
    //occupying threads have left the barrier 
    class ThreadBarrier
    {
      //------------------------------------
      //Internal properties 
      
      protected:
        
        //The number of threads which can enter the barrier 
        //at a time
        size_t m_capacity;
        size_t m_size;
        
        //Flag indicating whether or not the barrier can be entered
        bool can_enter_the_barrier;
        bool flush_the_barrier;
        
        //Mutex and condition variable used to guard the barrier 
        std::mutex mtx;
        std::condition_variable cnd;
        
      //------------------------------------
      //Accessors  
        
      public:
        
        //The number of threads waiting inside the barrier
        size_t size();
        
        //The total number of threads which can enter the barrier
        size_t capacity();
        
      //------------------------------------
      //Constructors and destructors 
        
      public:
        
        //Default constructor
        ThreadBarrier(size_t capacity);
        
        //Copy and move constructors (note: barrier cannot be copied)
        ThreadBarrier(const ThreadBarrier&  barrier) = delete;
        ThreadBarrier(      ThreadBarrier&& barrier) = delete;
        
        //Copy and move assignments (note: barrier cannot be copied)
        ThreadBarrier& operator= (const ThreadBarrier&  barrier) = delete;
        ThreadBarrier& operator= (      ThreadBarrier&& barrier) = delete;
      
        //Virtual destructor
        virtual ~ThreadBarrier();
        
      //------------------------------------
      //Public methods
        
      public:
        
        //Method used by a thread to enter the barrier
        void enter();
    };
    
  }
}

#endif
