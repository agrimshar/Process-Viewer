This process viewer uses system calls to read the `/proc` directory in Linux and print out all of the currently running process on the machine.

This implimentation uses the same mechanisms as utilities like `ps` or `top` (the Linux version of Windows Task Manager and macOS Activity Monitor).

The output of this program is the exact same as running `ps -eo pid:5,ucmd)`.
