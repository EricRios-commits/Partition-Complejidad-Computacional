# Partition-Complejidad-Computacional - Complete Code Documentation

## Table of Contents
1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Core Classes](#core-classes)
4. [Interface Layer](#interface-layer)
5. [I/O Components](#io-components)
6. [Solver Components](#solver-components)
7. [Reduction Components](#reduction-components)
8. [Pipeline Orchestration](#pipeline-orchestration)
9. [Class Diagram](#class-diagram)
10. [Usage Examples](#usage-examples)

---

## Overview

This project implements a **polynomial-time reduction** from the **3-Dimensional Matching (3DM) problem** to the **Partition problem**, demonstrating concepts from computational complexity theory. The codebase showcases how NP-complete problems can be reduced to one another, maintaining solution equivalence.

### Key Problems

#### 3-Dimensional Matching (3DM)
- **Input**: Three disjoint sets W, X, Y (each of size q) and a set of triples M ⊆ W × X × Y
- **Question**: Does there exist a perfect matching M' ⊆ M such that each element in W, X, Y appears exactly once?
- **Complexity**: NP-complete

#### Partition Problem
- **Input**: A set A of elements with positive integer sizes
- **Question**: Can A be partitioned into two subsets A' and A'' such that the sum of sizes in A' equals the sum in A''?
- **Complexity**: NP-complete

---

## Architecture

The project follows **SOLID principles** with a clean, modular architecture:

```
Core Layer          → Data structures (PartitionElement, Triple, etc.)
Interface Layer     → Abstract interfaces defining contracts
I/O Layer          → File reading and writing implementations
Solver Layer       → Algorithm implementations
Reduction Layer    → Problem transformation logic
Pipeline Layer     → Orchestration and workflow management
```

### Design Patterns Used
- **Strategy Pattern**: Interchangeable reduction and solving algorithms
- **Template Method**: Generic interfaces for readers, writers, and solvers
- **Factory Pattern**: Algorithm selection in PartitionSolver
- **Facade Pattern**: ReductionPipeline simplifies complex workflows

---

## Core Classes

### 1. PartitionElement

**Purpose**: Represents a single element in a Partition problem instance.

**Attributes**:
- `id_` (string): Unique identifier for the element
- `size_` (int64_t): The numeric size/weight of the element

**Key Methods**:
```cpp
PartitionElement(const std::string& id, int64_t size)  // Constructor
id() const -> const std::string&                        // Get ID
size() const -> int64_t                                 // Get size
operator==(const PartitionElement& other) const        // Equality comparison
ToString() const -> std::string                         // String representation
```

**Design Notes**:
- Immutable after construction (getters only)
- Equality based on both id and size
- Used as building blocks for PartitionInstance

---

### 2. PartitionInstance

**Purpose**: Represents a complete Partition problem instance containing multiple elements.

**Attributes**:
- `elements_` (vector<PartitionElement>): Collection of all elements
- `total_sum_` (int64_t): Cached sum of all element sizes

**Key Methods**:
```cpp
AddElement(const PartitionElement& element)           // Add single element
SetElements(const vector<PartitionElement>& elements) // Set all elements at once
elements() const -> const vector<PartitionElement>&   // Get all elements
total_sum() const -> int64_t                          // Get total sum
IsValid() const -> bool                               // Check instance validity
IsValidPartition(const set<string>& subset_ids) const // Verify a proposed solution
```

**Validation Rules**:
- `IsValid()`: Checks if total_sum is positive and even (necessary for partition)
- `IsValidPartition()`: Verifies that subset sums to exactly half of total_sum

**Invariants**:
- `total_sum_` is always kept up-to-date via `RecalculateTotalSum()`
- Element IDs must be unique within the instance

---

### 3. Triple

**Purpose**: Represents a single triple (w, x, y) from a 3DM instance.

**Attributes**:
- `w_` (string): Element from set W
- `x_` (string): Element from set X
- `y_` (string): Element from set Y

**Key Methods**:
```cpp
Triple(const std::string& w, const std::string& x, const std::string& y)
w() const -> const std::string&                    // Get W coordinate
x() const -> const std::string&                    // Get X coordinate
y() const -> const std::string&                    // Get Y coordinate
SharesCoordinateWith(const Triple& other) const    // Check for coordinate overlap
operator==(const Triple& other) const              // Equality comparison
```

**Special Features**:
- **Hash struct**: Enables use in unordered containers (hash maps, hash sets)
- `SharesCoordinateWith()`: Critical for checking if two triples conflict in a matching
- Immutable design ensures thread safety

---

### 4. ThreeDMInstance

**Purpose**: Represents a complete 3-Dimensional Matching problem instance.

**Attributes**:
- `w_` (set<string>): Set W elements
- `x_` (set<string>): Set X elements
- `y_` (set<string>): Set Y elements
- `m_` (vector<Triple>): Available triples
- `q_` (size_t): Size of each set (|W| = |X| = |Y| = q)

**Key Methods**:
```cpp
SetW(const set<string>& w)                           // Set W elements
SetX(const set<string>& x)                           // Set X elements
SetY(const set<string>& y)                           // Set Y elements
AddTriple(const Triple& triple)                      // Add a single triple
SetTriples(const vector<Triple>& triples)            // Set all triples
IsValid() const -> bool                              // Validate instance structure
IsValidMatching(const vector<Triple>& matching) const // Verify a solution
```

**Validation Rules**:
- `IsValid()`: Ensures |W| = |X| = |Y| = q
- `IsValidMatching()`: Checks that:
  - Matching has exactly q triples
  - No element appears more than once
  - All triples are from the original set M

---

## Interface Layer

### 1. InstanceReader<T>

**Purpose**: Abstract interface for reading problem instances from files or streams.

**Template Parameter**: `T` - The type of instance to read (ThreeDMInstance, PartitionInstance)

**Pure Virtual Methods**:
```cpp
ReadFromFile(const string& filename) const -> T = 0
ReadFromStream(istream& input) const -> T = 0
GetFormatDescription() const -> string = 0
```

**Benefits**:
- Enables polymorphic file reading
- Supports both file and stream input (flexibility)
- Decouples parsing logic from problem domain

---

### 2. InstanceWriter<T>

**Purpose**: Abstract interface for writing problem instances to files or streams.

**Template Parameter**: `T` - The type of instance to write

**Pure Virtual Methods**:
```cpp
WriteToFile(const T& instance, const string& filename) const -> void = 0
WriteToStream(const T& instance, ostream& output) const -> void = 0
GetFormatDescription() const -> string = 0
```

**Benefits**:
- Symmetric with InstanceReader
- Supports serialization to files or memory streams
- Facilitates testing with string streams

---

### 3. InstanceSolver<Instance, Solution>

**Purpose**: Generic interface for solving problem instances.

**Template Parameters**:
- `Instance`: Problem instance type
- `Solution`: Solution type

**Pure Virtual Methods**:
```cpp
Solve(const Instance& instance) -> optional<Solution> = 0
GetAlgorithmName() const -> string = 0
```

**Design Choice**: Returns `std::optional<Solution>` to handle unsolvable instances gracefully.

---

### 4. ReductionStrategy

**Purpose**: Interface for reducing one problem to another.

**Pure Virtual Methods**:
```cpp
Reduce(const ThreeDMInstance& three_dm) const -> PartitionInstance = 0
MapSolutionBack(const set<string>& partition_solution, 
                const ThreeDMInstance& original_instance) const -> vector<Triple> = 0
GetDescription() const -> string = 0
```

**Key Concept**: Bidirectional transformation
1. **Forward reduction**: 3DM → Partition
2. **Solution mapping**: Partition solution → 3DM solution

---

## I/O Components

### 1. PartitionReader

**File Format**:
```
n
id1 size1
id2 size2
...
idn sizen
```

**Example**:
```
4
a 10
b 20
c 15
d 15
```

**Implementation**: Reads line by line, validates format, constructs PartitionInstance.

---

### 2. PartitionWriter

**Output Format**: Same as PartitionReader input format (symmetry).

**Features**:
- Validates instance before writing
- Formats output for human readability
- Handles error conditions gracefully

---

### 3. ThreeDMReader

**File Format**:
```
q
w1 w2 ... wq
x1 x2 ... xq
y1 y2 ... yq
w1 x1 y1
w2 x2 y2
...
```

**Example**:
```
2
w1 w2
x1 x2
y1 y2
w1 x1 y1
w2 x2 y2
```

**Parsing Strategy**:
1. Read q
2. Parse space-separated elements for W, X, Y
3. Read triples one per line
4. Validate all triples reference existing elements

---

### 4. ThreeDMWriter

**Output Format**: Mirrors ThreeDMReader input format.

**Quality Checks**:
- Validates instance structure before writing
- Ensures all triple coordinates exist in W, X, Y
- Provides clear error messages

---

## Solver Components

### 1. PartitionSolver

**Purpose**: Solves Partition problem instances using multiple algorithms.

**Algorithms Available**:

#### A. Dynamic Programming (kDynamicProgramming)
```cpp
SolveDynamicProgramming(const PartitionInstance& instance)
```
- **Approach**: Classic DP table for subset sum
- **Time Complexity**: O(n × S) where S = total_sum/2
- **Space Complexity**: O(S)
- **Optimal**: Yes, finds solution if one exists
- **Best For**: Instances with moderate sums

**Algorithm Overview**:
1. Create boolean DP table `dp[sum]`
2. `dp[i]` = true if sum `i` can be achieved
3. For each element, update table backwards
4. Backtrack to reconstruct solution

#### B. Backtracking (kBacktracking)
```cpp
SolveBacktracking(const PartitionInstance& instance)
BacktrackHelper(instance, index, current_sum, target_sum, current_subset)
```
- **Approach**: Recursive depth-first search
- **Time Complexity**: O(2^n) worst case
- **Space Complexity**: O(n) stack depth
- **Optimal**: Yes, exhaustive search
- **Best For**: Small instances (n < 25)

**Pruning Optimizations**:
- Stops when target_sum reached
- Early termination if current_sum exceeds target

#### C. Greedy Heuristic (kGreedyHeuristic)
```cpp
SolveGreedy(const PartitionInstance& instance)
```
- **Approach**: Greedily add elements to smaller subset
- **Time Complexity**: O(n log n)
- **Space Complexity**: O(n)
- **Optimal**: NO - approximation algorithm
- **Best For**: Quick approximate solutions, large instances

**Greedy Strategy**:
1. Sort elements by size (descending)
2. Always add next element to lighter subset
3. Check if final partition is perfect

---

### 2. SolutionVerifier

**Purpose**: Validates solutions for both problem types.

**Static Methods**:

#### For 3DM Solutions:
```cpp
static Verify3DMSolution(const ThreeDMInstance& instance, 
                         const vector<Triple>& matching) -> bool
```
**Checks**:
1. Matching has exactly q triples
2. Each element in W, X, Y appears exactly once
3. All triples exist in original instance M

```cpp
static Get3DMVerificationReport(const ThreeDMInstance& instance,
                                const vector<Triple>& matching) -> string
```
**Returns**: Detailed report with counts and violations

#### For Partition Solutions:
```cpp
static VerifyPartitionSolution(const PartitionInstance& instance,
                               const set<string>& subset) -> bool
```
**Checks**:
1. All element IDs in subset exist in instance
2. Subset sum equals complement sum (perfect partition)

```cpp
static GetPartitionVerificationReport(const PartitionInstance& instance,
                                      const set<string>& subset) -> string
```
**Returns**: Report with subset sums and balance status

---

## Reduction Components

### 1. ThreeDMToPartitionReducer

**Purpose**: Implements the polynomial-time reduction from 3DM to Partition.

**Reduction Strategy**:

#### Step 1: Assign Unique Weights
Each element gets a unique weight based on position and dimension:

```cpp
CalculateWeight(size_t index, size_t dimension) const -> int64_t
```

Formula: `weight = base_weight + dimension * q + index`

**Example** (q=2, base_weight=1000):
- W: w1→1000, w2→1001
- X: x1→1002, x2→1003  
- Y: y1→1004, y2→1005

#### Step 2: Create Partition Elements
Each triple becomes a partition element with size = sum of coordinate weights:

```cpp
CalculateTripleSize(const Triple& triple, ...) const -> int64_t
```

For triple (w1, x1, y1): size = 1000 + 1002 + 1004 = 3006

#### Step 3: Add Filler Elements
Additional elements ensure the target sum is achievable and maintains the reduction's correctness.

#### Solution Mapping
```cpp
MapSolutionBack(const set<string>& partition_solution,
                const ThreeDMInstance& original_instance) const -> vector<Triple>
```

**Process**:
1. Filter partition solution to only triple elements (ignore fillers)
2. Use `element_to_triple_map_` to recover original triples
3. Return vector of selected triples

**Correctness Guarantee**:
- 3DM has perfect matching ⟺ Partition has perfect partition
- Solution mappings preserve validity

---

### 2. ReductionValidator

**Purpose**: Validates the correctness of reductions and solution mappings.

**Static Methods**:

#### Validate Reduction Structure
```cpp
static ValidateReduction(const ReductionStrategy& strategy,
                        const ThreeDMInstance& three_dm,
                        const PartitionInstance& partition) -> bool
```

**Checks**:
- Partition instance is structurally valid
- Element count matches expectations
- Total sum is even (necessary for partition)

#### Validate Solution Mapping
```cpp
static ValidateSolutionMapping(const ReductionStrategy& strategy,
                               const set<string>& partition_solution,
                               const vector<Triple>& three_dm_solution,
                               const ThreeDMInstance& original_instance) -> bool
```

**Verification Steps**:
1. Partition solution is valid for partition instance
2. 3DM solution is valid matching for original instance
3. Mapping preserves solution structure

#### Detailed Reporting
```cpp
static GetValidationReport(const ReductionStrategy& strategy,
                          const ThreeDMInstance& three_dm,
                          const PartitionInstance& partition) -> string
```

**Report Contents**:
- Instance sizes and properties
- Reduction statistics
- Validity checks with pass/fail status

---

## Pipeline Orchestration

### ReductionPipeline

**Purpose**: Orchestrates the complete end-to-end workflow.

**Architecture**: Dependency Injection pattern

**Constructor**:
```cpp
ReductionPipeline(
    shared_ptr<ReductionStrategy> reduction_strategy,
    shared_ptr<InstanceReader<ThreeDMInstance>> three_dm_reader,
    shared_ptr<InstanceWriter<PartitionInstance>> partition_writer,
    shared_ptr<InstanceSolver<PartitionInstance, set<string>>> partition_solver
)
```

**Benefits**:
- Loose coupling via interfaces
- Easy to swap implementations
- Testable with mock objects

---

**Main Workflow Method**:
```cpp
Execute(const string& three_dm_file, const string& partition_output_file) -> string
```

**Pipeline Steps**:

1. **Read** 3DM instance from file
   ```cpp
   ThreeDMInstance three_dm = three_dm_reader_->ReadFromFile(three_dm_file);
   ```

2. **Reduce** to Partition instance
   ```cpp
   PartitionInstance partition = reduction_strategy_->Reduce(three_dm);
   ```

3. **Write** Partition instance to file
   ```cpp
   partition_writer_->WriteToFile(partition, partition_output_file);
   ```

4. **Solve** Partition instance
   ```cpp
   optional<set<string>> partition_solution = partition_solver_->Solve(partition);
   ```

5. **Map back** to 3DM solution (if found)
   ```cpp
   if (partition_solution) {
       vector<Triple> three_dm_solution = 
           reduction_strategy_->MapSolutionBack(*partition_solution, three_dm);
   }
   ```

6. **Generate** comprehensive report
   ```cpp
   return GenerateReport(three_dm, partition, partition_solution, three_dm_solution);
   ```

---

**Partial Workflow Methods**:

```cpp
PerformReduction(const ThreeDMInstance& three_dm) -> PartitionInstance
```
- Executes only the reduction step
- Useful for analyzing reduction properties

```cpp
SolveAndMapBack(const PartitionInstance& partition,
                const ThreeDMInstance& original_three_dm) 
    -> optional<vector<Triple>>
```
- Solves partition and maps to 3DM solution
- Returns nullopt if no solution exists

---

**Report Generation**:
```cpp
GenerateReport(const ThreeDMInstance& three_dm,
               const PartitionInstance& partition,
               const optional<set<string>>& partition_solution,
               const optional<vector<Triple>>& three_dm_solution) -> string
```

**Report Sections**:
- Input statistics (sizes, element counts)
- Reduction information
- Solution status
- Timing information (if tracked)
- Verification results

---

## Class Diagram

```mermaid
classDiagram
    %% Core Classes
    class PartitionElement {
        -string id_
        -int64_t size_
        +PartitionElement(string id, int64_t size)
        +id() string
        +size() int64_t
        +operator==(PartitionElement) bool
        +operator!=(PartitionElement) bool
        +ToString() string
    }

    class PartitionInstance {
        -vector~PartitionElement~ elements_
        -int64_t total_sum_
        +PartitionInstance()
        +AddElement(PartitionElement) void
        +SetElements(vector~PartitionElement~) void
        +elements() vector~PartitionElement~
        +total_sum() int64_t
        +size() size_t
        +IsValid() bool
        +IsValidPartition(set~string~) bool
        +ToString() string
        -RecalculateTotalSum() void
    }

    class Triple {
        -string w_
        -string x_
        -string y_
        +Triple(string w, string x, string y)
        +w() string
        +x() string
        +y() string
        +SharesCoordinateWith(Triple) bool
        +operator==(Triple) bool
        +operator!=(Triple) bool
        +ToString() string
    }

    class TripleHash {
        <<struct>>
        +operator()(Triple) size_t
    }

    class ThreeDMInstance {
        -set~string~ w_
        -set~string~ x_
        -set~string~ y_
        -vector~Triple~ m_
        -size_t q_
        +ThreeDMInstance()
        +SetW(set~string~) void
        +SetX(set~string~) void
        +SetY(set~string~) void
        +AddTriple(Triple) void
        +SetTriples(vector~Triple~) void
        +w() set~string~
        +x() set~string~
        +y() set~string~
        +triples() vector~Triple~
        +q() size_t
        +IsValid() bool
        +IsValidMatching(vector~Triple~) bool
        +ToString() string
    }

    %% Interfaces
    class InstanceReader~T~ {
        <<interface>>
        +ReadFromFile(string) T*
        +ReadFromStream(istream) T*
        +GetFormatDescription() string*
    }

    class InstanceWriter~T~ {
        <<interface>>
        +WriteToFile(T, string) void*
        +WriteToStream(T, ostream) void*
        +GetFormatDescription() string*
    }

    class InstanceSolver~Instance, Solution~ {
        <<interface>>
        +Solve(Instance) optional~Solution~*
        +GetAlgorithmName() string*
    }

    class ReductionStrategy {
        <<interface>>
        +Reduce(ThreeDMInstance) PartitionInstance*
        +MapSolutionBack(set~string~, ThreeDMInstance) vector~Triple~*
        +GetDescription() string*
    }

    %% IO Classes
    class PartitionReader {
        +ReadFromFile(string) PartitionInstance
        +ReadFromStream(istream) PartitionInstance
        +GetFormatDescription() string
    }

    class PartitionWriter {
        +WriteToFile(PartitionInstance, string) void
        +WriteToStream(PartitionInstance, ostream) void
        +GetFormatDescription() string
    }

    class ThreeDMReader {
        +ReadFromFile(string) ThreeDMInstance
        +ReadFromStream(istream) ThreeDMInstance
        +GetFormatDescription() string
    }

    class ThreeDMWriter {
        +WriteToFile(ThreeDMInstance, string) void
        +WriteToStream(ThreeDMInstance, ostream) void
        +GetFormatDescription() string
    }

    %% Solvers
    class PartitionSolver {
        <<enumeration>> Algorithm
        -Algorithm algorithm_
        +PartitionSolver(Algorithm)
        +Solve(PartitionInstance) optional~set~string~~
        +GetAlgorithmName() string
        -SolveDynamicProgramming(PartitionInstance) optional~set~string~~
        -SolveBacktracking(PartitionInstance) optional~set~string~~
        -SolveGreedy(PartitionInstance) optional~set~string~~
        -BacktrackHelper(PartitionInstance, size_t, int64_t, int64_t, set~string~) bool
    }

    class SolutionVerifier {
        <<utility>>
        +Verify3DMSolution(ThreeDMInstance, vector~Triple~)$ bool
        +VerifyPartitionSolution(PartitionInstance, set~string~)$ bool
        +Get3DMVerificationReport(ThreeDMInstance, vector~Triple~)$ string
        +GetPartitionVerificationReport(PartitionInstance, set~string~)$ string
    }

    %% Reduction Classes
    class ThreeDMToPartitionReducer {
        -int64_t base_weight_
        -unordered_map~string, Triple~ element_to_triple_map_
        +ThreeDMToPartitionReducer(int64_t)
        +Reduce(ThreeDMInstance) PartitionInstance
        +MapSolutionBack(set~string~, ThreeDMInstance) vector~Triple~
        +GetDescription() string
        -CalculateWeight(size_t, size_t) int64_t
        -CalculateTripleSize(Triple, unordered_map, unordered_map, unordered_map) int64_t
        -CreateIndexMaps(ThreeDMInstance, unordered_map, unordered_map, unordered_map) void
    }

    class ReductionValidator {
        <<utility>>
        +ValidateReduction(ReductionStrategy, ThreeDMInstance, PartitionInstance)$ bool
        +ValidateSolutionMapping(ReductionStrategy, set~string~, vector~Triple~, ThreeDMInstance)$ bool
        +GetValidationReport(ReductionStrategy, ThreeDMInstance, PartitionInstance)$ string
    }

    %% Pipeline
    class ReductionPipeline {
        -shared_ptr~ReductionStrategy~ reduction_strategy_
        -shared_ptr~InstanceReader~ThreeDMInstance~~ three_dm_reader_
        -shared_ptr~InstanceWriter~PartitionInstance~~ partition_writer_
        -shared_ptr~InstanceSolver~PartitionInstance, set~string~~~ partition_solver_
        +ReductionPipeline(shared_ptr, shared_ptr, shared_ptr, shared_ptr)
        +Execute(string, string) string
        +PerformReduction(ThreeDMInstance) PartitionInstance
        +SolveAndMapBack(PartitionInstance, ThreeDMInstance) optional~vector~Triple~~
        -GenerateReport(ThreeDMInstance, PartitionInstance, optional, optional) string
    }

    %% Relationships - Core
    PartitionInstance "1" *-- "many" PartitionElement : contains
    ThreeDMInstance "1" *-- "many" Triple : contains
    Triple ..> TripleHash : uses

    %% Relationships - Interfaces
    InstanceReader~T~ <|.. PartitionReader : implements
    InstanceReader~T~ <|.. ThreeDMReader : implements
    InstanceWriter~T~ <|.. PartitionWriter : implements
    InstanceWriter~T~ <|.. ThreeDMWriter : implements
    InstanceSolver~Instance, Solution~ <|.. PartitionSolver : implements
    ReductionStrategy <|.. ThreeDMToPartitionReducer : implements

    %% Relationships - Dependencies
    PartitionReader ..> PartitionInstance : creates
    PartitionWriter ..> PartitionInstance : uses
    ThreeDMReader ..> ThreeDMInstance : creates
    ThreeDMWriter ..> ThreeDMInstance : uses
    PartitionSolver ..> PartitionInstance : uses
    ThreeDMToPartitionReducer ..> ThreeDMInstance : uses
    ThreeDMToPartitionReducer ..> PartitionInstance : creates
    ThreeDMToPartitionReducer ..> Triple : maps
    SolutionVerifier ..> ThreeDMInstance : verifies
    SolutionVerifier ..> PartitionInstance : verifies
    SolutionVerifier ..> Triple : uses
    ReductionValidator ..> ReductionStrategy : validates
    ReductionValidator ..> ThreeDMInstance : uses
    ReductionValidator ..> PartitionInstance : uses
    ReductionValidator ..> Triple : uses
    ReductionPipeline ..> ReductionStrategy : uses
    ReductionPipeline ..> ThreeDMInstance : uses
    ReductionPipeline ..> PartitionInstance : uses
    ReductionPipeline ..> Triple : uses
    ReductionPipeline "1" o-- "1" InstanceReader~ThreeDMInstance~ : uses
    ReductionPipeline "1" o-- "1" InstanceWriter~PartitionInstance~ : uses
    ReductionPipeline "1" o-- "1" InstanceSolver~PartitionInstance, set~string~~ : uses
```

---

## Usage Examples

### Example 1: Basic Pipeline Execution

```cpp
#include "ReductionPipeline.h"
#include "ThreeDMToPartitionReducer.h"
#include "ThreeDMReader.h"
#include "PartitionWriter.h"
#include "PartitionSolver.h"

using namespace partition;

int main() {
    // Create components
    auto reducer = std::make_shared<ThreeDMToPartitionReducer>();
    auto reader = std::make_shared<ThreeDMReader>();
    auto writer = std::make_shared<PartitionWriter>();
    auto solver = std::make_shared<PartitionSolver>(
        PartitionSolver::Algorithm::kDynamicProgramming
    );

    // Build pipeline
    ReductionPipeline pipeline(reducer, reader, writer, solver);

    // Execute complete workflow
    std::string report = pipeline.Execute(
        "input/3dm_instance.txt",
        "output/partition_instance.txt"
    );

    std::cout << report << std::endl;
    return 0;
}
```

---

### Example 2: Manual Step-by-Step Process

```cpp
#include "ThreeDMInstance.h"
#include "ThreeDMToPartitionReducer.h"
#include "PartitionSolver.h"
#include "SolutionVerifier.h"

using namespace partition;

int main() {
    // 1. Create 3DM instance manually
    ThreeDMInstance three_dm;
    three_dm.SetW({"w1", "w2"});
    three_dm.SetX({"x1", "x2"});
    three_dm.SetY({"y1", "y2"});
    three_dm.AddTriple(Triple("w1", "x1", "y1"));
    three_dm.AddTriple(Triple("w2", "x2", "y2"));
    three_dm.AddTriple(Triple("w1", "x2", "y1"));

    // 2. Perform reduction
    ThreeDMToPartitionReducer reducer;
    PartitionInstance partition = reducer.Reduce(three_dm);

    std::cout << "Partition instance: " << partition.ToString() << std::endl;

    // 3. Solve partition
    PartitionSolver solver(PartitionSolver::Algorithm::kBacktracking);
    auto partition_solution = solver.Solve(partition);

    if (partition_solution) {
        std::cout << "Partition solution found!" << std::endl;

        // 4. Map back to 3DM
        std::vector<Triple> matching = 
            reducer.MapSolutionBack(*partition_solution, three_dm);

        // 5. Verify 3DM solution
        bool valid = SolutionVerifier::Verify3DMSolution(three_dm, matching);
        std::cout << "3DM matching valid: " << (valid ? "YES" : "NO") << std::endl;

        // Print matching
        std::cout << "Matching:" << std::endl;
        for (const auto& triple : matching) {
            std::cout << "  " << triple.ToString() << std::endl;
        }
    } else {
        std::cout << "No solution exists" << std::endl;
    }

    return 0;
}
```

---

### Example 3: Algorithm Comparison

```cpp
#include "PartitionInstance.h"
#include "PartitionSolver.h"
#include <chrono>

using namespace partition;
using namespace std::chrono;

void compareAlgorithms(const PartitionInstance& instance) {
    std::vector<PartitionSolver::Algorithm> algorithms = {
        PartitionSolver::Algorithm::kDynamicProgramming,
        PartitionSolver::Algorithm::kBacktracking,
        PartitionSolver::Algorithm::kGreedyHeuristic
    };

    for (auto algo : algorithms) {
        PartitionSolver solver(algo);
        
        auto start = high_resolution_clock::now();
        auto solution = solver.Solve(instance);
        auto end = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(end - start);
        
        std::cout << solver.GetAlgorithmName() << ":\n";
        std::cout << "  Time: " << duration.count() << " ms\n";
        std::cout << "  Solution: " << (solution ? "FOUND" : "NOT FOUND") << "\n";
        
        if (solution) {
            bool valid = SolutionVerifier::VerifyPartitionSolution(
                instance, *solution
            );
            std::cout << "  Valid: " << (valid ? "YES" : "NO") << "\n";
        }
        std::cout << std::endl;
    }
}
```

---

### Example 4: Custom Reduction Validation

```cpp
#include "ReductionValidator.h"
#include "ThreeDMToPartitionReducer.h"

using namespace partition;

void validateReductionCorrectness(const ThreeDMInstance& three_dm) {
    ThreeDMToPartitionReducer reducer;
    
    // Perform reduction
    PartitionInstance partition = reducer.Reduce(three_dm);
    
    // Validate structural correctness
    bool valid = ReductionValidator::ValidateReduction(
        reducer, three_dm, partition
    );
    
    std::cout << "Reduction valid: " << (valid ? "YES" : "NO") << std::endl;
    
    // Get detailed report
    std::string report = ReductionValidator::GetValidationReport(
        reducer, three_dm, partition
    );
    
    std::cout << "\nDetailed Report:\n" << report << std::endl;
}
```

---

## Build Instructions

### Standard Build
```bash
cmake -B build
cmake --build build
```

### Build with Clang-Tidy (Strict Checks)
```bash
cmake -B build -DENABLE_TIDY=ON
cmake --build build
```

---

## Key Takeaways

### Architectural Strengths
1. **Modularity**: Each class has a single, well-defined responsibility
2. **Extensibility**: Easy to add new algorithms or reduction strategies
3. **Testability**: Interface-based design enables mocking and unit testing
4. **Type Safety**: Modern C++ features (templates, std::optional, strong typing)

### Complexity Theory Demonstration
- Shows practical implementation of polynomial-time reductions
- Maintains solution equivalence between problems
- Illustrates NP-completeness relationships

### Software Engineering Practices
- SOLID principles throughout
- Const-correctness and immutability
- Clear separation of concerns
- Comprehensive documentation

---

## Future Extensions

Potential enhancements:
1. **More Reduction Strategies**: Implement other NP-complete reductions
2. **Parallel Algorithms**: OpenMP/TBB for parallel solving
3. **Heuristics**: Additional approximation algorithms
4. **Visualization**: Generate graphical representations of instances
5. **Benchmarking**: Automated performance testing suite
6. **Web Interface**: REST API for cloud-based solving

---

*Documentation generated on November 30, 2025*
