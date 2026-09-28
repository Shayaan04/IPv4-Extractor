# IPv4 Extractor

This project is a C++ program that extracts and validates an IPv4 address with an optional port number from arbitrary text.

The program manually parses the input without using built-in numeric conversion functions, regular expressions, or address-parsing libraries.

## Features

- Extracts IPv4 addresses from surrounding text
- Supports optional port numbers
- Validates octets from `0` to `255`
- Validates ports from `0` to `65535`
- Rejects leading zeros
- Rejects malformed or incomplete addresses
- Continues accepting input until `END` is entered

## Compile

Using `g++`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o ipv4
```

## Run

On Windows PowerShell:

```bash
.\ipv4.exe
```

## Example

Input:

```text
connecting to 192.168.1.1 now
```

Output:

```text
Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
```

## Project Files

- `main.cpp` — C++ source code
- `TESTS.md` — test cases and outputs
- `AI_DISCLOSURE.md` — generative AI usage documentation
- `.gitignore` — excludes compiled and temporary files