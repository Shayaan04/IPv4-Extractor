#include <iostream>
#include <string>

using namespace std;

// Returns true if c is a digit from 0 through 9.
bool isDigitChar(char c)
{
    return c >= '0' && c <= '9';
}

// Returns true if the character is allowed to be part of
// an IPv4 candidate token.
bool isTokenChar(char c)
{
    return isDigitChar(c) || c == '.' || c == ':';
}

// Parses one IPv4 octet.
// Valid octets:
// 0
// 1
// 10
// 255
//
// Invalid octets:
// 00
// 01
// 256
// 1234
bool parseOctet(const string& token, size_t& pos, int& value)
{
    if (pos >= token.length() || !isDigitChar(token[pos]))
    {
        return false;
    }

    size_t start = pos;

    value = 0;
    int digitCount = 0;

    while (pos < token.length() && isDigitChar(token[pos]))
    {
        value = value * 10 + (token[pos] - '0');

        digitCount++;
        pos++;

        if (digitCount > 3)
        {
            return false;
        }
    }

    // Leading zeros are not allowed unless the octet is exactly 0.
    if (digitCount > 1 && token[start] == '0')
    {
        return false;
    }

    // IPv4 octets must be between 0 and 255.
    if (value > 255)
    {
        return false;
    }

    return true;
}

// Parses an optional port.
//
// Valid examples:
// 0
// 80
// 8080
// 65535
//
// Invalid examples:
// 00
// 080
// 65536
// 123456
bool parsePort(const string& token, size_t& pos, int& value)
{
    if (pos >= token.length() || !isDigitChar(token[pos]))
    {
        return false;
    }

    size_t start = pos;

    value = 0;
    int digitCount = 0;

    while (pos < token.length() && isDigitChar(token[pos]))
    {
        value = value * 10 + (token[pos] - '0');

        digitCount++;
        pos++;

        if (digitCount > 5)
        {
            return false;
        }
    }

    // Leading zeros are not allowed unless the port is exactly 0.
    if (digitCount > 1 && token[start] == '0')
    {
        return false;
    }

    // Maximum valid TCP/UDP port number.
    if (value > 65535)
    {
        return false;
    }

    return true;
}

// Validates an entire candidate token.
//
// Valid:
// 192.168.1.1
// 10.0.0.1:8080
//
// Invalid:
// 192.168.1.1.
// 192.168.01.1
// 1.2.3.4:99999
// 1.2.3.4::80
bool validateCandidate(const string& token,
                       unsigned long& address,
                       int& port)
{
    size_t pos = 0;

    int octets[4];

    // Parse exactly four octets.
    for (int i = 0; i < 4; i++)
    {
        if (!parseOctet(token, pos, octets[i]))
        {
            return false;
        }

        // The first three octets must each be followed by a period.
        if (i < 3)
        {
            if (pos >= token.length() || token[pos] != '.')
            {
                return false;
            }

            pos++;
        }
    }

    // Default means no port was supplied.
    port = -1;

    // If there are characters after the fourth octet,
    // they must begin with exactly one colon followed by a valid port.
    if (pos < token.length())
    {
        if (token[pos] != ':')
        {
            return false;
        }

        pos++;

        if (!parsePort(token, pos, port))
        {
            return false;
        }
    }

    // The whole candidate must be consumed.
    // This prevents partial matches.
    if (pos != token.length())
    {
        return false;
    }

    // Pack the four octets into one 32-bit numeric value.
    address = 0;

    for (int i = 0; i < 4; i++)
    {
        address =
            (address << 8) |
            static_cast<unsigned long>(octets[i]);
    }

    return true;
}

// Returns true if a valid IPv4 address was found.
//
// On success:
// outAddress contains the packed 32-bit IPv4 address.
// outPort contains the port number, or -1 if no port was present.
//
// On failure:
// outAddress = 0
// outPort = -1
bool extractIPv4(const std::string& str,
                 unsigned long& outAddress,
                 int& outPort)
{
    outAddress = 0;
    outPort = -1;

    size_t i = 0;

    while (i < str.length())
    {
        // Skip garbage characters.
        if (!isTokenChar(str[i]))
        {
            i++;
            continue;
        }

        // Beginning of a candidate token.
        size_t start = i;

        // A candidate is a maximal consecutive run of
        // digits, periods, and colons.
        while (i < str.length() && isTokenChar(str[i]))
        {
            i++;
        }

        string candidate = str.substr(start, i - start);

        unsigned long address = 0;
        int port = -1;

        // Validate the entire candidate.
        if (validateCandidate(candidate, address, port))
        {
            outAddress = address;
            outPort = port;

            return true;
        }
    }

    return false;
}

int main()
{
    string input;

    while (true)
    {
        cout << "Enter a string (or 'END' to quit): ";

        if (!getline(cin, input))
        {
            cout << "Program terminated." << endl;
            break;
        }

        if (input == "END")
        {
            cout << "Program terminated." << endl;
            break;
        }

        unsigned long address = 0;
        int port = -1;

        if (extractIPv4(input, address, port))
        {
            // Recover the four octets from the packed address.
            unsigned long a = (address >> 24) & 255UL;
            unsigned long b = (address >> 16) & 255UL;
            unsigned long c = (address >> 8) & 255UL;
            unsigned long d = address & 255UL;

            cout << "Extracted IPv4 address: "
                 << a << "."
                 << b << "."
                 << c << "."
                 << d
                 << " (decimal value: "
                 << address
                 << ", port: ";

            if (port == -1)
            {
                cout << "none";
            }
            else
            {
                cout << port;
            }

            cout << ")" << endl;
        }
        else
        {
            cout << "Invalid input: no valid IPv4 address found"
                 << endl;
        }
    }

    return 0;
}