3350 #include "types.h"
3351 #include "defs.h"
3352 #include "param.h"
3353 #include "memlayout.h"
3354 #include "mmu.h"
3355 #include "proc.h"
3356 #include "x86.h"
3357 #include "traps.h"
3358 #include "spinlock.h"
3359 
3360 // Interrupt descriptor table (shared by all CPUs).
3361 struct gatedesc idt[256];
3362 extern uint vectors[];  // in vectors.S: array of 256 entry pointers
3363 struct spinlock tickslock;
3364 uint ticks;
3365 
3366 void
3367 tvinit(void)
3368 {
3369   int i;
3370 
3371   for(i = 0; i < 256; i++)
3372     SETGATE(idt[i], 0, SEG_KCODE<<3, vectors[i], 0);
3373   SETGATE(idt[T_SYSCALL], 1, SEG_KCODE<<3, vectors[T_SYSCALL], DPL_USER);
3374 
3375   initlock(&tickslock, "time");
3376 }
3377 
3378 void
3379 idtinit(void)
3380 {
3381   lidt(idt, sizeof(idt));
3382 }
3383 
3384 
3385 
3386 
3387 
3388 
3389 
3390 
3391 
3392 
3393 
3394 
3395 
3396 
3397 
3398 
3399 
3400 void
3401 trap(struct trapframe *tf)
3402 {
3403   if(tf->trapno == T_SYSCALL){
3404     if(myproc()->killed)
3405       exit();
3406     myproc()->tf = tf;
3407     syscall();
3408     if(myproc()->killed)
3409       exit();
3410     return;
3411   }
3412 
3413   switch(tf->trapno){
3414   case T_IRQ0 + IRQ_TIMER:
3415     if(cpuid() == 0){
3416       acquire(&tickslock);
3417       ticks++;
3418       wakeup(&ticks);
3419       release(&tickslock);
3420     }
3421     cprintf("Tick on cpu %d !!! Your kernel is now alive !!!\n", mycpu()->apicid);
3422     lapiceoi();
3423     break;
3424   case T_IRQ0 + IRQ_IDE:
3425     ideintr();
3426     lapiceoi();
3427     break;
3428   case T_IRQ0 + IRQ_IDE+1:
3429     // Bochs generates spurious IDE1 interrupts.
3430     break;
3431   case T_IRQ0 + IRQ_KBD:
3432     kbdintr();
3433     lapiceoi();
3434     break;
3435   case T_IRQ0 + IRQ_COM1:
3436     uartintr();
3437     lapiceoi();
3438     break;
3439   case T_IRQ0 + 7:
3440   case T_IRQ0 + IRQ_SPURIOUS:
3441     cprintf("cpu%d: spurious interrupt at %x:%x\n",
3442             cpuid(), tf->cs, tf->eip);
3443     lapiceoi();
3444     break;
3445 
3446 
3447 
3448 
3449 
3450   default:
3451     if(myproc() == 0 || (tf->cs&3) == 0){
3452       // In kernel, it must be our mistake.
3453       cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
3454               tf->trapno, cpuid(), tf->eip, rcr2());
3455       panic("trap");
3456     }
3457     // In user space, assume process misbehaved.
3458     cprintf("pid %d %s: trap %d err %d on cpu %d "
3459             "eip 0x%x addr 0x%x--kill proc\n",
3460             myproc()->pid, myproc()->name, tf->trapno,
3461             tf->err, cpuid(), tf->eip, rcr2());
3462     myproc()->killed = 1;
3463   }
3464 
3465   // Force process exit if it has been killed and is in user space.
3466   // (If it is still executing in the kernel, let it keep running
3467   // until it gets to the regular system call return.)
3468   if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
3469     exit();
3470 
3471   // Check if the process has been killed since we yielded
3472   if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
3473     exit();
3474 }
3475 
3476 
3477 
3478 
3479 
3480 
3481 
3482 
3483 
3484 
3485 
3486 
3487 
3488 
3489 
3490 
3491 
3492 
3493 
3494 
3495 
3496 
3497 
3498 
3499 
