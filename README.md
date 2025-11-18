# `libcds`
## Description
The ISO C standard libraries are delibraretely minimal and do not attempt to implement data structures commonly included in some modern languages. `libcds` is a personal project being developed to add a handful useful data structures to C as a library other projects may link with.

## Data Structures
All data structures aim to be implemented with a "store-by-value" method using `void` pointers to store variables of any given type.

Data structures being implemented are:
- **Dynamic array** - _TODO_
- **Linked list** - _TODO_
- **Heap** - _TODO_
- **Unordered Map** - _TODO_
- **Ordered Map** - _TODO_

This is not a definitive list and is subject to be changed/added to.

## Purpose
I'm aware there are many suitable libraries for C that add useful data structures. This is mainly a personal project that attempts to adapt sturctures I've made before in Java for university assignments to C. I was interested about seeing how you could implement data structures in C that hold abitrary types without higher-level features like generics.

The library is meant to be simple, relatively safe, and mostly performant.

## License
`libcds` is licensed under the [GNU General Public License v3](https://www.gnu.org/licenses/gpl-3.0.en.html).
