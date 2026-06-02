# Galactic Cargo Management System (GCMS)

The Galactic Cargo Management System (GCMS) is a C++ implementation designed for efficient interstellar logistics and inventory management. This system provides a robust framework for managing cargo across distributed storage bins using advanced data structures to ensure high performance and scalability.

## Overview

The primary objective of GCMS is to optimize the allocation of cargo objects to storage bins based on various capacity and sorting requirements. The system utilizes balanced AVL trees to maintain logarithmic time complexity for insertion, deletion, and search operations.

### Key Protocols

The system implements four distinct bin selection protocols to accommodate different storage strategies:

- Blue Protocol (Compact Least): Selects the bin with the minimum sufficient capacity.
- Yellow Protocol (Compact Greatest): Selects the bin with the maximum sufficient capacity among those with the same capacity.
- Red Protocol (Largest Least): Selects the bin with the overall maximum capacity, prioritizing the smallest ID in case of ties.
- Green Protocol (Largest Greatest): Selects the bin with the overall maximum capacity, prioritizing the largest ID in case of ties.

## Technical Implementation

### Data Structures
- AVL Trees: Custom template implementation providing self-balancing binary search trees.
- Shared Memory Management: Utilization of `std::shared_ptr` to ensure data consistency and automatic memory management across multiple tree representations of bin data.

### Project Structure
- GCMS.h/cpp: Orchestrates the core logic and manages the primary indices for bins and objects.
- Bin.h/cpp: Defines storage bin entities and their internal object management.
- Object.h: Represents cargo entities with associated metadata.
- AVLTree.h: Provides a generic, thread-safe (via shared pointers) implementation of the AVL data structure.
- Exceptions.h: Standardized error handling for capacity and search failures.

## Build and Execution

### Prerequisites
- A C++ compiler supporting C++11 or higher (e.g., g++).

### Compilation
To compile the project and its test suite, execute the following command:

```bash
g++ -o gcms_control main.cpp Bin.cpp GCMS.cpp -I.
```

### Execution
To run the compiled binary:

```bash
./gcms_control
```

## Testing
The included `main.cpp` contains a comprehensive test suite designed to validate the system's compliance with the defined cargo management protocols and capacity constraints.
