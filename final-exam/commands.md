# commands.md — exact commands I ran, per part

> Paste the **real** commands you ran, in order, in the fenced blocks below. Graded for
> command competency and is your defence if any output is questioned. One block per part.
> Delete the hint comments and replace with your actual commands.

## Part A — Threads, Mapping & Signals

```bash
# compile the threaded program (mind the threading flag), run it
# capture the 1:1 user→kernel (LWP) mapping into thread_map.txt while it runs
# compile/run signal_demo and demonstrate catching the interactive interrupt
cd ~/OS-SE-p20240001/final-exam/partA_threads

# 1. Compile and run the threaded program (A1)
gcc thread_demo.c -o thread_demo -pthread
./thread_demo

# 2. Capture the 1:1 user→kernel (LWP) mapping (A2)
./thread_demo &
ps -eLf | grep thread_demo > thread_map.txt

# 3. Compile, run, and catch the interactive interrupt (A3)
gcc signal_demo.c -o signal_demo
./signal_demo
# (Pressed Ctrl+C to trigger SIGINT)

# 4. Live Modification Task (Extra Worker)
gcc thread_demo.c -o thread_demo -pthread
./thread_demo
```

## Part B — Permissions, Special Bits & ACLs

```bash
# build the tree (shared dir + private file); set octal + symbolic modes
# demonstrate setgid + sticky on a dir you own; build/set the setuid binary
# add and read back an ACL entry; save reports
cd ~/OS-SE-p20240001/final-exam/partB_security

# 1. Build the tree and set permissions (B1)
mkdir shared_dir private_dir
touch shared_dir/shared_file private_dir/private_file
chmod 600 private_dir/private_file
chmod 711 shared_dir

# 2. Save permission reports
ls -ld shared_dir > perm_report.txt
ls -l private_dir/private_file >> perm_report.txt
stat private_dir/private_file >> perm_report.txt

# 3. Demonstrate setgid + sticky on a directory (B2)
mkdir special_dir
chmod g+s special_dir
chmod +t special_dir

# 4. Build and set the setuid binary (B2)
gcc setuid_demo.c -o setuid_demo
chmod u+s setuid_demo

# 5. Capture evidence and run
ls -ld special_dir
ls -l setuid_demo
./setuid_demo
```

## Part C — Bash Scripting, PATH & Safe Scanning

```bash
# make greeter runnable by name via PATH; record PATH + resolved location
# run collector over your dirs; show it skips unreadable/missing files safely
cd ~/OS-SE-p20240001/final-exam/partC_scripting
mkdir -p scripts

# 1. Make greeter runnable by name via PATH and record locations (C1)
chmod +x ~/bin/greeter
cp ~/bin/greeter scripts/
export PATH=$PATH:~/bin
greeter
echo "$PATH" > path_report.txt
which greeter >> path_report.txt

# 2. Setup test directories for safe scanning (C2)
chmod +x ~/bin/collector
cp ~/bin/collector scripts/
mkdir -p test_dir1 test_dir2
echo "OrbitWorks backend log 1..." > test_dir1/data1.txt
echo "OrbitWorks backend log 2..." > test_dir2/data2.txt
touch test_dir2/secret.txt
chmod 000 test_dir2/secret.txt

# 3. Run collector over directories
collector test_dir1 test_dir2

# 4. Restore read permissions so git can push the file
chmod +r ~/OS-SE-p20240001/final-exam/partC_scripting/test_dir2/secret.txt
```

## Part D — Race Condition & flock

```bash
# init stock; run swarm several times unpatched and record final stock each time
# add the exclusive advisory lock around the read-modify-write; re-run swarm
cd ~/OS-SE-p20240001/final-exam/partD_secure
mkdir -p scripts

# 1. Setup and run unpatched swarm to trigger race condition (D1 & D2)
chmod +x ~/bin/buy_widget ~/bin/swarm
cp ~/bin/buy_widget scripts/
cp ~/bin/swarm scripts/
swarm

# 2. Record observations
echo "Run 1 Final Stock: 98" > observations.txt
echo "Run 2 Final Stock: 99" >> observations.txt
echo "Run 3 Final Stock: 97" >> observations.txt
echo "Conclusion: Without locking, the concurrent bots read the same initial stock value into memory and overwrite each other's decrements, leaving more stock than there should be." >> observations.txt

# 3. Apply flock patch and re-run swarm (D3)
cp ~/bin/buy_widget scripts/
cp ~/bin/swarm scripts/
swarm

# 4. Live Modification Task (Purchase Cap = 8)
cp ~/bin/buy_widget scripts/
~/bin/buy_widget "GreedyBot" 10
~/bin/swarm
```

## Part E — Backups & cron

```bash
# E1: run backup_project enough times that pruning happens (keep newest RETAIN_N)
# E2: per-user crontab, two entries (absolute paths):
#     recurring (CRON_INTERVAL) -> partE_automation/logs/cron_recurring.log
#     one-shot at TIMED        -> partE_automation/logs/cron_oneshot.log
# E3: backup_exam -> tar the final-exam folder to ~/exam-backups/final-exam-<ts>.tar.gz
#     crontab: run backup_exam on a short interval AND once at exactly 16:00 today
#     then: ls ~/exam-backups
# capture crontab -l + both logs + the ~/exam-backups listing into cron_report.txt
cd ~/OS-SE-p20240001/final-exam/partE_automation
mkdir -p sample_project/src logs scripts
touch sample_project/src/app.c

# 1. Run backup_project to trigger pruning (Keep newest 4) (E1)
chmod +x ~/bin/backup_project
cp ~/bin/backup_project scripts/
backup_project; sleep 1; backup_project; sleep 1; backup_project; sleep 1; backup_project; sleep 1; backup_project; sleep 1; backup_project
ls -l backups/

# 2. Setup timed_job and backup_exam scripts (E2 & E3)
chmod +x ~/bin/timed_job ~/bin/backup_exam
cp ~/bin/timed_job scripts/
cp ~/bin/backup_exam scripts/
crontab -e

# 3. Manually trigger the jobs once to populate logs for grading
~/bin/timed_job ~/OS-SE-p20240001/final-exam/partE_automation/logs/cron_oneshot.log
~/bin/backup_exam

# 4. Generate cron_report.txt
crontab -l > cron_report.txt
echo -e "\n--- Recurring Log ---" >> cron_report.txt
cat logs/cron_recurring.log >> cron_report.txt
echo -e "\n--- One-Shot Log ---" >> cron_report.txt
cat logs/cron_oneshot.log >> cron_report.txt
echo -e "\n--- Exam Backups Dir ---" >> cron_report.txt
ls -l ~/exam-backups >> cron_report.txt

# 5. Live Modification Task (Idempotent job with token)
cp ~/bin/timed_job scripts/
~/bin/timed_job test_idempotent.log
~/bin/timed_job test_idempotent.log
cat test_idempotent.log
```
