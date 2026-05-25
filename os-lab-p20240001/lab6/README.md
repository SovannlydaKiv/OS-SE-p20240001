# OS Lab 6 Submission — Linux Security, Users, Groups & File Permissions

- **Student Name:** Kiv Sovannlyda
- **Student ID:** p20240001

---

## Task Output Files

Make sure all of the following files are present in your `lab6/` folder:

- [ ] `task1_users.txt`
- [ ] `task2_groups.txt`
- [ ] `task3_permissions.txt`
- [ ] `task3_stat_output.txt`
- [ ] `task4_special_bits.txt`
- [ ] `task5_acl.txt`
- [ ] `security_lab/whoami_suid.c`

---

## Screenshots

Insert your screenshots below.

### Screenshot 1 — Task 1: User Creation
Show `cat task1_users.txt` confirming both `dev_alice` and `dev_bob` accounts exist.
<!-- Insert your screenshot below: -->
![user creation](images/task1_user_creation.png)

---

### Screenshot 2 — Task 1: User Modification
Show the updated `/etc/passwd` entry for `dev_alice` with the GECOS comment field.
<!-- Insert your screenshot below: -->
![user modify](images/task1_user_modify.png)

---

### Screenshot 3 — Task 2: Group Setup
Show `cat task2_groups.txt` with group membership for both users.
<!-- Insert your screenshot below: -->
![group setup](images/task2_group_setup.png)

---

### Screenshot 4 — Task 2: Multiple Group Membership
Show `id dev_alice` confirming membership in both `devteam` and `auditors`.
<!-- Insert your screenshot below: -->
![multi group](images/task2_multi_group.png)

---

### Screenshot 5 — Task 3: Directory Permissions
Show `cat task3_permissions.txt` with `drwxrwx---` on the project directory.
<!-- Insert your screenshot below: -->
![dir permissions](images/task3_dir_permissions.png)

---

### Screenshot 6 — Task 3: Access Denied
Show the `Permission denied` error when `temp_user` tries to access the project directory.
<!-- Insert your screenshot below: -->
![access denied](images/task3_access_denied.png)

---

### Screenshot 7 — Task 4: setgid Bit
Show the directory listing with `s` in the group execute position, and `bob_file.txt` inheriting the `devteam` group.
<!-- Insert your screenshot below: -->
![setgid](images/task4_setgid.png)

---

### Screenshot 8 — Task 4: Sticky Bit
Show the `t` bit in the directory listing and the `Operation not permitted` error when `dev_bob` tries to delete `dev_alice`'s file.
<!-- Insert your screenshot below: -->
![sticky bit](images/task4_sticky_bit.png)

---

### Screenshot 9 — Task 4: setuid Bit
Show `ls -l whoami_suid` with `s` in the owner execute position and the program's UID output.
<!-- Insert your screenshot below: -->
![setuid](images/task4_setuid.png)

---

### Screenshot 10 — Task 5: ACL Directory
Show `getfacl /opt/techcorp/devproject` with the `auditors` ACE.
<!-- Insert your screenshot below: -->
![acl dir](images/task5_acl_dir.png)

---

### Screenshot 11 — Task 5: ACL Access Test
Show `dev_alice` successfully accessing the file and `temp_user` being denied.
<!-- Insert your screenshot below: -->
![acl test](images/task5_acl_test.png)

---

### Screenshot 12 — Task 5: ACL Output File
Show `cat task5_acl.txt` with the full ACL entries.
<!-- Insert your screenshot below: -->
![acl output](images/task5_acl_output.png)

---

### Screenshot 13 — Challenge:
![acl output](images/challenge_dropbox.png)

## Answers to Lab Questions

1. **What is the difference between `userdel` and `userdel -r`?**
   > userdel removes the user account only, leaving their home directory and files behind while userdel -r removes the account AND deletes their home directory and all their files with it

2. **Why is it safer to use `visudo` instead of directly editing `/etc/sudoers`?**
   > It's safer because visudo validates the syntax before saving so if you make a typo editing /etc/sudoers directly and save it, sudo can break entirely and potentially locking you out of root access on the system.

3. **What happens when a `setgid` directory contains files created by different users? What benefit does this provide for team collaboration?**
   > Any file created inside automatically inherits the directory's group,regardless of which user created it so this means all team members can access each other's files without anyone having to manually chown every new file

4. **What limitation of standard Unix permissions does the ACL system solve?**
   > Standard Unix permissions only allow you to set access for one owner, one group, and everyone else while ACLs let you grant specific permissions to additional users or groups