import threading
import time
import random

BUFFER_CAPACITY = 100
buffer = []
produced_count = 0
packaged_count = 0

def producer(machine_id):
    global produced_count
    pair_id = 0
    while True:
        pair_id += 1
        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"

        # NO semaphore — race condition: buffer may overflow
        if len(buffer) + 2 > BUFFER_CAPACITY:
            print("The producing machine is broken")
            return

        # Simulate a context switch between adding P1 and P2
        buffer.append(p1)
        time.sleep(random.uniform(0, 0.01))  # gap allows interleaving
        buffer.append(p2)

        produced_count += 1
        print(f"Produced pairs: {produced_count} | Packaged pairs: {packaged_count} | Buffer particles: {len(buffer)}")
        time.sleep(random.uniform(0.01, 0.05))

def consumer():
    global packaged_count
    while True:
        time.sleep(0.03)

        # NO semaphore — may try to consume from empty buffer
        if len(buffer) < 2:
            print("The packaging machine is broken")
            return

        p1 = buffer.pop(0)
        p2 = buffer.pop(0)

        # Verify same pair
        id1 = p1.rsplit("-P", 1)[0]
        id2 = p2.rsplit("-P", 1)[0]
        if id1 != id2:
            print("Pairs are incorrect")
            return

        packaged_count += 1

threads = []
for i in range(1, 4):
    t = threading.Thread(target=producer, args=(i,), daemon=True)
    threads.append(t)

c = threading.Thread(target=consumer, daemon=True)
threads.append(c)

for t in threads:
    t.start()

for t in threads:
    t.join()