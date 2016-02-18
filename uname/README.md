Uname
=====

> Print out system information.

##Goal

Your goal is to modify uname.c to print out more system information.  
Your program's output must EXACTLY match the following.  

```
System name: Linux
Host name: newCS
OS Release: 3.13.0-36-generic
OS Version: #63-Ubuntu SMP Wed Sep 3 21:30:07 UTC 2014
CPU Type: x86_64
```

( A copy of the above output can be found in [UnameOutput.log](UnameOutput.log) )

##Testing

To test if your code meets the output requirements, use the `test.sh` script.

```
./test.sh uname.c
SUCCESS: Output is the same!
```

##uname()

Find information on `uname()` in section 2 of the man pages.

`man -S2 uname`
