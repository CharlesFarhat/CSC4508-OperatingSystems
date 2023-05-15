4150 #pragma once
4151 
4152 struct file {
4153   enum { FD_NONE, FD_PIPE, FD_INODE } type;
4154   int ref; // reference count
4155   char readable;
4156   char writable;
4157   struct pipe *pipe;
4158   struct inode *ip;
4159   uint off;
4160 };
4161 
4162 
4163 // in-memory copy of an inode
4164 struct inode {
4165   uint dev;           // Device number
4166   uint inum;          // Inode number
4167   int ref;            // Reference count
4168   struct sleeplock lock; // protects everything below here
4169   int valid;          // inode has been read from disk?
4170 
4171   short type;         // copy of disk inode
4172   short major;
4173   short minor;
4174   short nlink;
4175   uint size;
4176   uint addrs[NDIRECT+1];
4177 };
4178 
4179 // table mapping major device number to
4180 // device functions
4181 struct devsw {
4182   int (*read)(struct inode*, char*, int);
4183   int (*write)(struct inode*, char*, int);
4184 };
4185 
4186 extern struct devsw devsw[];
4187 
4188 #define CONSOLE 1
4189 
4190 
4191 
4192 
4193 
4194 
4195 
4196 
4197 
4198 
4199 
