# Vector

An Implementation of the C++ standard library's `std::vector` class from the `<vector>` header file.<br>
A vector is a dynamic array, a data structure which holds a sequence of values in a single block of contigous memory, where each value is the same size (in bytes), just like a traditional array.<br> 
However, a dynamic array is different from a traditional array in that the size of the former can be modified at runtime, such that operations like `insert`, `erase`, `push`, `pop`, etc. could be executed on the stucture.

## Dependencies
* [GoogleTest](https://github.com/google/googletest)

## Setup
### Prerequisites:
* [Premake5](https://github.com/premake/premake-core)


### Steps:
* Clone this repository
* Run `premake5 --help` and look at the "ACTIONS" section for a list of build actions
* Run `premake5 [options] <action> [arguments]` in the repo directory
 
*Note: Vector has only ben tests on the* `windows mingw gmake` *configuration.*

## Features
* Iterators
### Constructors/Assignment:
* The Rule of 5
* Fill
* Initializer List
### Access Methods:
* at
* operator[]
* front
* back
* data
### Capacity Methods:
* empty
* size
* reserve
* capacity
### Modification Methods:
* clear
* insert
* erase
* push_back
* pop_back
## Notes
This project uses code produced by generative artificial intelligence (GenAI) in [exampletest.cpp](tests/unit/exampletest/src/exampletest.cpp) to create unit tests.