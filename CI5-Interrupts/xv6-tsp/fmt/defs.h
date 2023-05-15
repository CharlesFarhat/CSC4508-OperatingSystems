0250 #pragma once
0251 
0252 struct buf;
0253 struct context;
0254 struct file;
0255 struct inode;
0256 struct pipe;
0257 struct proc;
0258 struct rtcdate;
0259 struct spinlock;
0260 struct sleeplock;
0261 struct stat;
0262 struct superblock;
0263 
0264 // bio.c
0265 void            binit(void);
0266 struct buf*     bread(uint, uint);
0267 void            brelse(struct buf*);
0268 void            bwrite(struct buf*);
0269 
0270 // console.c
0271 void            consoleinit(void);
0272 void            cprintf(char*, ...);
0273 void            consoleintr(int(*)(void));
0274 void            panic(char*) __attribute__((noreturn));
0275 
0276 // exec.c
0277 int             exec(char*, char**);
0278 
0279 // file.c
0280 struct file*    filealloc(void);
0281 void            fileclose(struct file*);
0282 struct file*    filedup(struct file*);
0283 void            fileinit(void);
0284 int             fileread(struct file*, char*, int n);
0285 int             filestat(struct file*, struct stat*);
0286 int             filewrite(struct file*, char*, int n);
0287 
0288 // fs.c
0289 void            readsb(int dev, struct superblock *sb);
0290 int             dirlink(struct inode*, char*, uint);
0291 struct inode*   dirlookup(struct inode*, char*, uint*);
0292 struct inode*   ialloc(uint, short);
0293 struct inode*   idup(struct inode*);
0294 void            iinit(int dev);
0295 void            ilock(struct inode*);
0296 void            iput(struct inode*);
0297 void            iunlock(struct inode*);
0298 void            iunlockput(struct inode*);
0299 void            iupdate(struct inode*);
0300 int             namecmp(const char*, const char*);
0301 struct inode*   namei(char*);
0302 struct inode*   nameiparent(char*, char*);
0303 int             readi(struct inode*, char*, uint, uint);
0304 void            stati(struct inode*, struct stat*);
0305 int             writei(struct inode*, char*, uint, uint);
0306 
0307 // ide.c
0308 void            ideinit(void);
0309 void            ideintr(void);
0310 void            iderw(struct buf*);
0311 
0312 // ioapic.c
0313 void            ioapicenable(int irq, int cpu);
0314 extern uchar    ioapicid;
0315 void            ioapicinit(void);
0316 
0317 // kalloc.c
0318 char*           kalloc(void);
0319 void            kfree(char*);
0320 void            kinit1(void*, void*);
0321 void            kinit2(void*, void*);
0322 
0323 // kbd.c
0324 void            kbdintr(void);
0325 
0326 // lapic.c
0327 void            cmostime(struct rtcdate *r);
0328 int             lapicid(void);
0329 extern volatile uint*    lapic;
0330 void            lapiceoi(void);
0331 void            lapicinit(void);
0332 void            lapicstartap(uchar, uint);
0333 void            microdelay(int);
0334 
0335 // log.c
0336 void            initlog(int dev);
0337 void            log_write(struct buf*);
0338 void            begin_op();
0339 void            end_op();
0340 
0341 // mp.c
0342 extern int      ismp;
0343 void            mpinit(void);
0344 
0345 // picirq.c
0346 void            picenable(int);
0347 void            picinit(void);
0348 
0349 
0350 // pipe.c
0351 int             pipealloc(struct file**, struct file**);
0352 void            pipeclose(struct pipe*, int);
0353 int             piperead(struct pipe*, char*, int);
0354 int             pipewrite(struct pipe*, char*, int);
0355 
0356 
0357 // proc.c
0358 int             cpuid(void);
0359 void            exit(void);
0360 int             fork(void);
0361 int             growproc(int);
0362 int             kill(int);
0363 struct cpu*     mycpu(void);
0364 struct proc*    myproc();
0365 void            pinit(void);
0366 void            procdump(void);
0367 void            scheduler(void) __attribute__((noreturn));
0368 void            sched(void);
0369 void            setproc(struct proc*);
0370 void            sleep(void*, struct spinlock*);
0371 void            userinit(void);
0372 int             wait(void);
0373 void            wakeup(void*);
0374 void            yield(void);
0375 
0376 // swtch.S
0377 void            swtch(struct context**, struct context*);
0378 
0379 // spinlock.c
0380 void            acquire(struct spinlock*);
0381 void            getcallerpcs(void*, uint*);
0382 int             holding(struct spinlock*);
0383 void            initlock(struct spinlock*, char*);
0384 void            release(struct spinlock*);
0385 void            pushcli(void);
0386 void            popcli(void);
0387 
0388 // sleeplock.c
0389 void            acquiresleep(struct sleeplock*);
0390 void            releasesleep(struct sleeplock*);
0391 int             holdingsleep(struct sleeplock*);
0392 void            initsleeplock(struct sleeplock*, char*);
0393 
0394 // string.c
0395 int             memcmp(const void*, const void*, uint);
0396 void*           memmove(void*, const void*, uint);
0397 void*           memset(void*, int, uint);
0398 char*           safestrcpy(char*, const char*, int);
0399 int             strlen(const char*);
0400 int             strncmp(const char*, const char*, uint);
0401 char*           strncpy(char*, const char*, int);
0402 
0403 // syscall.c
0404 int             argint(int, int*);
0405 int             argptr(int, char**, int);
0406 int             argstr(int, char**);
0407 int             fetchint(uint, int*);
0408 int             fetchstr(uint, char**);
0409 void            syscall(void);
0410 
0411 // timer.c
0412 void            timerinit(void);
0413 
0414 // trap.c
0415 void            idtinit(void);
0416 extern uint     ticks;
0417 void            tvinit(void);
0418 extern struct spinlock tickslock;
0419 
0420 // uart.c
0421 void            uartinit(void);
0422 void            uartintr(void);
0423 void            uartputc(int);
0424 
0425 // vm.c
0426 void            seginit(void);
0427 void            kvmalloc(void);
0428 pde_t*          setupkvm(void);
0429 char*           uva2ka(pde_t*, char*);
0430 int             allocuvm(pde_t*, uint, uint);
0431 int             deallocuvm(pde_t*, uint, uint);
0432 void            freevm(pde_t*);
0433 void            inituvm(pde_t*, char*, uint);
0434 int             loaduvm(pde_t*, char*, struct inode*, uint, uint);
0435 pde_t*          copyuvm(pde_t*, uint);
0436 void            switchuvm(struct proc*);
0437 void            switchkvm(void);
0438 int             copyout(pde_t*, uint, void*, uint);
0439 void            clearpteu(pde_t *pgdir, char *uva);
0440 
0441 // number of elements in fixed-size array
0442 #define NELEM(x) (sizeof(x)/sizeof((x)[0]))
0443 
0444 
0445 
0446 
0447 
0448 
0449 
