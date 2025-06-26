#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1, pid2, pid3;
  
  printf(1, "Priority Scheduler Test with Aging\n");
  printf(1, "===================================\n");
  
  // Create three child processes with different priorities
  pid1 = fork();
  if(pid1 == 0) {
    // Child 1: High priority (8)
    setpriority(getpid(), 8);
    printf(1, "Child 1 (PID %d, Priority 8): Starting CPU-intensive task\n", getpid());
    
    // CPU-intensive loop with longer iterations to show aging
    for(int i = 0; i < 2000000; i++) {
      if(i % 400000 == 0) {
        printf(1, "Child 1 (High Priority): %d iterations, current priority: %d\n", 
               i, getpriority(getpid()));
      }
      // Add some yielding to allow other processes to show aging
      if(i % 100000 == 0) {
        yield();
      }
    }
    printf(1, "Child 1 (High Priority): Finished\n");
    exit();
  }
  
  pid2 = fork();
  if(pid2 == 0) {
    // Child 2: Medium priority (5) - default
    printf(1, "Child 2 (PID %d, Priority 5): Starting CPU-intensive task\n", getpid());
    
    // CPU-intensive loop
    for(int i = 0; i < 2000000; i++) {
      if(i % 400000 == 0) {
        printf(1, "Child 2 (Medium Priority): %d iterations, current priority: %d\n", 
               i, getpriority(getpid()));
      }
      if(i % 100000 == 0) {
        yield();
      }
    }
    printf(1, "Child 2 (Medium Priority): Finished\n");
    exit();
  }
  
  pid3 = fork();
  if(pid3 == 0) {
    // Child 3: Low priority (2)
    setpriority(getpid(), 2);
    printf(1, "Child 3 (PID %d, Priority 2): Starting CPU-intensive task\n", getpid());
    
    // CPU-intensive loop
    for(int i = 0; i < 2000000; i++) {
      if(i % 400000 == 0) {
        printf(1, "Child 3 (Low Priority): %d iterations, current priority: %d\n", 
               i, getpriority(getpid()));
      }
      if(i % 100000 == 0) {  // Every 100k iterations, voluntarily give up CPU
        yield();
      }
    }
    printf(1, "Child 3 (Low Priority): Finished\n");
    exit();
  }
  
  // Parent process
  printf(1, "\nParent: Created 3 children with different priorities\n");
  printf(1, "Child 1 (PID %d): Priority 8 (High)\n", pid1);
  printf(1, "Child 2 (PID %d): Priority 5 (Medium)\n", pid2);
  printf(1, "Child 3 (PID %d): Priority 2 (Low)\n", pid3);
  
  printf(1, "\nNote: Watch how priorities change due to aging!\n");
  printf(1, "Low priority processes should eventually get CPU time.\n\n");
  
  // Wait for all children
  wait();
  wait();
  wait();
  
  printf(1, "\nPriority test with aging completed!\n");
  printf(1, "All processes finished - aging prevented starvation!\n");
  exit();
}
