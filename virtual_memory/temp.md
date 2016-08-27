```C
	Write(1, bufp, size);


	struct stat st;
	int fd;
	fd = Open(argv[1], O_RDONLY, 0);
	fstat(fd, &st);
```