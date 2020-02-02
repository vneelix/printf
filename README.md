# printf
Function, that display different data types on terminal or file.

- #Manage the following conversions: csp.
- #Manage the following conversions: diouxX with the following flags: hh, h, l and ll.
- #Manage the following conversion: f with the following flags: l and L.
- #Manage %%.
- #Manage the flags #0-+ and space.
- #Manage the minimum field-width.
- #Manage the precision.
- #Manage binary and quaternary systems.
- #Manage write in fd.
- #Flags management: *, $ and ’.

## Examples:
- Basically, the call is similar to the standard printf function, but there are several additional features.
- Syntax : ft_printf("%[parameters][flags][width][.precision][length]type").\
Parameter "~" indicate writing in a file descriptor.\
- Attention, fd must be firstly in list of parameters.
```c
printf("%d", 8); \\binary (display 8 at binary num)
printf("%q", 16); \\quaternary (display 16 at quaternary num)
printf("%~d", fd, 10); \\fd (write 10 in file, that have file descriptor - fd in system)
```
