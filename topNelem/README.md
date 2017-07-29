# Top N numbers from a file (larger than main memory limit)

## Pseudocode
Let the maximum number of integers in a line be **_m_**.

```
for each line in the file
    read first N numbers and construct a min-heap from these numbers # O(N)
    for each remaining (m-N) numbers in the line
      read the number and store it in variable $i
      # Note: For the above step, we'll read the numbers
      # in chunks which can be held in main memory.

      # the next if block justifies the choice of min-heap as
      # the smallest among the current N elements is removed.
      if ($i > heap.top())
      	heap.pop() 	     # O(logN)
      	heap.insert($i)      # O(logN)
      end if

    write the elements in the heap in a result file
```

|Complexity|Order|
-----------|:----:
Running time complexity | O(**_mlogN_**)
Space complexity | O(**_N_**)

## Instructions
For running the program, execute the following commands:
```
make
make run
cat output_file   # The result is written to "output_file"
```
