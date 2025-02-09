# Philosophers - Dining Philosophers Problem

An implementation of the classic dining philosophers problem using threads and mutexes (mandatory part) and processes and semaphores (bonus part).

## 🎯 Project Overview

Simulation of the dining philosophers problem where philosophers must eat, sleep, and think without starving, using different synchronization primitives.

## 🔄 Problem Description

N philosophers sit at a round table doing one of three things:
- Eating (requires two forks)
- Sleeping
- Thinking

Rules:
- Philosophers need 2 forks to eat
- Cannot take fork from philosopher who is eating
- Must prevent philosophers from starving
- Each philosopher must eat a specified number of times
- Program stops if a philosopher dies from starvation

## 📁 Project Structure

### Mandatory Implementation (Threads & Mutexes)
```
philo/
├── Makefile
├── philo.c              # Main program
├── philo.h              # Header file
├── init.c               # Initialization
├── parsing.c            # Argument parsing
├── simulation.c         # Core simulation
├── detached_thread.c    # Thread monitoring
├── struct_utils.c       # Data structure handling
└── ft_atoi.c           # Number conversion
```

### Bonus Implementation (Processes & Semaphores)
```
philo_bonus/
├── Makefile
├── philo_bonus.c        # Main bonus program
├── philo_bonus.h        # Bonus header
├── init.c              # Process initialization
├── parsing.c           # Argument handling
├── simulation.c        # Bonus simulation
├── detached_thread.c   # Process monitoring
├── struct_utils.c      # Structure management
├── aux_utils.c         # Helper functions
└── ft_atoi.c          # Number conversion
```

## 🛠️ Usage

### Compilation
```bash
cd philo && make        # Compile mandatory
cd philo_bonus && make  # Compile bonus
```

### Running
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200 7
```

## ⚙️ Parameters

1. `number_of_philosophers`: Number of philosophers and forks
2. `time_to_die`: Time (ms) philosopher can survive without eating
3. `time_to_eat`: Time (ms) it takes to eat
4. `time_to_sleep`: Time (ms) philosopher spends sleeping
5. `[number_of_times_each_philosopher_must_eat]`: Optional parameter

## 🔄 Implementation Details

### Mandatory Part (Threads)
- One thread per philosopher
- Mutex per fork
- Mutex for writing status
- Death checking mechanism
- Resource sharing protection

### Bonus Part (Processes)
- One process per philosopher
- Semaphores for forks
- Semaphore for writing
- Shared memory handling
- Process synchronization

## 🧪 Testing Scenarios

### Basic Tests
```bash
./philo 1 800 200 200    # One philosopher
./philo 5 800 200 200    # Basic case
./philo 4 410 200 200    # Death timing
```

### Edge Cases
```bash
./philo 200 800 200 200  # Large number of philosophers
./philo 5 800 200 200 7  # Limited number of meals
```

## ⚠️ Error Handling

- Invalid arguments
- Memory allocation failures
- Thread/Process creation failures
- Mutex/Semaphore initialization errors
- Resource cleanup
- Process termination

## 🔍 Synchronization Features

- Data race prevention
- Deadlock prevention
- Starvation handling
- Resource allocation fairness
- Death detection

## 📊 Performance Considerations

- Minimal CPU usage
- Efficient resource sharing
- Reduced context switching
- Optimal timing management
- Memory efficiency

## 📜 License

This project is part of the 42 curriculum and is provided as-is.
