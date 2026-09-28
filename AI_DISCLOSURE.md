# Generative AI Usage Disclosure

## AI Tool Used

I used **ChatGPT with the GPT-5.6 Sol model** on **September 27, 2026**.

I used ChatGPT to assist with the initial implementation of the IPv4 extraction program, understand the generated code, develop test cases, troubleshoot compilation issues, and review the program against the assignment requirements.

---

# Prompts Used

## Prompt 1 — Initial Assignment Assistance

I provided the assignment requirements to ChatGPT and asked:

> What is the goal of the assignment and how can I start with implementing the code?

This was used to obtain an initial C++ implementation and an outline of the development, testing, and documentation process.

---

## Prompt 2 — Development and Testing Process

I asked:

> Walk me through the full process of creating the repository, adding the code, compiling it, running the instructor sample cases, testing additional edge cases, diagnosing problems, documenting corrections, creating the test file, and pushing the final project to GitHub.

This prompt was used to make sure I did not miss any of the assignment requirements and to understand how to move from the initial generated code to a tested and documented submission.

---

## Prompt 3 — Understanding the Parsing Strategy

I asked ChatGPT to explain:

> Explain the overall strategy used by this program. In particular, explain how it scans garbage text, identifies candidate tokens, validates the entire token instead of accepting a partial match, and decides whether an IPv4 address is valid.

This helped me understand why the program treats consecutive digits, periods, and colons as a complete candidate token.

One important example was:

`192.168.1.1.`

The parser must reject the entire candidate instead of accepting only:

`192.168.1.1`

because the extra period is directly adjacent to the address.

---

## Prompt 4 — Understanding Manual Number Parsing

I asked:

> Explain how `parseOctet` converts characters into an integer without using `stoi`, `atoi`, or another conversion function. Also explain how the function checks the number of digits, leading zeros, and the range 0 through 255.

This helped me understand the numeric accumulation statement:

`value = value * 10 + (token[pos] - '0');`

For example, when reading `192`, the value develops as:

- `1`
- `19`
- `192`

The function also rejects octets with more than three digits, values greater than 255, and leading zeros such as `01`.

---

## Prompt 5 — Understanding Port Validation

I asked:

> Explain how the optional port is parsed and why values such as `65535` are valid while `65536`, `080`, an empty port, or a second colon must cause the entire candidate to be rejected.

This helped me verify that the port must contain 1–5 digits, have a value from 0 through 65535, and follow the same leading-zero rule as IPv4 octets.

---

## Prompt 6 — Understanding `validateCandidate`

I asked:

> Walk through `validateCandidate` line by line and explain how it guarantees exactly four octets, exactly three periods between them, an optional valid port, and no extra period or colon at the end.

This helped me understand why the final check that the parser has reached the end of the candidate is necessary.

Without that check, a program could incorrectly accept a valid-looking part of a malformed token.

---

## Prompt 7 — Understanding `extractIPv4`

I asked:

> Explain `extractIPv4` step by step. Show how it skips garbage characters, forms complete candidate tokens, rejects an invalid candidate, and continues searching for another candidate later in the same line.

This helped me understand inputs such as:

`999.999.999.999 text 192.168.1.1 end`

The first candidate is invalid, but the parser continues scanning and finds the later valid address.

---

## Prompt 8 — Reviewing Edge Cases

I asked:

> Review this IPv4 parser for edge cases. Focus on octet boundaries, leading zeros, malformed periods and colons, invalid ports, extra characters directly adjacent to an address, multiple candidate tokens, and cases where an apparently valid address is contained inside a larger invalid candidate.

This was used to develop additional tests beyond the instructor-provided examples.

---

## Prompt 9 — Port Boundary Verification

During testing, I entered:

> Enter a string (or 'END' to quit): 1.2.3.4:65536  
> Invalid input: no valid IPv4 address found
>
> is this correct output

ChatGPT confirmed that this result was correct because `65535` is the highest allowed port number.

---

## Prompt 10 — Compilation Troubleshooting

When compiling the program, I received:

> undefined reference to `WinMain@16`

I provided the compiler output to ChatGPT and asked for help diagnosing the problem.

ChatGPT explained that the linker was not finding the normal C++ `main()` entry point and suggested checking that the saved source file contained:

`int main()`

and that the correct file was being compiled.

---

## Prompt 11 — Execution Troubleshooting

After an unsuccessful compilation, I attempted to run:

`.\ipv4.exe`

and PowerShell reported that the program could not be found.

I provided that error to ChatGPT. ChatGPT explained that the executable did not exist because the previous compilation had not completed successfully and that the source first needed to compile successfully.

---

## Prompt 12 — Test Documentation

I asked:

> Create the test file in a different format: first show all instructor-provided test cases and their outputs, and then show the additional test cases I used and their outputs.

This was used to organize `TESTS.md` so the instructor-provided cases and my additional verification cases could be reviewed separately.

---

# AI-Generated Portions

ChatGPT assisted with the initial generation of the following program components:

- `isDigitChar`
- `isTokenChar`
- `parseOctet`
- `parsePort`
- `validateCandidate`
- `extractIPv4`

ChatGPT also assisted with generating possible edge cases and documentation structure.

# Student-Generated Portions

These were done by me after reviewing the code provided by ChatGPT.

- the continuous input loop in `main`
- construction of the 32-bit IPv4 numeric value
- required output formatting

---

# My Review of the Generated Code

I reviewed the generated code function by function rather than relying only on whether it compiled.

I checked that the program follows the required candidate-token rule. Consecutive digits, periods, and colons are treated as one candidate, and that complete candidate must be valid.

For example:

`192.168.1.1.`

must be rejected rather than shortened to:

`192.168.1.1`

I also reviewed:

`192a168.1.1.1`

Because `a` is not a valid candidate character, it separates the input. The first candidate `192` is not a complete IPv4 address, while `168.1.1.1` is valid.

---

# Numeric Parsing Review

The program does not use prohibited string-to-number conversion functions.

Each digit is accumulated manually using:

`value = value * 10 + (token[pos] - '0');`

I verified that the octet parser checks:

- at least one digit;
- no more than three digits;
- values no greater than 255;
- no leading zero unless the octet is exactly `0`.

I verified that the port parser checks:

- at least one digit;
- no more than five digits;
- values no greater than 65535;
- no leading zero unless the port is exactly `0`.

---

# Testing Performed

I tested the instructor-provided examples as well as additional cases designed to check boundaries and malformed input.

Examples included:

- `0.0.0.0`
- `255.255.255.255`
- `256.1.1.1`
- `01.2.3.4`
- `1..2.3.4`
- `1.2.3.4.5`
- `1.2.3.4:0`
- `1.2.3.4:65535`
- `1.2.3.4:65536`
- `1.2.3.4:080`
- `1.2.3.4:`
- `1.2.3.4::80`
- `abc###192.168.1.1!!!xyz`
- `999.999.999.999 text 192.168.1.1 end`

The full list of tests and outputs is recorded in `TESTS.md`.

---

# Modifications and Troubleshooting

The initial AI-assisted implementation was reviewed against the assignment requirements and then compiled and tested.

During development, I encountered an `undefined reference to WinMain@16` linker error. I checked that the source file contained the correct C++ `int main()` function and that the intended version of `main.cpp` had been saved before recompiling.

I also attempted to run `ipv4.exe` before a successful executable had been produced. After identifying this, I recompiled the source successfully before executing the program.

The parsing logic was then tested using both the instructor-provided examples and additional boundary and malformed-input cases.

---

# Verification Statement

I reviewed the final submitted program and understand the purpose of each major function.

I understand that:

- `isDigitChar` determines whether a character is a numeric digit;
- `isTokenChar` identifies characters that can belong to an IPv4 candidate;
- `parseOctet` manually parses and validates one IPv4 octet;
- `parsePort` manually parses and validates an optional port;
- `validateCandidate` requires an entire candidate to satisfy the grammar;
- `extractIPv4` scans through the input and checks each candidate;
- `main` repeatedly reads input and formats the required output.

I understand why the program validates complete candidate tokens rather than accepting valid-looking substrings.

I also verified that the implementation does not use prohibited numeric-conversion functions, regular expressions, or address-parsing libraries.

The program was tested with instructor-provided cases and additional edge cases. At the time of submission, I am not aware of any unresolved functional bugs in the cases tested.