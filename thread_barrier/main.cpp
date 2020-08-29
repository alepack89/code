/*
 * Fun with threads and thread barriers
 */

//Include standard libraries
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>
#include <vector>

//Include thread barrier 
#include <thread_barrier.h>

//Dummy function to be executed by the threads
void dummyThreadFun(size_t thread_idx, size_t* target_idx, std::shared_ptr<utils::threads::ThreadBarrier> barrier)
{
  while(true)
  {
    //Wait for all threads to complete execution
    barrier->enter();
    
    //Check if all threads have executed 
    if (*target_idx >= barrier->capacity())
      break;
  
    //Only the target thread performs execution
    if (thread_idx == *target_idx)
    {
      //Execute
      std::cout << "Executing thread " << thread_idx << std::endl;
      for (size_t i = 0; i < 1e9; )
        i++;
      
      std::this_thread::sleep_for(std::chrono::seconds{2});
      
      //Update target thread index
      *target_idx = *target_idx + 1;
      std::cout << "Next thread = " << *target_idx << std::endl;
    }
  }
  
  //Wait for all threads to finish
  barrier->enter();
}

//Main method
int main (int argc, char* argv[])
{      
  //Instantiate thread barrier 
  size_t thread_count = 10;
  auto barrier = std::make_shared<utils::threads::ThreadBarrier>(thread_count);
  
  //Initialize the target idx 
  size_t target_idx = 0;
  
  //Create threads on which we will use the barrier
  std::vector<std::thread> threads;
  for (size_t i = 0; i < thread_count; i++)
    threads.emplace_back(std::bind(&dummyThreadFun, i, &target_idx, barrier));
  
  for (auto& t : threads)
    t.join();
  
  //Return success code
  return 0;
}
