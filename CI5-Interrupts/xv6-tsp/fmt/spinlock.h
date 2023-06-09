1500 #pragma once
1501 
1502 // Mutual exclusion lock.
1503 struct spinlock {
1504   uint locked;       // Is the lock held?
1505 
1506   // For debugging:
1507   char *name;        // Name of lock.
1508   struct cpu *cpu;   // The cpu holding the lock.
1509   uint pcs[10];      // The call stack (an array of program counters)
1510                      // that locked the lock.
1511 };
1512 
1513 
1514 
1515 
1516 
1517 
1518 
1519 
1520 
1521 
1522 
1523 
1524 
1525 
1526 
1527 
1528 
1529 
1530 
1531 
1532 
1533 
1534 
1535 
1536 
1537 
1538 
1539 
1540 
1541 
1542 
1543 
1544 
1545 
1546 
1547 
1548 
1549 
