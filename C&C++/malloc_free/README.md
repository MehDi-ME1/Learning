# malloc & free
**Implementing malloc() and free().**

In attempt to implement malloc function and free function, The following files appeared.
v1.0 has several logical issues, But it tend to show basic concepts of malloc() and free() functions.
Issues are explained in related version directories, Inside the README.md file.

Second verions, v2.0, Has a solid implementation with no syntax or logical issues.
But open for developments.


### Core Concepts
**Core concept for implement this functions** are bellow:
- A static array is considered role as heap memory.
- A structure header block shows the memory situation.
- Blocks are related through linked list.
- Memory management is done by arithmic calculation on array.

### Implementation
You only need a gcc compiler. It is not OS dependent. Compile and run.
