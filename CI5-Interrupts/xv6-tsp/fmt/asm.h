0650 #pragma once
0651 
0652 //
0653 // assembler macros to create x86 segments
0654 //
0655 
0656 #define SEG_NULLASM                                             \
0657         .word 0, 0;                                             \
0658         .byte 0, 0, 0, 0
0659 
0660 // The 0xC0 means the limit is in 4096-byte units
0661 // and (for executable segments) 32-bit mode.
0662 #define SEG_ASM(type,base,lim)                                  \
0663         .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
0664         .byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
0665                 (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)
0666 
0667 #define STA_X     0x8       // Executable segment
0668 #define STA_W     0x2       // Writeable (non-executable segments)
0669 #define STA_R     0x2       // Readable (executable segments)
0670 
0671 
0672 
0673 
0674 
0675 
0676 
0677 
0678 
0679 
0680 
0681 
0682 
0683 
0684 
0685 
0686 
0687 
0688 
0689 
0690 
0691 
0692 
0693 
0694 
0695 
0696 
0697 
0698 
0699 
