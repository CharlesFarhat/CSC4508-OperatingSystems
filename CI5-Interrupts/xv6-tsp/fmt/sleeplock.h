3900 #pragma once
3901 
3902 // Long-term locks for processes
3903 struct sleeplock {
3904   uint locked;       // Is the lock held?
3905   struct spinlock lk; // spinlock protecting this sleep lock
3906 
3907   // For debugging:
3908   char *name;        // Name of lock.
3909   int pid;           // Process holding lock
3910 };
3911 
3912 
3913 
3914 
3915 
3916 
3917 
3918 
3919 
3920 
3921 
3922 
3923 
3924 
3925 
3926 
3927 
3928 
3929 
3930 
3931 
3932 
3933 
3934 
3935 
3936 
3937 
3938 
3939 
3940 
3941 
3942 
3943 
3944 
3945 
3946 
3947 
3948 
3949 
