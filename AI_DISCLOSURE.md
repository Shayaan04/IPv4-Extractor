# Generative AI Usage Disclosure

## AI Tool Used

I used ChatGPT with the GPT-5 on September 27, 2026.

The AI tool was used to assist with the initial design, implementation,
testing strategy, and explanation of the IPv4 parsing program.

## How AI Was Used

ChatGPT assisted with:

- designing the character-by-character parsing approach;
- separating candidate tokens from surrounding garbage text;
- manually parsing numeric octets;
- validating IPv4 octet ranges;
- validating leading-zero rules;
- parsing and validating an optional port number;
- packing the four IPv4 octets into a 32-bit numeric value;
- developing additional test cases;
- explaining the generated program so that I could review it.

## Initial Prompt

The assignment requirements were provided to ChatGPT, and I asked it to
develop a complete C++ solution while following the restrictions on numeric
conversion functions, regular expressions, and address-parsing libraries.

I also asked ChatGPT to explain the implementation process and provide
testing and documentation guidance.

## AI-Generated Portions

ChatGPT assisted with the initial implementation of:

- `isDigitChar`
- `isTokenChar`
- `parseOctet`
- `parsePort`
- `validateCandidate`
- `extractIPv4`
- the main program input loop
- required output formatting

## My Review

I reviewed the generated program rather than assuming that generated code
was correct simply because it compiled.

I specifically checked:

- IPv4 octet values at the boundaries 0 and 255;
- rejection of values greater than 255;
- valid and invalid port numbers;
- the port boundary of 65535;
- leading-zero handling;
- empty octets;
- missing octets;
- extra periods;
- extra colons;
- malformed ports;
- complete candidate validation;
- extraction of addresses surrounded by garbage characters;
- handling of multiple candidate tokens.

A particularly important rule was confirming that the program rejects:

`192.168.1.1.`

rather than incorrectly extracting:

`192.168.1.1`

The entire consecutive sequence of digits, periods, and colons must be
validated as one candidate.

I also reviewed the case:

`192a168.1.1.1`

The letter `a` separates the input into different candidate sequences.
Therefore, `192` is rejected and `168.1.1.1` is accepted.

## Modifications

Any modifications made after testing will be recorded in this section.

At this stage, the initial AI-assisted implementation is being compiled
and tested against both instructor-provided and student-created cases.

## Testing

Tests include:

- instructor-provided sample cases;
- minimum IPv4 values;
- maximum IPv4 values;
- values beyond allowed limits;
- leading-zero cases;
- malformed syntax;
- valid and invalid ports;
- punctuation adjacent to otherwise valid addresses;
- garbage text;
- multiple candidate tokens.

The complete test list is documented in `TESTS.md`.

## Verification Statement

I reviewed the submitted code and understand the purpose of each function
and the character-by-character parsing strategy.

Numeric values are accumulated manually using:

`value = value * 10 + (digit - '0')`

No prohibited numeric conversion function, regular expression facility,
or address-parsing library is used.

I will verify the final program through testing before submission and will
document any unresolved bugs or unexpected behavior if any remain.