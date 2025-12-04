README for linux-system-programming repository
--------------------------------------------------

This repository contains three Linux system programming labs:

1. os-sort-cli
2. system-info-cli
3. file-split-merge-cli

Each folder should contain its own README, but they were missing — this file includes
the combined documentation. You can split the sections manually into per-folder README files.

--------------------------------------------------
1. os-sort-cli — Sorting Utility
--------------------------------------------------
A command-line tool that sorts integers provided by the user using Bubble Sort.
Supports ascending (-a) and descending (-d) modes.

Compile:
    g++ main.cpp argparser.cpp sort.cpp -o sortcli

Run:
    ./sortcli -a 5 2 7 1
    ./sortcli -d 4 9 1

--------------------------------------------------
2. system-info-cli — User & File Information Utility
--------------------------------------------------
Retrieves Linux system information:
- User data via getpwnam()
- File metadata via stat()

Compile:
    g++ main.cpp -o sysinfo

Run:
    ./sysinfo -u root
    ./sysinfo -f /etc/passwd

--------------------------------------------------
3. file-split-merge-cli — File Split & Merge Utility
--------------------------------------------------
Splits a file into four parts and merges them back using POSIX system calls.

Compile:
    g++ main.cpp -o ftool

Split:
    ./ftool split input.bin part1 part2 part3 part4

Merge:
    ./ftool merge part1 part2 part3 part4 restored.bin

--------------------------------------------------
System Concepts Demonstrated
--------------------------------------------------
- CLI argument parsing
- Modular C++ development
- POSIX user and file metadata
- Low-level file descriptors (open, read, write, lseek)
