<h1>
	<p align="center">Libft</p>
	<img align="right" alt="Final Grade: 125/ 100%" src="https://img.shields.io/badge/-%20125%20%2F%20100-success">
</h1>
<p align="center">
	<b><i>Your very first own library</b></i>
</p>
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/WudDoo/Libft">
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/WudDoo/Libft">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/WudDoo/Libft">
</p>

## 💡 About

> _This project is your very first project as a student at 42. You will need to recode a few functions of the C standard library as well as some other utility functions that you will use during your whole cursus._

	This project is about coding a C library containing a lot of general purpose
	functions that our future programs would rely on.

My Libft now also includes [my ft_printf](https://github.com/WudDoo/ft_printf) !

<br>

## 🛠️ Usage

### **1. Cloning**

To clone, run:
```ZSH
git clone https://github.com/WudDoo/Libft.git
```


### **2. Compiling**

To compile, run `make` at the root of the `Libft` directory.


### **3. Using it**

To use my ft_printf, simply include its header with the correct path in your code:

```C
#include "<PATH>/libft.h"
```

And compile your code with my static library `libft.a`:

```C
$(CC) $(CFLAGS) $(YOUR_SRCS) $(<PATH>/libft.a)
```
