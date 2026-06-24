# Class Activity 8 - Memory Management & Virtual Memory

- **Student Name:** Kiv Sovannlyda   **Student ID:** p20240001
- **Personalization:** a = 1, b = 0 → N = (10x1 + 0) mod 128 = 10
- **Programming Language Used:** [...]

## Part 1A — Address translation (by hand)
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

## Part 1B — TLB & Effective Access Time (by hand)
- My page-reference stream: 1 2 4 1 6 2 7 1 4 6    Prediction (expected hits): maybe 3-4 

|Ref | HIT/MISS | Page table read? | TLB after (LRU→MRU) | Evicted |
|---|---|---|---|---|
| 1 | MISS | yes | [1] | – |
| 2 | MISS | yes | [1,2] | – |
| 4 | MISS | yes | [1,2,4] | – |
| 1 | HIT  | no  | [2,4,1] | – |
| 6 | MISS | yes | [2,4,1,6] | – |
| 2 | HIT  | no  | [4,1,6,2] | – |
| 7 | MISS | yes | [1,6,2,7] | 4 |
| 1 | HIT  | no  | [6,2,7,1] | – |
| 4 | MISS | yes | [2,7,1,4] | 6 |
| 6 | MISS | yes | [7,1,4,6] | 2 |
 
Measured hits = 3/10, α = 0.3
 
- EAT at my α (0.3): 0.3(1+11) + 0.7(1+22) = 3.6 + 16.1 = 19.7 ns
- EAT at 80%: 0.8(12) + 0.2(23) = 9.6 + 4.6 = 14.2 ns
- EAT at 99%: 0.99(12) + 0.01(23) = 11.88 + 0.23 = 12.11 ns
- No TLB: 1 + 2(11) = 23 ns

- Why 99% beats no-TLB by 47%: (23 − 12.11) / 23 ≈ 47.3% faster 
![EAT](screenshots/part1_eat.png)   ![TLB](screenshots/part1_tlb.png)

## Part 1C — Paging simulator verification
![Translation](screenshots/task1_translation.png)
- Did the simulator match my 1A table? yes, all six addresses matched exactly
- (Optional) Did the TLB sim reproduce my 1B hit ratio / EAT? …

## Part 2A — Page replacement (by hand)
- My reference string: 1 0 1 2 0 3 0 4 2 3 0 3    Prediction (FIFO vs LRU): i think FIFO would have more faults 

**FIFO**
 
| Ref | H/F | F1 | F2 | F3 | Evicted |
|---|---|---|---|---|---|
| 1 | F | 1 | – | – | – |
| 0 | F | 1 | 0 | – | – |
| 1 | H | 1 | 0 | – | – |
| 2 | F | 1 | 0 | 2 | – |
| 0 | H | 1 | 0 | 2 | – |
| 3 | F | 3 | 0 | 2 | 1 |
| 0 | H | 3 | 0 | 2 | – |
| 4 | F | 3 | 4 | 2 | 0 |
| 2 | H | 3 | 4 | 2 | – |
| 3 | H | 3 | 4 | 2 | – |
| 0 | F | 3 | 4 | 0 | 2 |
| 3 | H | 3 | 4 | 0 | – |

 
→ FIFO faults: 6
 
**LRU**
 

| Ref | H/F | F1 | F2 | F3 | Evicted |
|---|---|---|---|---|---|
| 1 | F | 1 | – | – | – |
| 0 | F | 1 | 0 | – | – |
| 1 | H | 0 | 1 | – | – |
| 2 | F | 0 | 1 | 2 | – |
| 0 | H | 1 | 2 | 0 | – |
| 3 | F | 2 | 0 | 3 | 1 |
| 0 | H | 2 | 3 | 0 | – |
| 4 | F | 3 | 0 | 4 | 2 |
| 2 | F | 0 | 4 | 2 | 3 |
| 3 | F | 4 | 2 | 3 | 0 |
| 0 | F | 2 | 3 | 0 | 4 |
| 3 | H | 2 | 0 | 3 | – |

 
→ LRU faults: 8

Which faulted more, and did it match my prediction: it didnt match my prediction because LRU resulted in more faults so i was wrong

## Part 2B — Demand-paging simulator verification
![FIFO](screenshots/task2_fifo.png)   ![LRU](screenshots/task2_lru.png)
- Did the simulator's counts for my 2A string match my hand totals? (if not, what was wrong): yes, it did match my hands total 

## Part 3 — Applied reasoning
1. paging is free of external fragmentation while contiguous allocation isnt is because pages and frames are always the same fixed size, so any free frame fits any page  
2. loading a page into an empty frame still count as a page fault because the frame being empty just means there's nothing to evict and the page still has to be fetched from disk and that fetch is what makes it a fault
3. each miss costs a full extra memory access, so even a small slice of misses adds up fast so going from 80% to 99% cuts almost half the gap to having no TLB at all 
4. LRU and FIFO differ because right after page 4 loads, FIFO and LRU are holding the same three frames but tracking different things because FIFO cares about load order and LRU cares about last use, so from that point on they start evicting different pages, and LRU ends up paying for it later  
5. thrashing is when the system spends more time swapping pages than actually running anything and with 1 frame in part 2b, almost every reference would fault since each new page kicks out the one just loaded
6. 
> benefit: you skip loading stuff the program might never touch

> risk: the first time you do touch something new, you eat a stall waiting for it to load