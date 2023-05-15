2300 #pragma once
2301 
2302 // Per-CPU state
2303 struct cpu {
2304   uchar apicid;                // Local APIC ID
2305   struct context *scheduler;   // swtch() here to enter scheduler
2306   struct taskstate ts;         // Used by x86 to find stack for interrupt
2307   struct segdesc gdt[NSEGS];   // x86 global descriptor table
2308   volatile uint started;       // Has the CPU started?
2309   int ncli;                    // Depth of pushcli nesting.
2310   int intena;                  // Were interrupts enabled before pushcli?
2311   struct proc *proc;           // The process running on this cpu or null
2312 };
2313 
2314 extern struct cpu cpus[NCPU];
2315 extern int ncpu;
2316 
2317 
2318 // Saved registers for kernel context switches.
2319 // Don't need to save all the segment registers (%cs, etc),
2320 // because they are constant across kernel contexts.
2321 // Don't need to save %eax, %ecx, %edx, because the
2322 // x86 convention is that the caller has saved them.
2323 // Contexts are stored at the bottom of the stack they
2324 // describe; the stack pointer is the address of the context.
2325 // The layout of the context matches the layout of the stack in swtch.S
2326 // at the "Switch stacks" comment. Switch doesn't save eip explicitly,
2327 // but it is on the stack and allocproc() manipulates it.
2328 struct context {
2329   uint edi;
2330   uint esi;
2331   uint ebx;
2332   uint ebp;
2333   uint eip;
2334 };
2335 
2336 
2337 
2338 
2339 
2340 
2341 
2342 
2343 
2344 
2345 
2346 
2347 
2348 
2349 
2350 enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
2351 
2352 // Per-process state
2353 struct proc {
2354   uint sz;                     // Size of process memory (bytes)
2355   pde_t* pgdir;                // Page table
2356   char *kstack;                // Bottom of kernel stack for this process
2357   enum procstate state;        // Process state
2358   int pid;                     // Process ID
2359   struct proc *parent;         // Parent process
2360   struct trapframe *tf;        // Trap frame for current syscall
2361   struct context *context;     // swtch() here to run process
2362   void *chan;                  // If non-zero, sleeping on chan
2363   int killed;                  // If non-zero, have been killed
2364   struct file *ofile[NOFILE];  // Open files
2365   struct inode *cwd;           // Current directory
2366   char name[16];               // Process name (debugging)
2367 };
2368 
2369 // Process memory is laid out contiguously, low addresses first:
2370 //   text
2371 //   original data and bss
2372 //   fixed-size stack
2373 //   expandable heap
2374 
2375 
2376 
2377 
2378 
2379 
2380 
2381 
2382 
2383 
2384 
2385 
2386 
2387 
2388 
2389 
2390 
2391 
2392 
2393 
2394 
2395 
2396 
2397 
2398 
2399 
