# System Info CLI

A small Linux command-line utility written in C++ that reads basic system information from the `/proc` filesystem.

## What it does

- Displays hostname
- Displays kernel information
- Displays CPU model and logical CPU count
- Displays memory usage
- Displays system uptime

## Why I built it

This is a learning project for practicing C++ on Linux while understanding how operating-system information is exposed through the `/proc` filesystem.

It is intentionally small. The goal is to understand the implementation rather than hide the work behind a framework.

## Build

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sysinfo
```

## Run

```bash
./sysinfo
```

## Requirements

- Linux
- C++17 compiler

This project is for learning and experimentation.
