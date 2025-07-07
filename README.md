# Project 2: Priority CPU Scheduling for xv6

## 📋 Overview

In this project, you will implement a priority-based process scheduler with an aging mechanism in the xv6 operating system. This will replace the default round-robin scheduler with a more sophisticated scheduling algorithm that prevents starvation while maintaining priority-based execution order.

## 🎯 Learning Objectives

By completing this project, you will:
- ✅ Understand process scheduling algorithms and their trade-offs
- ✅ Learn how to modify kernel data structures and system calls
- ✅ Implement aging mechanisms to prevent starvation
- ✅ Gain hands-on experience with operating system internals
- ✅ Practice safe kernel programming and memory management

## 📚 Background

### Current xv6 Scheduler
The default xv6 scheduler employs a simple round-robin algorithm with a fixed time quantum of approximately 10 milliseconds, which executes processes in the order they become runnable. 
It scans the process table from the beginning and runs the first runnable process it finds until that process voluntarily yields, blocks, exits, or the time slice (i.e., quantum) expires. 
This approach is simple, but it doesn't allow for prioritizing critical processes or ensuring a fair distribution of time.

### Priority Scheduling
Priority scheduling assigns each process a priority level and always runs the highest-priority ready process. However, this can lead to **starvation** where low-priority processes never get CPU time.

### Aging Mechanism
Aging solves the starvation problem by gradually increasing the priority of processes that have been waiting for a long time, ensuring all processes eventually get CPU time.

## 📝 Project Requirements

### Part 1: Basic Priority Scheduler (60 points)

Implement a priority-based scheduler that:

#### 1. Add Priority Field to Process Structure
- [ ] Modify `struct proc` in `proc.h` to include priority information
- [ ] Priority range: 0-10 (higher number = higher priority)
- [ ] Default priority: 5

#### 2. Modify the Scheduler Function
- [ ] Change `scheduler()` in `proc.c` to select the highest-priority runnable process
- [ ] Maintain safety with proper locking mechanisms

#### 3. Implement Priority Management System Calls
- [ ] `int setpriority(int pid, int priority)`: Set process priority
- [ ] `int getpriority(int pid)`: Get current process priority
- [ ] Add complete system call interface (syscall numbers, handlers, user stubs)

#### 4. Priority Inheritance
- [ ] Child processes inherit the parent's priority in `fork()`
- [ ] Proper initialization in `allocproc()`

### Part 2: Aging Mechanism (30 points)

Implement aging to prevent starvation:

#### 1. Add Aging Fields
- [ ] `base_priority`: Original priority for reset after running
- [ ] `wait_time`: Time spent waiting (in scheduler ticks)

#### 2. Aging Algorithm
- [ ] Increment priority every `X`, e.g., 10, scheduler ticks of waiting
- [ ] Maximum priority cap at 10
- [ ] Reset priority to base priority when process runs

#### 3. Aging Integration
- [ ] Modify scheduler to apply aging before process selection
- [ ] Ensure atomic operations with proper locking

### Part 3: Testing and Validation 

#### 1. Create/Modify Test Program
Use and modify the [priority_test.c](source/priority_test.c) program that
- [ ] Creates multiple processes with different priorities
- [ ] CPU-intensive workloads to demonstrate scheduling behaviour
- [ ] Periodic priority reporting to show aging effects

#### 2. Demonstrate Functionality (10 points)
Create a 5-minute video presentation that:
- [ ] Show that higher priority processes get preference
- [ ] Show that aging prevents starvation of low-priority processes
- [ ] Validate that all processes eventually complete

## 🛠️ Implementation Guidelines

### Files to Modify

| File | Purpose | Key Changes |
|------|---------|-------------|
| `proc.h` | Process structure | Add priority and aging fields |
| `proc.c` | Core scheduler logic | Modify scheduler, add priority functions |
| `syscall.h` | System call numbers | Add new syscall constants |
| `syscall.c` | System call table | Register new system calls |
| `sysproc.c` | System call handlers | Implement syscall wrappers |
| `usys.S` | User syscall stubs | Add assembly stubs |
| `user.h` | User function declarations | Add function prototypes |
| `defs.h` | Kernel function declarations | Add kernel function prototypes |

### 🔒 Safety Considerations

- ⚠️ Always acquire `ptable.lock` before modifying process state
- ⚠️ Use `argint()` for safe parameter extraction in system calls
- ⚠️ Validate priority ranges (0-10) in `setpriority()`
- ⚠️ Handle error cases gracefully (process not found, invalid parameters)

### 🔄 Aging Algorithm Details

```c
// Pseudocode for aging in scheduler
for each runnable process p:
    p->wait_time++
    if (p->wait_time >= 10 && p->priority < 10):
        p->priority++
        p->wait_time = 0

// When process is selected to run:
p->priority = p->base_priority
p->wait_time = 0
```

## 🧪 Testing Strategy

### Test Cases to Implement

1. **Basic Priority Test**
   - Create processes with different priorities
   - Verify higher priority processes run first

2. **Aging Effectiveness Test**
   - Create high and low priority processes
   - Verify that the low-priority processes eventually run due to aging

3. **System Call Validation**
   - Test `setpriority()` and `getpriority()` with various inputs
   - Verify error handling for invalid PIDs and priorities

There is a sample test program in the source folder, `priority_test.c`, that you can use/modify for testing purposes.

## 📚 Resources and References

- [xv6 Book](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
- Operating System Concepts (Silberschatz, Galvin, Gagne) - Chapter 5: CPU Scheduling
- Linux kernel scheduler documentation for real-world examples

## 🚀 Getting Started

1. **Familiarize yourself with the existing scheduler** in `proc.c`
2. **Start with Part 1** - implement basic priority scheduling
3. **Test frequently** with simple programs
4. **Add aging mechanism** in Part 2
5. **Create comprehensive tests** in Part 3

**Good luck with your implementation! Remember that operating systems programming requires patience, careful debugging, and attention to detail. Start early and test frequently!** 💻✨

## 🎓 Academic Integrity

**⚠️ Important**: This is an individual project. While you may discuss concepts with classmates, all code must be your own work. Copying code from online sources or other students will result in academic penalties.
Vibe coding is allowed and encouraged.

## 📤 Deliverables and Submission Instructions
You need to submit two files:
1. **Code Submission**: Zip the whole xv6-public folder, including all your modifications and test programs, and submit as `xv6-public.zip`.
2. **Demo Video**: A 5-minute video (e.g., Zoom with screen capture and Camera) explaining your code and showcasing your scheduler in action.

**Instructor:** Hamzeh Khazaei
