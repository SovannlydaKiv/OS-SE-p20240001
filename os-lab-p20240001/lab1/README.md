# OS Lab 1 Submission

- **Student Name:** Kiv Sovannlyda
- **Student ID:** p20240001

---

## Task 1: Operating System Identification

**The commands used in this task are:**
<pre>
- uname: displays kernel and system information
- lsb_release: displays Ubuntu distribution details
</pre>
<!-- Insert your screenshot for Task 1 below: -->
<!-- SCREENSHOT REQUIREMENT: Show the terminal after running uname -a and lsb_release -a, or the contents of your task1_os_info.txt file. -->
![alt text](../lab1/images/task 1.png)
---

## Task 2: Essential Linux File and Directory Commands

**The commands introduced in this task are:**
<pre>
- pwd: Print Working Directory
- ls: List directory contents
- mkdir/cd:  Make a new directory / Change into a directory
- touch: Creates a new, empty file
- echo: Writes out / print text
- cat: Concatenates and displays the contents of a file
- cp /mv /rm: Copy, Move/Rename, and Remove (delete) files
</pre>

<!-- Insert your screenshot for Task 2 below: -->
<!-- SCREENSHOT REQUIREMENT: Show the terminal running the file manipulation commands (mkdir, touch, cp, mv, rm) or the final cat of your task2_file_commands.txt file. -->

![alt text](../lab1/images/task 2.png)

---

## Task 3: Package Management Using APT

Explain the difference you observed between `remove` and `purge`.

The difference that I observed it that `remove` just uninstalls the program whereas `purge` completely wipes everything. 


**The commands used in this task are:**
<pre>
- apt-get update: refreshes the local package index from remote repositories
- apt-get install: downloads and installs a package
- apt-get remove: uninstalls a package but keeps its configuration files
- apt-get purge: uninstalls a package and removes its configuration files
- apt-get upgrade: upgrades all currently installed packages to their latest available versions
- apt list --installed: lists all packages currently installed on the system
- ls: used here to check for the existence of configuration directories
</pre>

<!-- Insert your screenshot for Task 3 below: -->
<!-- SCREENSHOT REQUIREMENT: Show the output of ls -ld /etc/mc after running apt-get remove (folder still exists) versus after running apt-get purge (folder is gone). -->

![alt text](../lab1/images/task 3.png)

---

## Task 4: Programs vs Processes (Single Process)

Briefly describe how you ran a background process and found it in the process list.

The background process ran `sleep 120 &` and that threw it into the backgrounf and then it did `ps > task4_process_list.txt` in order to list the cuurent running processes 

**The commands used in this task are:**
<pre>
- sleep: runs a program that simply pauses for a specified duration
- &: added to the end of a command to run a program in the background
- ps: lists currently running processes
</pre>

<!-- Insert your screenshot for Task 4 below: -->
<!-- SCREENSHOT REQUIREMENT: Show the terminal where you ran sleep 120 & and the subsequent ps output showing the sleep process running. -->

![alt text](../lab1/images/task 4.png)

---

## Task 5: Installing Real Applications & Observing Multitasking

**The commands used in this task are:**
<pre>
- apt-get install
- python3
</pre>

<!-- Insert your screenshot for Task 5 below: -->
<!-- SCREENSHOT REQUIREMENT: Show the terminal ps output capturing the multiple background tasks (sleep and python3 server) running at the same time. -->

![alt text](../lab1/images/task 5.png)

---

## Task 6: Virtualization and Hypervisor Detection

**The commands used in this task are:**
<pre>
- systemd-detect-virt
- lscpu
- uname, hostname
</pre>

<!-- Insert your screenshot for Task 6 below: -->
<!-- SCREENSHOT REQUIREMENT: Show the terminal output of the systemd-detect-virt and lscpu commands. -->

![alt text](../lab1/images/task 6.png)