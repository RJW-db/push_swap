# push_swap
`push_swap` is a sorting algorithm implementation in C that sorts a stack of integers using two stacks and a limited set of 11 operations, outputting the shortest possible instruction sequence.

## Table of Contents
- [Description](#description)
- [Operations](#operations)
- [Algorithm](#algorithm)
- [Benchmark](#benchmark)
- [Project Rules (42 Subject)](#project-rules-42-subject)
- [Build](#build)
- [Usage](#usage)
- [Bonus: checker](#bonus-checker)
- [Resources](#resources)

## Description
You have two stacks (`a` and `b`) and a fixed set of instructions to manipulate them.
Stack `a` starts with a list of unique integers in any order. Stack `b` starts empty.
The goal is to sort stack `a` in ascending order (smallest at the top) using the fewest possible operations.

`push_swap` takes the initial stack as command-line arguments and prints the optimized instruction sequence to stdout.

## Operations
| Instruction | Effect |
|-------------|--------|
| `sa` | Swap the top 2 elements of stack a |
| `sb` | Swap the top 2 elements of stack b |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Push the top of b onto a |
| `pb` | Push the top of a onto b |
| `ra` | Rotate a upward (first becomes last) |
| `rb` | Rotate b upward (first becomes last) |
| `rr` | `ra` and `rb` at the same time |
| `rra` | Reverse rotate a (last becomes first) |
| `rrb` | Reverse rotate b (last becomes first) |
| `rrr` | `rra` and `rrb` at the same time |

## Algorithm
This implementation uses a cost-based greedy approach known as the Turk Algorithm:

1. **Small stacks (2 or 3 elements)**: handled with direct hardcoded logic.
2. **Larger stacks**: push all elements except three to stack b, sort the remaining three in stack a, then repeatedly select the element from b that can be inserted into its correct position in a at the lowest combined rotation cost.
3. **Cost calculation**: for each element in b, compute the number of rotations needed in both stacks to place it at its target position in a. Execute the cheapest move. Use combined `rr`/`rrr` operations when both stacks rotate in the same direction to reduce total instruction count.
4. **Final rotation**: once all elements are back in a, rotate a so the minimum is at the top.

Source: [Turk Algorithm](https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0)


## Benchmark

### 3 elements
- `2 1 0` sorted in 2 or 3 operations

### 5 elements
- Any 5 values sorted in 12 operations or fewer (8 is kudos)

### 100 and 500 numbers
| Score | 100 numbers | 500 numbers |
|-------|-------------|-------------|
| 5/5 | under 700 | under 5500 |
| 4/5 | under 900 | under 7000 |
| 3/5 | under 1100 | under 8500 |
| 2/5 | under 1300 | under 10000 |
| 1/5 | under 1500 | under 11500 |

Note: the bonus part is only evaluated if the mandatory part scores perfectly, including flawless error management.


## Project Rules (42 Subject)

### General rules
- Must be written in C.
- Must follow the Norm (Norminette). Bonus files/functions are included in the norm check.
- Must not crash unexpectedly (segfault, bus error, double free, etc.), except undefined behavior.
- All heap allocations must be freed properly. Memory leaks are not tolerated.
- Global variables are forbidden.

### Mandatory
- Output: a binary named `push_swap`.
- Required Makefile rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`.
- The program takes the initial stack a as arguments (first argument = top of stack).
- Prints the shortest instruction sequence to stdout, one instruction per line.
- Prints nothing if no arguments are given.
- Prints `Error` to stderr for invalid input (non-integers, out of int range, duplicates).

### Bonus
- Output: a binary named `checker`.
- Built separately with `make bonus`.
- Takes the initial stack a as arguments (first argument = top of stack).
- Reads instructions from stdin, one per line, until EOF (CTRL+D).
- Displays `OK` to stdout if stack a is sorted and stack b is empty after executing all instructions.
- Displays `KO` to stdout otherwise.
- Prints `Error` to stderr for invalid input (non-integers, out of int range, duplicates, unknown or malformed instructions).
- Stops silently if no arguments are given.


## Build
Build the static library:

```sh
make        # build push_swap
make bonus  # build checker
make clean  # remove build artifacts
make fclean # clean + remove push_swap checker (and extern deps)
make re     # fclean + build
make bre    # fclean + build + bonus
make debug  # debug flags + sanitizers (per Makefile)
```


## Usage

Sort a list of integers:

```
./push_swap 2 1 3 6 5 8
pb
pb
rb
pb
sa
pa
pa
pa
```

Check the number of operations generated:

```
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
```

Validate the output with the provided checker:

```
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
OK
```

Already sorted input produces no output:

```
./push_swap 0 1 2 3
```

Error cases:

```
./push_swap 0 one 2 3
Error

./push_swap 1 +1 -1
Error

./push_swap 2147483648
Error
```

## Resources

- [push_swap visualizer](https://github.com/o-reo/push_swap_visualizer): real-time visual debugging tool for watching your algorithm sort step by step.
- [push_swap tester by gemartin99](https://github.com/gemartin99/Push-Swap-Tester): automated stress tester for validating operation counts across many random inputs.
- [push_swap ProChecker by ailopez-o](https://github.com/ailopez-o/42Barcelona-PushSwap-ProChecker): extended checker with detailed feedback for validating correctness and performance.
