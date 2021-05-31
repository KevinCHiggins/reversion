### Re: Version

**A quiz game using tree and list data structures in C**

This is a learning C project. It's a text-based quiz that checks your knowledge of JS and C features!

I used some ideas from [these class little game dev tutorials](https://www.parallelrealities.co.uk/tutorials/#shooter) to organise the code into decoupled modules. The idea is that the ```str_list``` and  ```str_tree``` data structures, and the ```kev_str``` utility functions are reusable, independent modules. Then ```load_topics.c``` handles storing the quiz topics, wrapping the tree data structure and exposing data-structure-agnostic convenience functions; ```game.c``` calls these and contains the quiz rules and question templates; and ```#define``` statements, structs and enums are separated out into their own files too.

Obvious improvements would be dynamic rather than somewhat static data structures, a channel for error handling, and calling a GUI library (which should be pretty easy with this decoupled design).

I really enjoyed this introduction to manual memory management and pointer arithmetic. I also got a glimpse of some of C's stickier spots like string handling. Looking forward to doing some more C game dev someday.

Thanks for reading!

Kevin Higgins, 31/05/21