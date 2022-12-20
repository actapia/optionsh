# optionsh

This software is still a work in progress. Previously, the Bash script for reading arguments with optionsh was included in this repository, but the script has been moved to the [optionsh-bash](https://www.github.com/actapia/optionsh-bash) repository.

## Building

You can build this software using the default target of the included Makefile.

```bash
make
```

This software can use features from C++20, but it requires at least some features from C++17. Compilers that do not support the C++17 standard cannot be used to build this software.

## Installation

Installation requires running the `install` target of the included Makefile.

```bash
sudo make install
```