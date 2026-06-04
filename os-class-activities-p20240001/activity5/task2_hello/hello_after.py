import threading

a = threading.Semaphore(1)   
b = threading.Semaphore(0)   
c = threading.Semaphore(0)   

done = threading.Event()     

def process1():
    while True:
        a.acquire()           
        print("H", end="", flush=True)
        print("E", end="", flush=True)
        b.release()           
        

def process2():
    l_printed = 0
    # Loop2
    while True:
        b.acquire()           # wait(b)
        print("L", end="", flush=True)
        l_printed += 1
        if l_printed == 1:
            b.release()       # signal(b) → loop back, print 2nd L
        else:
            c.release()       # signal(c) → unblock Process 3 to print O
            break             # Process 2 is done
        # goto Loop2

def process3():
    # Loop3 (effectively runs once — c never re-signaled)
    while True:
        c.acquire()           # wait(c)
        print("O", end="", flush=True)
        done.set()            # signal main thread we are done
        # goto Loop3 → but c is 0 now, so next iteration blocks forever

t1 = threading.Thread(target=process1, daemon=True)
t2 = threading.Thread(target=process2, daemon=True)
t3 = threading.Thread(target=process3, daemon=True)

t1.start()
t2.start()
t3.start()

t2.join()          # wait for Process 2 to finish (it terminates cleanly)
done.wait()        # wait for Process 3 to print O
print()            # newline after HELLO