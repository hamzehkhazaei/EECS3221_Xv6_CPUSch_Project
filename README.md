# Project 2: Process Scheduler Enhancement

## Overview

This project involves replacing Xv6's default round-robin scheduler with a more sophisticated scheduling algorithm. Students will implement either a priority-based scheduler or a multilevel feedback queue (MLFQ) scheduler, incorporating advanced features like priority aging and comprehensive scheduler statistics.

## Objectives

By completing this project, students will:

- Gain a deep understanding of process scheduling algorithms and their trade-offs
- Learn to work with complex kernel data structures and synchronization primitives
- Understand the intricacies of context switching and process state management
- Implement priority-based scheduling with starvation prevention mechanisms
- Develop skills in kernel-level programming and debugging

## Project Requirements

### Core Implementation

#### 1. Scheduler Algorithm Selection
Choose and implement one of the following scheduling algorithms:

**Priority-Based Scheduler**
- Assign priority levels to processes (e.g., 0-31, where 0 is highest priority)
- Schedule the highest priority ready process first
- Handle priority inheritance and inversion scenarios

**Multilevel Feedback Queue (MLFQ)**
- Implement multiple priority queues with different time quantum sizes
- Automatically adjust process priorities based on behaviour
- Provide interactive processes with higher priority

#### 2. Priority Assignment Mechanism
- Implement system calls for setting and getting process priorities
- Support both user-level and kernel-level priority assignment
- Ensure proper validation of priority values

#### 3. Aging Implementation
- Prevent priority inversion and starvation
- Gradually increase the priority of processes that haven't run recently
- Implement configurable aging parameters

#### 4. Scheduler Statistics
Track and report the following metrics:
- Average turnaround time per process
- Average waiting time per process
- CPU utilization percentage
- Context switch frequency
- Priority distribution of scheduled processes

## Technical Specifications

### Modified Files
- `proc.c` - Core process management and scheduling logic
- `proc.h` - Process structure definitions and scheduler interface
- `syscall.c` - System call implementations
- `syscall.h` - System call declarations
- `sysproc.c` - Process-related system calls
- `user.h` - User-space interface definitions

### New System Calls
```c
int setpriority(int pid, int priority);    // Set process priority
int getpriority(int pid);                  // Get process priority
int schedstats(struct schedstat *stats);   // Retrieve scheduler statistics
```

### Data Structures
```c
struct proc {
    // Existing fields...
    int priority;           // Process priority (0 = highest)
    int nice;              // Nice value for priority calculation
    uint ticks_scheduled;  // Total CPU time received
    uint last_scheduled;   // Last time process was scheduled
    uint wait_time;        // Time spent in ready queue
    // Additional scheduler-specific fields...
};

struct schedstat {
    uint total_processes;
    uint context_switches;
    uint avg_turnaround_time;
    uint avg_waiting_time;
    uint cpu_utilization;
};
```

## Implementation Guidelines

### Phase 1: Basic Priority Scheduler
1. Modify the `proc` structure to include priority fields
2. Implement priority-based process selection in `scheduler()`
3. Add system calls for priority management
4. Test with simple priority assignments

### Phase 2: Aging Mechanism
1. Implement an aging algorithm to prevent starvation
2. Add timer-based priority adjustments
3. Configure aging parameters (increment rate, maximum boost)
4. Validate aging effectiveness with long-running processes

### Phase 3: Statistics Collection
1. Add statistical counters to relevant kernel structures
2. Implement statistics collection during context switches
3. Create user-space utilities to display scheduler metrics
4. Verify the accuracy of collected statistics

### Phase 4: Testing and Optimization
1. Create a comprehensive test suite covering edge cases
2. Benchmark performance against the original round-robin scheduler
3. Optimize critical paths in scheduler code
4. Document performance characteristics and trade-offs

## Testing Strategy

### Unit Tests
- Priority assignment and retrieval
- Aging mechanism functionality
- Statistics accuracy
- System call parameter validation

### Integration Tests
- Multi-process scheduling behaviour
- Starvation prevention effectiveness
- Performance under various workloads
- Stress testing with many processes

### Performance Benchmarks
- CPU-bound workload scheduling
- I/O-intensive process handling
- Mixed workload scenarios
- Scheduler overhead measurement

## Deliverables

1. **Source Code**: Complete implementation with clear documentation
2. **Test Suite**: Comprehensive tests validating scheduler behavior
3. **Performance Analysis**: Benchmarks comparing new scheduler with original
4. **Design Document**: Detailed explanation of implementation choices
5. **User Manual**: Instructions for using new scheduler features

## Evaluation Criteria

- **Correctness** (40%): Proper implementation of chosen scheduling algorithm
- **Completeness** (25%): All required features implemented and working
- **Performance** (20%): Efficient implementation with minimal overhead
- **Code Quality** (10%): Clean, well-documented, maintainable code
- **Testing** (5%): Thorough test coverage and validation

## Resources

- Xv6 source code and documentation
- Operating Systems: Three Easy Pieces (OSTEP) - Scheduling chapters
- Advanced Programming in the UNIX Environment
- GDB debugging guide for kernel development

## Getting Started

1. Study the existing scheduler implementation in `proc.c`
2. Design your scheduler algorithm and data structures
3. Implement incrementally, testing each component thoroughly
4. Document your design decisions and trade-offs

## Submission Guidelines

Submit your project as a zip file containing:
- Modified Xv6 source code with your scheduler implementation
- Test programs demonstrating scheduler functionality
- README with build and usage instructions
- Performance analysis report
- Any additional documentation or design notes

---

**Note**: This project requires significant experience with kernel programming. Start early, test frequently, and don't hesitate to seek help when debugging kernel-level issues.

***Instructor:*** Hamzeh Khazaei
