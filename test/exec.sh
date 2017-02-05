#ifeq ($(HOSTTYPE),)
#HOSTTYPE := $(shell uname -m)_$(shell uname -s)
#endif
gcc -Wall -Wextra -shared -fPIC -o libft_malloc_$HOSTTYPE.so ft_malloc.c ft_free.c ft_memcpy.c
set env DYLD_LIBRARY_PATH .
set env DYLD_INSERT_LIBRARIES libft_malloc_$HOSTTYPE.so
set env DYLD_INSERT_FLAT_NAMESPACE 1
