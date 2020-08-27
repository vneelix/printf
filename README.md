# printf
Function, that display different data types on terminal or file.

- #Realised the following conversions: csp.
- #Realised the following conversions: diouxX with the following flags: hh, h, l and ll.
- #Realised the following conversion: f with the following flags: l and L.
- #Realised %%.
- #Realised the flags #0-+ and space.
- #Realised the minimum field-width.
- #Realised the precision.
- #Realised binary and quaternary systems.
- #Realised write in fd.
- #Flags management: *.

## Examples:
- Basically, the call is similar to the standard printf function, but there are several additional features.
- Syntax : ft_printf("%[parameters][flags][width][.precision][length]type").\
Parameter "~" indicate writing in a file descriptor.\
Attention, fd must be firstly in list of parameters.
```c
printf("%d", 8); \\binary (display 8 at binary num)
printf("%q", 16); \\quaternary (display 16 at quaternary num)
printf("%~d", fd, 10); \\fd (write 10 in file, that have file descriptor - fd in system)
```
