# OS Lab 5 Submission — Threads, Kernel Workers & Process Signals

- **Student Name:** Kiv Sovannlyda
- **Student ID:** p20240001
---

## Task Output Source Files

Make sure all of the following files are present in your `lab5/thread_lab/` folder:

- [ ] `process_test.c`
- [ ] `thread_test.c`
- [ ] `multi_thread.c`
- [ ] `sleeper_threads.c`
- [ ] `signal_handler.c`
- [ ] `challenge.c`

---

## Screenshots

Insert your screenshots below.

### Screenshot 1 — Task 1: Process vs Thread (Process Test)
Show the output of `process_test.c`.
<!-- Insert your screenshot below: -->
![process vs thread 1](images/process_vs_thread_1.png)

---

### Screenshot 2 — Task 1: Process vs Thread (Thread Test)
Show the output of `thread_test.c`.
<!-- Insert your screenshot below: -->
![process vs thread 2](images/process_vs_thread_2.png)

---

### Screenshot 3 — Task 2: Thread Interaction
Show the output of `multi_thread.c`.
<!-- Insert your screenshot below: -->
![thread interaction](images/thread_interaction.png)

---

### Screenshot 4 — Task 3: Visualizing 1:1 Thread Mapping
Show the `ps -eLf` output or `/proc/[pid]/task/` directory visualizing the LWP mapping for user threads.
<!-- Insert your screenshot below: -->
![user to kernel mapping](images/user_kernel_mapping.png)

---

### Screenshot 5 — Task 3: `htop` Kernel Threads
Show `htop` visualizing kernel threads (usually bracketed names like `[kworker]`).
<!-- Insert your screenshot below: -->
![htop kernel threads](images/htop_kernel_threads.png)

---

### Screenshot 6 — Task 4: Catching `SIGINT`
Show the output of your `signal_handler` program gracefully catching `Ctrl+C`.
<!-- Insert your screenshot below: -->
![signal handling](images/signal_sigint.png)

---

### Screenshot 7 — Challenge: Graceful Multithreaded Shutdown
Show the output of your `challenge.c` program joining its threads and exiting gracefully after receiving `Ctrl+C`.
<!-- Insert your screenshot below: -->
![challenge shutdown](images/challenge_shutdown.png)

---

## Answers to Lab Questions

1. **Why do threads share memory while processes do not (by default)?**
   > Threads share the same memory because they are created within the same process so they share the same memory space but processes do not because they are seperate and each of them get their own memory

2. **Based on the 1:1 mapping, what is the role of an LWP (Lightweight Process) in Linux?**
   > The role of an LWP is that it acts as the bridge between a user thread and the kernel so each user thread maps to one LWP, which is what the kernel actually schedules and runs on the CPU

3. **Why is it restricted to send signals to kernel threads (e.g., `kthreadd` or `kworker`)?**
   > It is restricted because kernel threads handle important system tasks like memory mangement so if we are able to send signals then it could crash the entire system

4. **Why can't `SIGKILL` (kill -9) be caught by a signal handler?**
   > It can't be caught because it is directly handled by the kernel, so this guarantees that a process can always be forcibly terminated

---

## Reflection

**What was the most challenging part of managing threads and signals in this lab? How do you think these concepts apply to large-scale applications like web servers or databases?**

> The most challenging part for me was to find the threads that we need to put in the screenshot because I'm not sure what I'm actually looking for/at so it was quite difficult for me to grasp that and also making sure that the output/screenshots necessary corresponds to what we need 