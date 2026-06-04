import java.util.concurrent.Semaphore;

class AccountSafe {
    String name;
    int balance;

    AccountSafe(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class SafeTransfer {
    static Semaphore mutex = new Semaphore(1);

    static void transfer(AccountSafe from, AccountSafe to, int amount, int workerId) {
        try {
            System.out.println("Worker " + workerId + " waiting for mutex...");
            mutex.acquire();
            System.out.println("Worker " + workerId + " acquired mutex");

            try {
                Thread.sleep(100); // simulate some processing time
                from.balance -= amount;
                to.balance += amount;
                System.out.println("Worker " + workerId + " transferred " + amount
                        + " from " + from.name + " to " + to.name);
            } finally {
                mutex.release();
                System.out.println("Worker " + workerId + " released mutex");
            }

        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class DeadlockFixed {
    public static void main(String[] args) throws InterruptedException {
        AccountSafe accountA = new AccountSafe("Account-A", 1000);
        AccountSafe accountB = new AccountSafe("Account-B", 1000);

        System.out.println("=== Bank Transfer Deadlock Prevention ===");
        System.out.println("Starting balances:");
        System.out.println("  Account-A: " + accountA.balance);
        System.out.println("  Account-B: " + accountB.balance);
        int startingTotal = accountA.balance + accountB.balance;
        System.out.println("  Starting total: " + startingTotal);
        System.out.println();

        Thread t1 = new Thread(() ->
            SafeTransfer.transfer(accountA, accountB, 100, 1), "Thread-1");

        Thread t2 = new Thread(() ->
            SafeTransfer.transfer(accountB, accountA, 200, 2), "Thread-2");

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        int finalTotal = accountA.balance + accountB.balance;

        System.out.println();
        System.out.println("Final balances:");
        System.out.println("  Account-A: " + accountA.balance);
        System.out.println("  Account-B: " + accountB.balance);
        System.out.println("  Final total: " + finalTotal);
        System.out.println();

        if (finalTotal == startingTotal) {
            System.out.println("Balance check PASSED: total preserved (" + startingTotal + " == " + finalTotal + ")");
        } else {
            System.out.println("Balance check FAILED: total mismatch!");
        }
        System.out.println("No deadlock occurred");
    }
}