# Performance

This document outlines the final benchmarking results, the optimisation techniques applied and their performance effects.

## Benchmarking results

The solver was benchmarked, obtaining the results shown in the following table:

| Benchmark name | Samples     | Iterations   | Estimated    |  
| -------------- | ----------- | ------------ | ------------ | 
|                | mean        | low mean     | high mean    |     
|                | std dev     | low std dev  | high std dev |    
| -------------- | ----------- | ------------ | ---------    | 
|                |             |              |              |     
| Benchmark name | Samples     | Iterations   | Estimated    |  
| -------------- | ----------- | ------------ | ------------ | 
|        Diffusion        |  100  |   1  |  1.12728 s   |  
|                | 11.2673 ms  |  11.2522 ms  |  11.2828 ms   |  
|                | 78.1882 us  |   69.031 us  |   90.6525 us   |  
| -------------- | ----------- | ------------ | ---------    | 
|                |             |              |              |     
| Benchmark name | Samples     | Iterations   | Estimated    |  
| -------------- | ----------- | ------------ | ------------ | 
|        Jacobi        |  100      |         1    |  143.387 ms  | 
|                |  1.43005 ms   |   1.42343 ms   |    1.4383 ms  | 
|                |  37.3863 us    |   31.027 us    |  47.4977 us  |   
| -------------- | ----------- | ------------ | ---------    | 
|                |             |              |              |     
| Benchmark name | Samples     | Iterations   | Estimated    |
| -------------- | ----------- | ------------ | ------------ |
|         Gauss-Seidel       |  100       |        1  |    566.289 ms  | 
|                |  5.62072 ms  |    5.60853 ms    |  5.63598 ms  | 
|                |  69.3318 us    |  54.8678 us  |    93.2107 us | 
| -------------- | ----------- | ------------ | ---------    |
|                |             |              |              |

*Note that the non-solver parts of the software have not been benchmarked, as they are dependent on user input and have a minimal impact in performance.

## Performance optimisations

The code already followed several best practices, leading to a reasonable performance. However, several improvements were made in different areas:

### Solver algorithm
- As shown in the benchmarking table, the algorithm choice greatly impacts performance and dominates over other factors.
This resulted in improvements of several miliseconds.

### Efficiently relying on existing libraries
- We replaced in-house functions and structures with those from the standard library when possible, as those are already optimised.
- Additionally, we chose to use the standard array instead of vector when possible.
This resulted in small improvements of around 0.01 miliseconds.

### Minimalistic use of operations and object creation
- We precomputed variables which were constant throughout the loops, such as products and powers.
- We swapped pointers in substitution of the copy constructor, thus avoiding the creation of new objects.
- We simplified conditionals and loops, reducing the number of checks.
This resulted in an improvement of around 1 milisecond.

Furthermore, we used the -O3 when compiling to further optimise the code. -O2 was also considered, but -O3 was kept as we did not encounter stability problems.