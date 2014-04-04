#include <iostream>
#include "Leap.h"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "draw.hpp"
#include "LeapListener.hpp"
#include <pthread.h>

using namespace Leap;

void LeapHandler(){
  // Create a sample listener and controller
  LeapListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);
  
}

int main(int argc, char* argv[])
{
  pthread_t thread1, thread2;	     
  int  iret1, iret2;
  const char *filename = argv[1];
  /* Create independent threads each of which will execute function */
  
  iret1 = pthread_create( &thread1, NULL, LeapHandler, NULL);
  iret2 = pthread_create( &thread2, NULL, draw, (void*) filename);
  
  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */
  
  //pthread_join( thread1, NULL);
  //pthread_join( thread2, NULL);
  
  //printf("Thread 1 returns: %d\n",iret1);
  //printf("Thread 2 returns: %d\n",iret2);
  exit(0);
  
}

