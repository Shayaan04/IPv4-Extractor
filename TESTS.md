# IPv4 Extractor Test Cases

## Instructor-Provided Test Cases

### Test 1

**Input:**
```text
connecting to 192.168.1.1 now
```

**Output:**
```text
Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
```

### Test 2

**Input:**
```text
server=10.0.0.255:8080end
```

**Output:**
```text
Extracted IPv4 address: 10.0.0.255 (decimal value: 167772415, port: 8080)
```

### Test 3

**Input:**
```text
192a168.1.1.1
```

**Output:**
```text
Extracted IPv4 address: 168.1.1.1 (decimal value: 2818638081, port: none)
```

### Test 4

**Input:**
```text
192.168.1.1.
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 5

**Input:**
```text
Connection from 192.168.1.1 refused
```

**Output:**
```text
Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
```

### Test 6

**Input:**
```text
192.168.01.1
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 7

**Input:**
```text
1.2.3.4:99999
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 8

**Input:**
```text
12.34.56
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 9

**Input:**
```text
no number here
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

---

## Additional Test Cases I Used

### Test 1 — Minimum IPv4 Address

**Input:**
```text
0.0.0.0
```

**Output:**
```text
Extracted IPv4 address: 0.0.0.0 (decimal value: 0, port: none)
```

### Test 2 — Maximum IPv4 Address

**Input:**
```text
255.255.255.255
```

**Output:**
```text
Extracted IPv4 address: 255.255.255.255 (decimal value: 4294967295, port: none)
```

### Test 3 — Maximum Valid Port

**Input:**
```text
1.2.3.4:65535
```

**Output:**
```text
Extracted IPv4 address: 1.2.3.4 (decimal value: 16909060, port: 65535)
```

### Test 4 — Port Above Maximum

**Input:**
```text
1.2.3.4:65536
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 5 — Valid Port Zero

**Input:**
```text
1.2.3.4:0
```

**Output:**
```text
Extracted IPv4 address: 1.2.3.4 (decimal value: 16909060, port: 0)
```

### Test 6 — Octet Above Maximum

**Input:**
```text
256.1.1.1
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 7 — Leading Zero in First Octet

**Input:**
```text
01.2.3.4
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 8 — Leading Zero in Port

**Input:**
```text
1.2.3.4:080
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 9 — Empty Octet

**Input:**
```text
1..2.3.4
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 10 — Too Many Octets

**Input:**
```text
1.2.3.4.5
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 11 — Missing Port After Colon

**Input:**
```text
1.2.3.4:
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 12 — Multiple Colons

**Input:**
```text
1.2.3.4::80
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 13 — Address Surrounded by Garbage

**Input:**
```text
abc###192.168.1.1!!!xyz
```

**Output:**
```text
Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
```

### Test 14 — Invalid Candidate Followed by Valid Candidate

**Input:**
```text
999.999.999.999 text 192.168.1.1 end
```

**Output:**
```text
Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
```

### Test 15 — Extra Period After Address

**Input:**
```text
1.2.3.4.
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

### Test 16 — No Address Present

**Input:**
```text
hello world
```

**Output:**
```text
Invalid input: no valid IPv4 address found
```

## Test Result

All instructor-provided and additional test cases produced the expected output.