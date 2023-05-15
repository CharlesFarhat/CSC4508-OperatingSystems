7350 // The local APIC manages internal (non-I/O) interrupts.
7351 // See Chapter 8 & Appendix C of Intel processor manual volume 3.
7352 
7353 #include "param.h"
7354 #include "types.h"
7355 #include "defs.h"
7356 #include "date.h"
7357 #include "memlayout.h"
7358 #include "traps.h"
7359 #include "mmu.h"
7360 #include "x86.h"
7361 
7362 // Local APIC registers, divided by 4 for use as uint[] indices.
7363 #define ID      (0x0020/4)   // ID
7364 #define VER     (0x0030/4)   // Version
7365 #define TPR     (0x0080/4)   // Task Priority
7366 #define EOI     (0x00B0/4)   // EOI
7367 #define SVR     (0x00F0/4)   // Spurious Interrupt Vector
7368   #define ENABLE     0x00000100   // Unit Enable
7369 #define ESR     (0x0280/4)   // Error Status
7370 #define ICRLO   (0x0300/4)   // Interrupt Command
7371   #define INIT       0x00000500   // INIT/RESET
7372   #define STARTUP    0x00000600   // Startup IPI
7373   #define DELIVS     0x00001000   // Delivery status
7374   #define ASSERT     0x00004000   // Assert interrupt (vs deassert)
7375   #define DEASSERT   0x00000000
7376   #define LEVEL      0x00008000   // Level triggered
7377   #define BCAST      0x00080000   // Send to all APICs, including self.
7378   #define BUSY       0x00001000
7379   #define FIXED      0x00000000
7380 #define ICRHI   (0x0310/4)   // Interrupt Command [63:32]
7381 #define TIMER   (0x0320/4)   // Local Vector Table 0 (TIMER)
7382   #define X1         0x0000000B   // divide counts by 1
7383   #define PERIODIC   0x00020000   // Periodic
7384 #define PCINT   (0x0340/4)   // Performance Counter LVT
7385 #define LINT0   (0x0350/4)   // Local Vector Table 1 (LINT0)
7386 #define LINT1   (0x0360/4)   // Local Vector Table 2 (LINT1)
7387 #define ERROR   (0x0370/4)   // Local Vector Table 3 (ERROR)
7388   #define MASKED     0x00010000   // Interrupt masked
7389 #define TICR    (0x0380/4)   // Timer Initial Count
7390 #define TCCR    (0x0390/4)   // Timer Current Count
7391 #define TDCR    (0x03E0/4)   // Timer Divide Configuration
7392 
7393 volatile uint *lapic;  // Initialized in mp.c
7394 
7395 
7396 
7397 
7398 
7399 
7400 static void
7401 lapicw(int index, int value)
7402 {
7403   lapic[index] = value;
7404   lapic[ID];  // wait for write to finish, by reading
7405 }
7406 
7407 void
7408 lapicinit(void)
7409 {
7410   if(!lapic)
7411     return;
7412 
7413   // Enable local APIC; set spurious interrupt vector.
7414   lapicw(SVR, ENABLE | (T_IRQ0 + IRQ_SPURIOUS));
7415 
7416   // Disable logical interrupt lines.
7417   lapicw(LINT0, MASKED);
7418   lapicw(LINT1, MASKED);
7419 
7420   // Disable performance counter overflow interrupts
7421   // on machines that provide that interrupt entry.
7422   if(((lapic[VER]>>16) & 0xFF) >= 4)
7423     lapicw(PCINT, MASKED);
7424 
7425   // Map error interrupt to IRQ_ERROR.
7426   lapicw(ERROR, T_IRQ0 + IRQ_ERROR);
7427 
7428   // Clear error status register (requires back-to-back writes).
7429   lapicw(ESR, 0);
7430   lapicw(ESR, 0);
7431 
7432   // Ack any outstanding interrupts.
7433   lapicw(EOI, 0);
7434 
7435   // Send an Init Level De-Assert to synchronise arbitration ID's.
7436   lapicw(ICRHI, 0);
7437   lapicw(ICRLO, BCAST | INIT | LEVEL);
7438   while(lapic[ICRLO] & DELIVS)
7439     ;
7440 
7441   // Enable interrupts on the APIC (but not on the processor).
7442   lapicw(TPR, 0);
7443 }
7444 
7445 
7446 
7447 
7448 
7449 
7450 int
7451 lapicid(void)
7452 {
7453   if (!lapic)
7454     return 0;
7455   return lapic[ID] >> 24;
7456 }
7457 
7458 // Acknowledge interrupt.
7459 void
7460 lapiceoi(void)
7461 {
7462   if(lapic)
7463     lapicw(EOI, 0);
7464 }
7465 
7466 // Spin for a given number of microseconds.
7467 // On real hardware would want to tune this dynamically.
7468 void
7469 microdelay(int us)
7470 {
7471 }
7472 
7473 #define CMOS_PORT    0x70
7474 #define CMOS_RETURN  0x71
7475 
7476 // Start additional processor running entry code at addr.
7477 // See Appendix B of MultiProcessor Specification.
7478 void
7479 lapicstartap(uchar apicid, uint addr)
7480 {
7481   int i;
7482   ushort *wrv;
7483 
7484   // "The BSP must initialize CMOS shutdown code to 0AH
7485   // and the warm reset vector (DWORD based at 40:67) to point at
7486   // the AP startup code prior to the [universal startup algorithm]."
7487   outb(CMOS_PORT, 0xF);  // offset 0xF is shutdown code
7488   outb(CMOS_PORT+1, 0x0A);
7489   wrv = (ushort*)P2V((0x40<<4 | 0x67));  // Warm reset vector
7490   wrv[0] = 0;
7491   wrv[1] = addr >> 4;
7492 
7493   // "Universal startup algorithm."
7494   // Send INIT (level-triggered) interrupt to reset other CPU.
7495   lapicw(ICRHI, apicid<<24);
7496   lapicw(ICRLO, INIT | LEVEL | ASSERT);
7497   microdelay(200);
7498   lapicw(ICRLO, INIT | LEVEL);
7499   microdelay(100);    // should be 10ms, but too slow in Bochs!
7500   // Send startup IPI (twice!) to enter code.
7501   // Regular hardware is supposed to only accept a STARTUP
7502   // when it is in the halted state due to an INIT.  So the second
7503   // should be ignored, but it is part of the official Intel algorithm.
7504   // Bochs complains about the second one.  Too bad for Bochs.
7505   for(i = 0; i < 2; i++){
7506     lapicw(ICRHI, apicid<<24);
7507     lapicw(ICRLO, STARTUP | (addr>>12));
7508     microdelay(200);
7509   }
7510 }
7511 
7512 #define CMOS_STATA   0x0a
7513 #define CMOS_STATB   0x0b
7514 #define CMOS_UIP    (1 << 7)        // RTC update in progress
7515 
7516 #define SECS    0x00
7517 #define MINS    0x02
7518 #define HOURS   0x04
7519 #define DAY     0x07
7520 #define MONTH   0x08
7521 #define YEAR    0x09
7522 
7523 static uint
7524 cmos_read(uint reg)
7525 {
7526   outb(CMOS_PORT,  reg);
7527   microdelay(200);
7528 
7529   return inb(CMOS_RETURN);
7530 }
7531 
7532 static void
7533 fill_rtcdate(struct rtcdate *r)
7534 {
7535   r->second = cmos_read(SECS);
7536   r->minute = cmos_read(MINS);
7537   r->hour   = cmos_read(HOURS);
7538   r->day    = cmos_read(DAY);
7539   r->month  = cmos_read(MONTH);
7540   r->year   = cmos_read(YEAR);
7541 }
7542 
7543 
7544 
7545 
7546 
7547 
7548 
7549 
7550 // qemu seems to use 24-hour GWT and the values are BCD encoded
7551 void
7552 cmostime(struct rtcdate *r)
7553 {
7554   struct rtcdate t1, t2;
7555   int sb, bcd;
7556 
7557   sb = cmos_read(CMOS_STATB);
7558 
7559   bcd = (sb & (1 << 2)) == 0;
7560 
7561   // make sure CMOS doesn't modify time while we read it
7562   for(;;) {
7563     fill_rtcdate(&t1);
7564     if(cmos_read(CMOS_STATA) & CMOS_UIP)
7565         continue;
7566     fill_rtcdate(&t2);
7567     if(memcmp(&t1, &t2, sizeof(t1)) == 0)
7568       break;
7569   }
7570 
7571   // convert
7572   if(bcd) {
7573 #define    CONV(x)     (t1.x = ((t1.x >> 4) * 10) + (t1.x & 0xf))
7574     CONV(second);
7575     CONV(minute);
7576     CONV(hour  );
7577     CONV(day   );
7578     CONV(month );
7579     CONV(year  );
7580 #undef     CONV
7581   }
7582 
7583   *r = t1;
7584   r->year += 2000;
7585 }
7586 
7587 
7588 
7589 
7590 
7591 
7592 
7593 
7594 
7595 
7596 
7597 
7598 
7599 
