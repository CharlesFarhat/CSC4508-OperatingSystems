0450 #pragma once
0451 // Routines to let C code use special x86 instructions.
0452 
0453 static inline uchar
0454 inb(ushort port)
0455 {
0456   uchar data;
0457 
0458   asm volatile("in %1,%0" : "=a" (data) : "d" (port));
0459   return data;
0460 }
0461 
0462 static inline void
0463 insl(int port, void *addr, int cnt)
0464 {
0465   asm volatile("cld; rep insl" :
0466                "=D" (addr), "=c" (cnt) :
0467                "d" (port), "0" (addr), "1" (cnt) :
0468                "memory", "cc");
0469 }
0470 
0471 static inline void
0472 outb(ushort port, uchar data)
0473 {
0474   asm volatile("out %0,%1" : : "a" (data), "d" (port));
0475 }
0476 
0477 static inline void
0478 outw(ushort port, ushort data)
0479 {
0480   asm volatile("out %0,%1" : : "a" (data), "d" (port));
0481 }
0482 
0483 static inline void
0484 outsl(int port, const void *addr, int cnt)
0485 {
0486   asm volatile("cld; rep outsl" :
0487                "=S" (addr), "=c" (cnt) :
0488                "d" (port), "0" (addr), "1" (cnt) :
0489                "cc");
0490 }
0491 
0492 static inline void
0493 stosb(void *addr, int data, int cnt)
0494 {
0495   asm volatile("cld; rep stosb" :
0496                "=D" (addr), "=c" (cnt) :
0497                "0" (addr), "1" (cnt), "a" (data) :
0498                "memory", "cc");
0499 }
0500 static inline void
0501 stosl(void *addr, int data, int cnt)
0502 {
0503   asm volatile("cld; rep stosl" :
0504                "=D" (addr), "=c" (cnt) :
0505                "0" (addr), "1" (cnt), "a" (data) :
0506                "memory", "cc");
0507 }
0508 
0509 struct segdesc;
0510 
0511 static inline void
0512 lgdt(struct segdesc *p, int size)
0513 {
0514   volatile ushort pd[3];
0515 
0516   pd[0] = size-1;
0517   pd[1] = (uint)p;
0518   pd[2] = (uint)p >> 16;
0519 
0520   asm volatile("lgdt (%0)" : : "r" (pd));
0521 }
0522 
0523 struct gatedesc;
0524 
0525 static inline void
0526 lidt(struct gatedesc *p, int size)
0527 {
0528   volatile ushort pd[3];
0529 
0530   pd[0] = size-1;
0531   pd[1] = (uint)p;
0532   pd[2] = (uint)p >> 16;
0533 
0534   asm volatile("lidt (%0)" : : "r" (pd));
0535 }
0536 
0537 static inline void
0538 ltr(ushort sel)
0539 {
0540   asm volatile("ltr %0" : : "r" (sel));
0541 }
0542 
0543 static inline uint
0544 readeflags(void)
0545 {
0546   uint eflags;
0547   asm volatile("pushfl; popl %0" : "=r" (eflags));
0548   return eflags;
0549 }
0550 static inline void
0551 loadgs(ushort v)
0552 {
0553   asm volatile("movw %0, %%gs" : : "r" (v));
0554 }
0555 
0556 static inline void
0557 cli(void)
0558 {
0559   asm volatile("cli");
0560 }
0561 
0562 static inline void
0563 sti(void)
0564 {
0565   asm volatile("sti");
0566 }
0567 
0568 static inline uint
0569 xchg(volatile uint *addr, uint newval)
0570 {
0571   uint result;
0572 
0573   // The + in "+m" denotes a read-modify-write operand.
0574   asm volatile("lock; xchgl %0, %1" :
0575                "+m" (*addr), "=a" (result) :
0576                "1" (newval) :
0577                "cc");
0578   return result;
0579 }
0580 
0581 static inline uint
0582 rcr2(void)
0583 {
0584   uint val;
0585   asm volatile("movl %%cr2,%0" : "=r" (val));
0586   return val;
0587 }
0588 
0589 static inline void
0590 lcr3(uint val)
0591 {
0592   asm volatile("movl %0,%%cr3" : : "r" (val));
0593 }
0594 
0595 
0596 
0597 
0598 
0599 
0600 // Layout of the trap frame built on the stack by the
0601 // hardware and by trapasm.S, and passed to trap().
0602 struct trapframe {
0603   // registers as pushed by pusha
0604   uint edi;
0605   uint esi;
0606   uint ebp;
0607   uint oesp;      // useless & ignored
0608   uint ebx;
0609   uint edx;
0610   uint ecx;
0611   uint eax;
0612 
0613   // rest of trap frame
0614   ushort gs;
0615   ushort padding1;
0616   ushort fs;
0617   ushort padding2;
0618   ushort es;
0619   ushort padding3;
0620   ushort ds;
0621   ushort padding4;
0622   uint trapno;
0623 
0624   // below here defined by x86 hardware
0625   uint err;
0626   uint eip;
0627   ushort cs;
0628   ushort padding5;
0629   uint eflags;
0630 
0631   // below here only when crossing rings, such as from user to kernel
0632   uint esp;
0633   ushort ss;
0634   ushort padding6;
0635 };
0636 
0637 
0638 
0639 
0640 
0641 
0642 
0643 
0644 
0645 
0646 
0647 
0648 
0649 
