0900 #pragma once
0901 
0902 // Format of an ELF executable file
0903 
0904 #define ELF_MAGIC 0x464C457FU  // "\x7FELF" in little endian
0905 
0906 // File header
0907 struct elfhdr {
0908   uint magic;  // must equal ELF_MAGIC
0909   uchar elf[12];
0910   ushort type;
0911   ushort machine;
0912   uint version;
0913   uint entry;
0914   uint phoff;
0915   uint shoff;
0916   uint flags;
0917   ushort ehsize;
0918   ushort phentsize;
0919   ushort phnum;
0920   ushort shentsize;
0921   ushort shnum;
0922   ushort shstrndx;
0923 };
0924 
0925 // Program section header
0926 struct proghdr {
0927   uint type;
0928   uint off;
0929   uint vaddr;
0930   uint paddr;
0931   uint filesz;
0932   uint memsz;
0933   uint flags;
0934   uint align;
0935 };
0936 
0937 // Values for Proghdr type
0938 #define ELF_PROG_LOAD           1
0939 
0940 // Flag bits for Proghdr flags
0941 #define ELF_PROG_FLAG_EXEC      1
0942 #define ELF_PROG_FLAG_WRITE     2
0943 #define ELF_PROG_FLAG_READ      4
0944 
0945 
0946 
0947 
0948 
0949 
