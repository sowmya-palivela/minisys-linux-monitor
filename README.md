# MiniSys — Linux System Monitor

MiniSys is a command-line system monitoring utility written in C for Linux. It demonstrates Linux system interfaces, process information retrieval, memory statistics, and CPU utilization.

## Features

- **System Information:** Displays the operating system, hostname, kernel release, and machine architecture.
- **Memory Monitor:** Reads `/proc/meminfo` to report total, available, and estimated used memory.
- **CPU Monitor:** Estimates CPU utilization using counters from `/proc/stat`.
- **Process Analyzer:** Lists accessible process IDs, process names, and process states.
- **State Filtering:** Filters processes by states such as running, sleeping, stopped, and zombie.
- **Interactive Menu:** Provides a single entry point to access the monitoring modules.

## Technology Stack

- C
- Linux
- GCC
- Linux `/proc` virtual filesystem
- WSL 2 with Ubuntu for Windows development
- Git

## Project Structure

```text
minisys/
├── minisys.c
├── system_info.c
├── memory_info.c
├── cpu_info.c
├── process_info.c
└── README.md
```

## Prerequisites

- A Linux environment, such as Ubuntu
- GCC and standard development tools
- Git (optional, for version control)

Install the required tools on Ubuntu:

```bash
sudo apt update
sudo apt install build-essential git -y
```

## Build

From the project directory, compile the modules:

```bash
gcc -Wall -Wextra -std=c11 system_info.c -o system_info
gcc -Wall -Wextra -std=c11 memory_info.c -o memory_info
gcc -Wall -Wextra -std=c11 cpu_info.c -o cpu_info
gcc -Wall -Wextra -std=c11 process_info.c -o process_info
gcc -Wall -Wextra -std=c11 minisys.c -o minisys
```

## Run

Launch the interactive menu:

```bash
./minisys
```

Select an option to view system information, memory statistics, CPU utilization, or process details.

The process analyzer supports filters for all processes (`A`), running or runnable (`R`), sleeping (`S`), uninterruptible sleep (`D`), stopped (`T`), and zombie (`Z`) processes.

## Concepts Demonstrated

- C functions, structures, pointers, and file handling
- Linux system identification through `uname()`
- CPU accounting using `/proc/stat`
- Memory statistics through `/proc/meminfo`
- Process enumeration and state inspection through `/proc`
- Input validation, error handling, and compiler warnings

## Limitations

MiniSys is an educational prototype. CPU readings are interval-based estimates, process entries may change during scanning, and results reflect the Linux environment visible to the program. In WSL 2, these values may not represent the complete Windows host.

## Future Improvements

- Automated tests and improved error handling
- More detailed process statistics and sorting
- Safer process launching and module integration
- Continuous monitoring and formatted output
- CI checks and additional documentation

## Status

Learning and development project. Features are being tested and refined.
