# Project 2: Priority CPU Scheduling

## 📋 Overview

In this project, you will implement a priority-based process scheduler with an aging mechanism in the Xv6 operating system. This will replace the default round-robin scheduler with a more sophisticated scheduling algorithm that prevents starvation while maintaining priority-based execution order.

## 🎯 Learning Objectives

By completing this project, you will:
- ✅ Understand process scheduling algorithms and their trade-offs
- ✅ Learn how to modify kernel data structures and system calls
- ✅ Implement aging mechanisms to prevent starvation
- ✅ Gain hands-on experience with operating system internals
- ✅ Practice safe kernel programming and memory management

## 📚 Background

### Current Xv6 Scheduler
The default xv6 scheduler uses a simple FIFO (First In, First Out) algorithm that runs processes in the order they become runnable. It scans the process table from the beginning and runs the first runnable process it finds until that process voluntarily yields, blocks, or exits. This is essentially a round-robin scheduler with infinite quantum time - there's no preemptive time slicing, so processes run until they give up the CPU voluntarily. This approach is simple but doesn't allow for prioritizing critical processes or ensuring fair time distribution.ty-Based Scheduler with Aging in Xv6.

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
- [ ] Change `scheduler()` in `proc.c` to select highest-priority runnable process
- [ ] Maintain safety with proper locking mechanisms

#### 3. Implement Priority Management System Calls
- [ ] `int setpriority(int pid, int priority)`: Set process priority
- [ ] `int getpriority(int pid)`: Get current process priority
- [ ] Add complete system call interface (syscall numbers, handlers, user stubs)

#### 4. Priority Inheritance
- [ ] Child processes inherit parent's priority in `fork()`
- [ ] Proper initialization in `allocproc()`

### Part 2: Aging Mechanism (30 points)

Implement aging to prevent starvation:

#### 1. Add Aging Fields
- [ ] `base_priority`: Original priority for reset after running
- [ ] `wait_time`: Time spent waiting (in scheduler ticks)

#### 2. Aging Algorithm
- [ ] Increment priority every 10 scheduler ticks of waiting
- [ ] Maximum priority cap at 10
- [ ] Reset priority to base priority when process runs

#### 3. Aging Integration
- [ ] Modify scheduler to apply aging before process selection
- [ ] Ensure atomic operations with proper locking

### Part 3: Testing and Validation (10 points)

#### 1. Create Test Program
- [ ] Program that creates multiple processes with different priorities
- [ ] CPU-intensive workloads to demonstrate scheduling behavior
- [ ] Periodic priority reporting to show aging effects

#### 2. Demonstrate Functionality
- [ ] Prove that higher priority processes get preference
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
   - Verify low priority processes eventually run due to aging

3. **System Call Validation**
   - Test `setpriority()` and `getpriority()` with various inputs
   - Verify error handling for invalid PIDs and priorities

4. **Stress Testing**
   - Multiple processes with same priority
   - Rapid priority changes
   - Process creation/termination during scheduling

### Expected Output Example

```
Priority Scheduler Test with Aging
===================================
Child 1 (PID 4, Priority 8): Starting CPU-intensive task
Child 2 (PID 5, Priority 5): Starting CPU-intensive task  
Child 3 (PID 6, Priority 2): Starting CPU-intensive task

Child 1 (High Priority): 0 iterations, current priority: 8
Child 1 (High Priority): 400000 iterations, current priority: 8
Child 2 (Medium Priority): 0 iterations, current priority: 5
Child 3 (Low Priority): 0 iterations, current priority: 3  // aged!
...
All processes finished - aging prevented starvation!
```

## 📦 Deliverables

1. **Source Code** (80%)
   - All modified Xv6 files with clear, commented code
   - Compilation without warnings or errors
   - Proper coding style and formatting

2. **Test Program** (10%)
   - Comprehensive test demonstrating all features
   - Clear output showing scheduler behavior
   - Test cases covering edge cases

3. **Project Report** (10%)
   - Design decisions and implementation details
   - Analysis of scheduler performance and behavior
   - Discussion of challenges and solutions
   - Screenshots/logs of test execution

## 📊 Grading Rubric

| Component | Excellent (A) | Good (B) | Satisfactory (C) | Needs Improvement (D/F) |
|-----------|---------------|----------|------------------|-------------------------|
| **Basic Priority Scheduler** | Fully functional, efficient, safe | Minor issues, mostly working | Basic functionality, some bugs | Major problems, doesn't compile |
| **Aging Mechanism** | Perfect aging, no starvation | Aging works, minor edge cases | Basic aging implementation | Aging broken or missing |
| **System Calls** | Complete interface, proper error handling | Minor syscall issues | Basic syscalls work | Syscalls broken/incomplete |
| **Testing** | Comprehensive tests, clear demonstration | Good test coverage | Basic testing | Inadequate testing |
| **Code Quality** | Clean, well-documented, efficient | Minor style/documentation issues | Acceptable code quality | Poor code quality |

## 🎖️ Bonus Opportunities (+10 points each)

1. **Multi-level Priority Queues**: Implement separate queues for different priority levels
2. **Dynamic Priority Adjustment**: Implement CPU burst-based priority adjustment
3. **Process Niceness**: Add user-controllable process niceness levels
4. **Scheduler Statistics**: Implement detailed scheduling statistics and reporting

## 📚 Resources and References

- [Xv6 Book](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
- Operating System Concepts (Silberschatz, Galvin, Gagne) - Chapter 5: CPU Scheduling
- Linux kernel scheduler documentation for real-world examples

## 📤 Submission Instructions

1. **Code Submission**: Submit all modified Xv6 files in a compressed archive
2. **Report**: PDF document (max 10 pages) with analysis and screenshots
3. **Demo Video**: 5-minute video demonstrating your scheduler in action
4. **Due Date**: [Insert your due date]
5. **Late Policy**: [Insert your late policy]

## 🎓 Academic Integrity

> **⚠️ Important**: This is an individual project. While you may discuss concepts with classmates, all code must be your own work. Copying code from online sources or other students will result in academic penalties.

---

## 🚀 Getting Started

1. **Clone the Xv6 repository**
2. **Familiarize yourself with the existing scheduler** in `proc.c`
3. **Start with Part 1** - implement basic priority scheduling
4. **Test frequently** with simple programs
5. **Add aging mechanism** in Part 2
6. **Create comprehensive tests** in Part 3

**Good luck with your implementation! Remember that operating systems programming requires patience, careful debugging, and attention to detail. Start early and test frequently!** 💻✨

---

### 📞 Help and Support

- **Office Hours**: [Insert your office hours]
- **Discussion Forum**: [Insert forum link]
- **Email**: [Insert your email]

### 🏷️ Tags
`#operating-systems` `#Xv6` `#scheduler` `#kernel-programming` `#system-calls`
