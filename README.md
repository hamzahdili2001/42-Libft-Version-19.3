*This project has been created as part of the 42 curriculum by hhdili.*

# Libft

## Description

Libft is my first own C library, built as part of the 42 curriculum. The idea is simple: C is painful without the standard functions, so instead of just using them, I rewrote them myself to understand how they actually work under the hood. The result is `libft.a`, a static library I can reuse in my future 42 projects.

I wrote everything from scratch, from the first function to the last one, following the Norm and without relying on any external functions beyond the ones allowed in the subject (`malloc`, `free` and `write`).

The library is split in three parts:

**Part 1 - Libc functions**
My own versions of standard libc functions, with the same behavior as the originals but prefixed with `ft_`:

- Character checks and conversion: `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`
- Strings: `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strdup`, `ft_atoi`
- Memory: `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc`

**Part 2 - Additional functions**
Functions that either don't exist in libc or exist in a different form:

- `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`
- `ft_strmapi`, `ft_striteri`
- `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

**Part 3 - Linked lists**
Functions to manipulate lists built on the `t_list` struct defined in `libft.h`:

- `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`
- `ft_lstsize`, `ft_lstlast`
- `ft_lstdelone`, `ft_lstclear`
- `ft_lstiter`, `ft_lstmap`

All the mandatory functions from the subject are implemented.

## Instructions

Everything is compiled with `cc` and the flags `-Wall -Wextra -Werror`, and the library is created with `ar`. The `libft.a` file ends up at the root of the repository.

**Build the library**

```
make
```

**Other Makefile rules**

```
make clean    # removes the object files
make fclean   # removes the object files and libft.a
make re       # fclean + all
```

**Use it in your own program**

Include the header in your code:

```c
#include "libft.h"
```

Then compile and link against the library:

```
cc -Wall -Wextra -Werror main.c -L. -lft
```

## Resources

**References**

- The `man` pages for each libc function (`man 3 strlen`, `man 3 memmove`, etc.), which I used as the reference for the expected behavior
- The 42 Norm
- The Libft subject itself
# 42-Libft-Version-19.3
# 42-Libft-Version-19.3
