0200 #pragma once
0201 
0202 // Memory layout
0203 
0204 #define EXTMEM  0x100000            // Start of extended memory
0205 #define PHYSTOP 0xE000000           // Top physical memory
0206 #define DEVSPACE 0xFE000000         // Other devices are at high addresses
0207 
0208 // Key addresses for address space layout (see kmap in vm.c for layout)
0209 #define KERNBASE 0x80000000         // First kernel virtual address
0210 #define KERNLINK (KERNBASE+EXTMEM)  // Address where kernel is linked
0211 
0212 #define V2P(a) (((uint) (a)) - KERNBASE)
0213 #define P2V(a) ((void *)(((char *) (a)) + KERNBASE))
0214 
0215 #define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
0216 #define P2V_WO(x) ((x) + KERNBASE)    // same as P2V, but without casts
0217 
0218 
0219 
0220 
0221 
0222 
0223 
0224 
0225 
0226 
0227 
0228 
0229 
0230 
0231 
0232 
0233 
0234 
0235 
0236 
0237 
0238 
0239 
0240 
0241 
0242 
0243 
0244 
0245 
0246 
0247 
0248 
0249 
