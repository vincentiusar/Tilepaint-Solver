# Tilepaint Puzzle Solver

Tilepaint (Tairupeinto) is a logic pencil-and-paper puzzle that has proven NP-Complete. The verification and solver related to the Tilepaint puzzles are in this repository. We implemented the solver using complete search with bitmasking technique and prune-and-search with the backtracking technique whose asymptotic running times are $O(2^{p} \cdot p \cdot mn) $ $O(2^{p} \cdot mn)$, where $m \times n$ is the size of the instance. For more information about the puzzle, see [https://www.nikoli.co.jp/en/puzzles/tilepaint/](https://www.nikoli.co.jp/en/puzzles/tilepaint/).

## Test Cases
There are 250 test cases in the TC folder taken from [https://www.janko.at/Raetsel/Tairupeinto/index.htm](https://www.janko.at/Raetsel/Tairupeinto/index.htm). Each test case is numbered from `1` to `250` where a file with extension \*.in is the input and \*\_sol.txt is the expected answer of such number cases.
There are 3 kinds of instance sizes, i.e. $10 \times 10$; $12 \times 12$; and $15 \times 15$.

## Verifier

The verifier code is written in C++ and can be found in the `tilepaint_validation.cpp`. 

### Input
The input format for the verifier is as follows
```
m n
cc_1 cc_2 ... cc_n
cr_1 cr_2 ... cr_m
T_{1,1} T_{1,2} ... T_{1,n}
T_{2,1} T_{2,2} ... T_{2,n}
...
T_{m,1} T_{m,2} ... T_{m,n}
C_{1,1} C_{1,2} ... C_{1,n}
C_{2,1} C_{2,2} ... C_{2,n}
...
C_{m,1} C_{m,2} ... C_{m,n}
```
- m and n respectively are row and column size of the instance.
- cc_{j} representing the constraint column of j. (if there is no constraint in column j, then cc_j = -1).
- cr_{i} representing the constraint row of i. (if there is no constraint in row i, then cr_i = -1).
- T_{i, j} is an integer denoting the cell (i, j) where it belongs to. Each tile denoted by a unique number.
- C_{i, j} is an integer denoting the cell (i, j) coloring status. 1 means colored, and 0 means uncolored.

### Output
- If the configuration is a valid solution
```
Valid Solution
Execution time: {execution time} ms
```
- Otherwise
```
Invalid
Execution time: 1 ms
```

### Example
```
10 10
7 7 7 4 3 4 4 8 6 3
9 7 4 4 6 3 1 5 6 8
1 6 6 6 13 13 19 19 19 27 
1 1 1 10 13 13 20 19 19 27 
1 1 7 10 10 13 20 23 23 25
2 2 7 11 11 13 20 23 25 25 
3 3 7 7 11 16 21 21 21 21
3 3 7 12 12 16 21 21 26 26 
4 4 4 12 12 17 17 22 26 26
5 5 8 8 14 14 22 22 22 26
5 5 8 9 15 15 15 24 24 24 
5 5 9 9 9 18 18 24 24 24
1 1 1 1 1 1 1 1 1 0
1 1 1 0 1 1 0 1 1 0
1 1 1 0 0 1 0 0 0 0
1 1 1 0 0 1 0 0 0 0
0 0 1 1 0 0 1 1 1 1
0 0 1 0 0 0 1 1 0 0
0 0 0 0 0 0 0 1 0 0
1 1 0 0 0 0 1 1 1 0
1 1 0 1 0 0 0 1 1 1
1 1 1 1 1 0 0 1 1 1
```
```
Valid Solution
Execution time: 1 ms
```

## Solver
The verifier code is written in C++ and can be found in the `tilepaint_BF.cpp` (exhausted search) and `tilepaint_BT.cpp` (prune-and-search).
Both of them receive the same input format.
However, the exhausted search output is a set of a number of colored tiles, and the prune-and-search output is a set of a number of colored tiles with also the configuration denoted by an $m \times n$ of `1` or `0`.

### Input
```
m n
cc_1 cc_2 ... cc_n
cr_1 cr_2 ... cr_m
T_{1,1} T_{1,2} ... T_{1,n}
T_{2,1} T_{2,2} ... T_{2,n}
...
T_{m,1} T_{m,2} ... T_{m,n}
```
- m and n respectively are row and column size of the instance.
- cc_{j} representing the constraint column of j. (if there is no constraint in column j, then cc_j = -1).
- cr_{i} representing the constraint row of i. (if there is no constraint in row i, then cr_i = -1).
- T_{i, j} is an integer denoting the cell (i, j) where it belongs to. Each tile denoted by a unique number.

### Output
- The given input has a solution
### Brute Force
```
Solution : 
T_1 T_2 ... T_p
Execution Time: {execution time} ms
```

### Prune-and-Search
```
Solution : 
T_1 T_2 ... T_p
C_{1,1} C_{1,2} ... C_{1,n}
C_{2,1} C_{2,2} ... C_{2,n}
...
C_{m,1} C_{m,2} ... C_{m,n}
Execution Time: {execution time} ms
```

- Otherwise
```
No Solution
```

## Example
```
10 10
7 7 7 4 3 4 4 8 6 3
9 7 4 4 6 3 1 5 6 8
1 6 6 6 13 13 19 19 19 27 
1 1 1 10 13 13 20 19 19 27 
1 1 7 10 10 13 20 23 23 25
2 2 7 11 11 13 20 23 25 25 
3 3 7 7 11 16 21 21 21 21
3 3 7 12 12 16 21 21 26 26 
4 4 4 12 12 17 17 22 26 26
5 5 8 8 14 14 22 22 22 26
5 5 8 9 15 15 15 24 24 24 
5 5 9 9 9 18 18 24 24 24
```
```
Solution : 
1 2 5 6 7 9 13 19 21 22 24 
1 1 1 1 1 1 1 1 1 0 
1 1 1 0 1 1 0 1 1 0 
1 1 1 0 0 1 0 0 0 0 
1 1 1 0 0 1 0 0 0 0 
0 0 1 1 0 0 1 1 1 1 
0 0 1 0 0 0 1 1 0 0 
0 0 0 0 0 0 0 1 0 0 
1 1 0 0 0 0 1 1 1 0 
1 1 0 1 0 0 0 1 1 1 
1 1 1 1 1 0 0 1 1 1 
Execution Time: 1ms.
```

## Experiment Results
The experiment result of running time for all test cases are in file `.xlsx`
