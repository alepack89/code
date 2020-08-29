//Include header file 
#include <thread_barrier.h>

//Utilities namespace
namespace utils
{
  //Thread namespace
  namespace threads
  {
    //------------------------------------------------------------------
    //Accessors 
    
    //The number of threads waiting inside the barrier
    size_t ThreadBarrier::size()
    {
      std::unique_lock<std::mutex> lock{ mtx };
      return m_size;
    }

    //The total number of threads which can enter the barrier
    size_t ThreadBarrier::capacity()
    {
      std::unique_lock<std::mutex> lock{ mtx };
      return m_capacity;
    }
    
    //------------------------------------------------------------------
    //Constructors and destructors 
    
    //Default constructor
    ThreadBarrier::ThreadBarrier(size_t capacity)
      : m_capacity            { capacity }, 
        m_size                {        0 }, 
        can_enter_the_barrier {     true }
    {
    }
    
    //Destructor
    ThreadBarrier::~ThreadBarrier()
    {
      //Lock the mutex before entering the barrier 
      std::unique_lock<std::mutex> lock{ mtx };
      
      //Signal that the barrier should be flushed
      flush_the_barrier = true;
      cnd.notify_all();
      
      //Wait for barrier to be empty
      cnd.wait(lock, [&](){ return (m_size == 0); });
    }

    //------------------------------------------------------------------
    //Public methods
    
    //Method used by a thread to enter the barrier
    void ThreadBarrier::enter()
    {
      //Lock the mutex before entering the barrier 
      std::unique_lock<std::mutex> lock{ mtx };
      
      //Check if the barrier can accept requests 
      cnd.wait(lock, [&](){ return ((can_enter_the_barrier == true) || (flush_the_barrier == true)); });
      if (flush_the_barrier == true)
        return;
            
      //Check if we have reached maximum size
      if (++m_size < m_capacity)
      {
        //Wait for the last thread to enter the barrier
        cnd.wait(lock, [&](){ return ((can_enter_the_barrier == false) || (flush_the_barrier == true)); });
      }
      else
      {
        //Signal that the last thread is arrived 
        //Now the barrier can be left 
        can_enter_the_barrier = false;
        cnd.notify_all();
      }
      
      //Check if the barrier is empty again
      if (--m_size == 0)
      {
        //Signal that the last thread has left 
        //Now the barrier can be re-entered again 
        can_enter_the_barrier = true;
        cnd.notify_all();
      }
    }

    
  }
}
