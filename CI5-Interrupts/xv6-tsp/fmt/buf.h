3850 #pragma once
3851 
3852 struct buf {
3853   int flags;
3854   uint dev;
3855   uint blockno;
3856   struct sleeplock lock;
3857   uint refcnt;
3858   struct buf *prev; // LRU cache list
3859   struct buf *next;
3860   struct buf *qnext; // disk queue
3861   uchar data[BSIZE];
3862 };
3863 #define B_VALID 0x2  // buffer has been read from disk
3864 #define B_DIRTY 0x4  // buffer needs to be written to disk
3865 
3866 
3867 
3868 
3869 
3870 
3871 
3872 
3873 
3874 
3875 
3876 
3877 
3878 
3879 
3880 
3881 
3882 
3883 
3884 
3885 
3886 
3887 
3888 
3889 
3890 
3891 
3892 
3893 
3894 
3895 
3896 
3897 
3898 
3899 
