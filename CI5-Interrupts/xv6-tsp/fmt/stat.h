4000 #pragma once
4001 
4002 #define T_DIR  1   // Directory
4003 #define T_FILE 2   // File
4004 #define T_DEV  3   // Device
4005 
4006 struct stat {
4007   short type;  // Type of file
4008   int dev;     // File system's disk device
4009   uint ino;    // Inode number
4010   short nlink; // Number of links to file
4011   uint size;   // Size of file in bytes
4012 };
4013 
4014 
4015 
4016 
4017 
4018 
4019 
4020 
4021 
4022 
4023 
4024 
4025 
4026 
4027 
4028 
4029 
4030 
4031 
4032 
4033 
4034 
4035 
4036 
4037 
4038 
4039 
4040 
4041 
4042 
4043 
4044 
4045 
4046 
4047 
4048 
4049 
