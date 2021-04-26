### Result:
##### open and fopen
+ call 'open' and 'fopen' each 16M times
+ open: 11.5(s)
+ fopen: 13.6(s)

##### read, fscanf. mmap
+ create a file which contains 16MB data
+ read: 2.5(s)
+ fscanf: 0.5(s)
+ mmap: 0.04(s)

##### calloc, malloc
+ Calloc: 0.028809
+ Malloc + Memset: 2.420703
> NOTE: In most cases, they will be the same. In some cases, `calloc()` will do less work because it can skip `memset()` entirely. In other cases, `calloc()` can even cheat and not allocate any memory.
> However, `malloc() + memset()` will always do the full amount of work.
> -- Quoting the answer from Dietrich Epp (on stackoverflow)
