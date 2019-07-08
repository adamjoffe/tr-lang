# tr-lang

### Author - Adam Joffe - Joffeadamf@gmail.com
Designed and implemented as part of Undergraduate Engineering Honours Thesis - [Teleo-Reactive Language for Reactive Agent Behaviour](doc/Adam_Joffe_BEng_Honours_Thesis.pdf)

## Overview
tr-lang (short for Teleo-Reactive Language) is an interpreted, high-level, dynamically typed, domain specific language (DSL) for short for Reactive Agent Behaviour. Based on the Teleo-Reactive programs concepts as described by [Nils Nilsson](https://www.jair.org/index.php/jair/article/view/10112), the language allows rapid development of complex hierarchical based agent behaviour for real-time robotic platforms.

tr-lang was implemented with an interpreter so that *.tr* source code files can be quickly and easily modified and updated on a remote platform without need to compile. Additionally, to provide improved interoperability with real-time systems that are build on low level C/C++ for performance purposes, tr-lang provides bindings to inject C/C++ functions, variables, objects, methods and lambdas as inbuilt accessable variables and function in tr-lang. This is supported through the tr-lang interpreter existing as a C/C++ object that can be constructed and manage from within an already exists C/C++ pipeline/framework, providing the interface for registering these functions/variables for injects:<br/>
![TRInterpreter Interface](doc/C%2B%2B_TR-Lang_Interface.jpg)

Finally, tr-lang provides a blackboard data structure that can easily be shared between the tr-lang and C/C++ layer allowing for a concurrency safe method of sharing data. For example, platform localisation information computed by C/C++ layer can be provided in the data structure to be used by the tr-lang layer for making behavioural decisions. Example blackboard structure:<br/>
![Example Struture](doc/Blackboard_Structure.jpg)

## Language Definition
The language syntax is defined in the [Extended Backus-Naur Form (EBNF)](doc/EBNF.txt). The core of the language are the *tr-nodes* defined with the **:-** operator and behave like labelled *if-else* blocks. 
```
find_ball() :-
ball_seen(ball_frames() > 10) -> eyeLED(RED), approachBall(v) : achieves find_ball;
search_known(last_seen_frame() < 5) -> headspin(LEFT) : achieves ball_seen;
true -> spin_search() : achieves search_known;
```
There are a few key components that construct each othe *tr-conditions*. Firstly, each condition requires being suffixed with an *achieves-statement* which denotes which *tr-condition* above it or the *tr-node* itself. This enforces the first property of *regression*, as described by [Nils Nilsson](https://www.jair.org/index.php/jair/article/view/10112), for Teleo-Reactive structure. The second is fulfilled by the requires **true** condition, which acts as a catch-all to ensure that the properties are *complete*.

Since tr-lang is designed for robotic platforms, it also contains vectory variable types and literals. By default, it is implemented as a 2D vector defined in [default_vector.h](libs/default_vector.h). However, a user can easily implement their own underlying vector type for any number of dimensions, since the [EBNF](dec/EBNF.txt) supports any number of double values for the vector litteral. This can be done by by defining a custom vector implementation in [vector_impl.h](user-customisation/vector_impl.h), and using the **#define VECTOR_IMPLEMENTATION** macro combined with a vector type renaming in the *TR* namespace:<br/>
```
namespace TR {
  using Vector = MyVector;
}
#define VECTOR_IMPLEMENTATION
```

## Tools
tr-lang also provides a number of tools to aid with development on behaviours and ensure runtime performance is optimised. The profiler, to measure execution number and time of code components, the drawer, to output a tree diagram of the hierarchical behaviour implemented in the code, and the debugger, to help understand program flow during execution.

### Profiler

### Drawer

### Debugger

