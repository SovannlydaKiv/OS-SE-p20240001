# Class Activity 8 - Memory Management & Virtual Memory

- **Student Name:** Kiv Sovannlyda  **Student ID:** p20240001
- **Personalization:** a = 1, b = 0 → N = (10a+b) mod 128 = [(10x1) + 0] mod 128 = 10
- **Programming Language Used:** [...]

## Part A1 — Address translation (by hand)
[your filled translation table]
1. Offset unchanged because: …
2. Largest offset = …, bits = …
3. (60 + a) = … bytes → … pages, internal fragmentation = … bytes (show working)

## Part A2 — Page replacement (by hand)
- My reference string: …    Prediction (FIFO vs LRU): …
[FIFO trace table] → FIFO faults: …
[LRU trace table]  → LRU faults: …
Which faulted more, and did it match my prediction: …

## Part B — Simulator verification
![Translation](screenshots/task1_translation.png)
![FIFO](screenshots/task2_fifo.png)
![LRU](screenshots/task2_lru.png)
- Did the simulator match my A1 table? …
- Did the simulator's counts for my A2 string match my hand totals? … (if not, what was wrong)

## Part C — Applied reasoning
1. …  2. …  3. …  4. …  5. …