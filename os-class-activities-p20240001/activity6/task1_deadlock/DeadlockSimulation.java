import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;

class Account {
    String name;
    int balance;
    Semaphore lock = new Semaphore(1);

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Transfer {
    static AtomicBoolean t1Done = new AtomicBoolean(false);
    static AtomicBoolean t2Done = new AtomicBoolean(false);
    static volatile String t1WaitingFor = null;
    static volatile String t2WaitingFor = null;

    static void transfer(Account from, Account to, int amount, AtomicBoolean done, int workerId) {
        try {
            System.out.println("Worker " + workerId + " trying to lock FROM " + from.name);
            from.lock.acquire();
            System.out.println("Worker " + workerId + " locked FROM " + from.name);

            Thread.sleep(200); // enough time for the other thread to grab its first lock

            System.out.println("Worker " + workerId + " trying to lock TO " + to.name);
            if (workerId == 1) t1WaitingFor = to.name;
            else               t2WaitingFor = to.name;

            to.lock.acquire(); // this is where deadlock occurs

            if (workerId == 1) t1WaitingFor = null;
            else               t2WaitingFor = null;

            System.out.println("Worker " + workerId + " locked TO " + to.name);

            from.balance -= amount;
            to.balance += amount;

            System.out.println("Worker " + workerId + " transfer of " + amount + " completed");
            done.set(true);

            to.lock.release();
            from.lock.release();
        } catch (InterruptedException e) {
            System.out.println("Worker " + workerId + " was interrupted.");
        }
    }
}

public class DeadlockSimulation {
    public static void main(String[] args) throws InterruptedException {
        Account accountA = new Account("Account-A", 1000);
        Account accountB = new Account("Account-B", 1000);

        System.out.println("=== Bank Transfer Deadlock Simulation ===");
        System.out.println("Starting balances:");
        System.out.println("  Account-A: " + accountA.balance);
        System.out.println("  Account-B: " + accountB.balance);
        System.out.println("  Total: " + (accountA.balance + accountB.balance));
        System.out.println();

        Thread t1 = new Thread(() ->
            Transfer.transfer(accountA, accountB, 100, Transfer.t1Done, 1), "Thread-1");

        Thread t2 = new Thread(() ->
            Transfer.transfer(accountB, accountA, 200, Transfer.t2Done, 2), "Thread-2");

        t1.start();
        t2.start();

        // Watchdog: check every 500ms for up to 3 seconds
        long deadline = System.currentTimeMillis() + 3000;
        while (System.currentTimeMillis() < deadline) {
            Thread.sleep(500);
            if (Transfer.t1Done.get() && Transfer.t2Done.get()) {
                break;
            }
        }

        if (!Transfer.t1Done.get() || !Transfer.t2Done.get()) {
            System.out.println();
            System.out.println("Deadlock detected: transactions are stuck");
            System.out.println();
            if (Transfer.t1WaitingFor != null)
                System.out.println("  Worker 1 is waiting for " + Transfer.t1WaitingFor);
            if (Transfer.t2WaitingFor != null)
                System.out.println("  Worker 2 is waiting for " + Transfer.t2WaitingFor);
            System.out.println();
            System.out.println("Final balances (unchanged due to deadlock):");
            System.out.println("  Account-A: " + accountA.balance);
            System.out.println("  Account-B: " + accountB.balance);
        }

        t1.interrupt();
        t2.interrupt();
        t1.join(500);
        t2.join(500);
    }
}
