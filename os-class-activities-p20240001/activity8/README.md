# Class Activity 8 - Memory Management & Virtual Memory

- **Student Name:** Kiv Sovannlyda  **Student ID:** p20240001
- **Personalization:** a = 1, b = 0 → N = (10a+b) mod 128 = [(10x1) + 0] mod 128 = 10
- **Programming Language Used:** [...]

## Part A1 — Address translation (by hand)
Personalization: a=9, b=1, N = (10×9+1) mod 128 = 91

| LA  | page = LA÷16 | offset = LA mod 16 | valid? | frame | physical = frame×16+offset |
|-----|-------------|-------------------|--------|-------|---------------------------|
| 20  | 1           | 4                 | YES    | 2     | 2×16+4 = 36               |
| 100 | 6           | 4                 | YES    | 0     | 0×16+4 = 4                |
| 48  | 3           | 0                 | NO     | —     | Page fault                |
| 16  | 1           | 0                 | YES    | 2     | 2×16+0 = 32               |
| 127 | 7           | 15                | YES    | 4     | 4×16+15 = 79              |
| 10  | 0           | 10                | YES    | 5     | 5x16+10 = 90              |

1. Offset unchanged because: the offset just reoresents the specific location of a byte inside a page and since the logical page and physical frame are the same size(16 bytes), nothing changes
2. Largest offset = 15, bits = 4
3. (60 + a) = 61 bytes → 4 pages, internal fragmentation = 3 bytes
   * Bytes needed: 60 + 1 = 61 bytes
   * Pages allocated: 61 / 16 = 4 pages
   * Working: 4 x 16 = 64 bytes allocated => 64 - 61 = 3 bytes wasted

## Part A2 — Page replacement (by hand)
- My reference string: 1 0 1 2 0 3 0 4 2 3 0 3     
- Prediction (FIFO vs LRU): my prediction is that FIFO will cause more faults than the LRU because it may kick out a page that we may still actively need while LRU keeps recently used pages that are more likely to be reused soon

### FIFO trace
| Ref | H/F | F1 | F2 | F3 | Evicted |
|-----|-----|----|----|----|---------|
| 1   | F   | 1  | _  | _  | —       |
| 0   | F   | 1  | 0  | _  | —       |
| 1   | H   | 1  | 0  | _  | —       |
| 2   | F   | 1  | 0  | 2  | —       |
| 0   | H   | 1  | 0  | 1  | —       |
| 3   | F   | 3  | 0  | 2  | 1       |
| 0   | H   | 3  | 0  | 2  | —       |
| 4   | F   | 3  | 4  | 2  | 0       |
| 2   | H   | 3  | 4  | 2  | —       |
| 3   | H   | 3  | 4  | 2  | —       |
| 0   | F   | 3  | 4  | 0  | 2       |
| 3   | H   | 3  | 4  | 0  | —       |

 → FIFO faults: 6

### LRU Trace

| Ref | H/F | F1  | F2  | F3 | Evicted | Recency order (LRU→MRU) |
| --- | --- | --- | --- |--- | ---     | ---                     |
| 1   | F   | 1   | —   | —  | —       | [1]                      |
| 0   | F   | 1   | 0   | —  | —       | [1, 0]                   |
| 1   | H   | 1   | 0   | —  | —       | [0, 1]                   |
| 2   | F   | 1   | 0   | 2  | —       | [0, 1, 2]                |
| 0   | H   | 1   | 0   | 2  | —       | [1, 2, 0]                |
| 3   | F   | 3   | 0   | 2  | 1       | [2, 0, 3]                |
| 0   | H   | 3   | 0   | 2  | —       | [2, 3, 0]                |
| 4   | F   | 3   | 0   | 4  | 2       | [3, 0, 4]                |
| 2   | F   | 2   | 0   | 4  | 3       | [0, 4, 2]                |
| 3   | F   | 2   | 3   | 4  | 0       | [4, 2, 3]                |
| 0   | F   | 2   | 3   | 0  | 4       | [2, 3, 0]                |
| 3   | H   | 2   | 3   | 0  | —       | [2, 0, 3]                |

→ LRU faults: 8
Which faulted more, and did it match my prediction: the LRU has more faults so i'm wrong and it didnt match my prediction at all

## Part B — Simulator verification
![Translation](screenshots/task1_translation.png)
![FIFO](screenshots/task2_fifo.png)
![LRU](screenshots/task2_lru.png)
- Did the simulator match my A1 table? …
- Did the simulator's counts for my A2 string match my hand totals? … (if not, what was wrong)

## Part C — Applied reasoning
1. …  
2. …  
3. …  
4. …  
5. …