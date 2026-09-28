# IPv4 Extractor

This project is a C++ program that searches arbitrary text for a valid IPv4
address with an optional port number.

The program validates candidate addresses character by character without
using built-in numeric conversion functions, regular expressions, or
address-parsing libraries.

## Compile

Using g++:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o ipv4