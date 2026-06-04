import threading
import time

stop_flag = threading.Event()

def process1():
    while not stop_flag.is_set():
        print("H", end="", flush=True)
        print("E", end="", flush=True)

def process2():
    while not stop_flag.is_set():
        print("L", end="", flush=True)

def process3():
    while not stop_flag.is_set():
        print("O", end="", flush=True)

threads = [
    threading.Thread(target=process1),
    threading.Thread(target=process2),
    threading.Thread(target=process3),
]

for t in threads:
    t.start()

time.sleep(0.05)   # let them run briefly so interleaving is visible
stop_flag.set()

for t in threads:
    t.join()

print()
print("(letters above are in wrong/unpredictable order — no semaphore ordering used)")