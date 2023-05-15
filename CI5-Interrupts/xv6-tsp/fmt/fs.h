4050 #pragma once
4051 
4052 // On-disk file system format.
4053 // Both the kernel and user programs use this header file.
4054 
4055 
4056 #define ROOTINO 1  // root i-number
4057 #define BSIZE 512  // block size
4058 
4059 // Disk layout:
4060 // [ boot block | super block | log | inode blocks |
4061 //                                          free bit map | data blocks]
4062 //
4063 // mkfs computes the super block and builds an initial file system. The
4064 // super block describes the disk layout:
4065 struct superblock {
4066   uint size;         // Size of file system image (blocks)
4067   uint nblocks;      // Number of data blocks
4068   uint ninodes;      // Number of inodes.
4069   uint nlog;         // Number of log blocks
4070   uint logstart;     // Block number of first log block
4071   uint inodestart;   // Block number of first inode block
4072   uint bmapstart;    // Block number of first free map block
4073 };
4074 
4075 #define NDIRECT 12
4076 #define NINDIRECT (BSIZE / sizeof(uint))
4077 #define MAXFILE (NDIRECT + NINDIRECT)
4078 
4079 // On-disk inode structure
4080 struct dinode {
4081   short type;           // File type
4082   short major;          // Major device number (T_DEV only)
4083   short minor;          // Minor device number (T_DEV only)
4084   short nlink;          // Number of links to inode in file system
4085   uint size;            // Size of file (bytes)
4086   uint addrs[NDIRECT+1];   // Data block addresses
4087 };
4088 
4089 
4090 
4091 
4092 
4093 
4094 
4095 
4096 
4097 
4098 
4099 
4100 // Inodes per block.
4101 #define IPB           (BSIZE / sizeof(struct dinode))
4102 
4103 // Block containing inode i
4104 #define IBLOCK(i, sb)     ((i) / IPB + sb.inodestart)
4105 
4106 // Bitmap bits per block
4107 #define BPB           (BSIZE*8)
4108 
4109 // Block of free map containing bit for block b
4110 #define BBLOCK(b, sb) (b/BPB + sb.bmapstart)
4111 
4112 // Directory is a file containing a sequence of dirent structures.
4113 #define DIRSIZ 14
4114 
4115 struct dirent {
4116   ushort inum;
4117   char name[DIRSIZ];
4118 };
4119 
4120 
4121 
4122 
4123 
4124 
4125 
4126 
4127 
4128 
4129 
4130 
4131 
4132 
4133 
4134 
4135 
4136 
4137 
4138 
4139 
4140 
4141 
4142 
4143 
4144 
4145 
4146 
4147 
4148 
4149 
