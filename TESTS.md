# IPv4 Extractor Test Cases

## Instructor Sample Tests

| Input | Expected Result |
|---|---|
| `connecting to 192.168.1.1 now` | Valid: `192.168.1.1`, no port |
| `server=10.0.0.255:8080end` | Valid: `10.0.0.255`, port `8080` |
| `192a168.1.1.1` | Valid: `168.1.1.1`, no port |
| `192.168.1.1.` | Invalid |
| `Connection from 192.168.1.1 refused` | Valid: `192.168.1.1`, no port |
| `192.168.01.1` | Invalid |
| `1.2.3.4:99999` | Invalid |
| `12.34.56` | Invalid |
| `no number here` | Invalid |

## Valid Boundary Tests

| Input | Expected Result |
|---|---|
| `0.0.0.0` | Valid |
| `255.255.255.255` | Valid |
| `1.2.3.4:0` | Valid |
| `1.2.3.4:65535` | Valid |
| `255.255.255.255:65535` | Valid |

## Invalid Octet Tests

| Input | Expected Result |
|---|---|
| `256.1.1.1` | Invalid |
| `1.256.1.1` | Invalid |
| `1.1.256.1` | Invalid |
| `1.1.1.256` | Invalid |
| `999.1.1.1` | Invalid |

## Leading Zero Tests

| Input | Expected Result |
|---|---|
| `01.2.3.4` | Invalid |
| `1.02.3.4` | Invalid |
| `1.2.03.4` | Invalid |
| `1.2.3.04` | Invalid |
| `1.2.3.4:080` | Invalid |
| `1.2.3.4:00` | Invalid |

## Structural Tests

| Input | Expected Result |
|---|---|
| `1.2.3` | Invalid |
| `1.2.3.4.5` | Invalid |
| `1..2.3.4` | Invalid |
| `.1.2.3.4` | Invalid |
| `1.2.3.4.` | Invalid |
| `1.2.3.4:` | Invalid |
| `1.2.3.4::80` | Invalid |
| `1.2.3.4:80:90` | Invalid |

## Invalid Port Tests

| Input | Expected Result |
|---|---|
| `1.2.3.4:65536` | Invalid |
| `1.2.3.4:99999` | Invalid |
| `1.2.3.4:123456` | Invalid |
| `1.2.3.4:00080` | Invalid |

## Garbage and Multiple Candidate Tests

| Input | Expected Result |
|---|---|
| `abc192.168.1.1xyz` | Valid: `192.168.1.1` |
| `abc###192.168.1.1!!!xyz` | Valid: `192.168.1.1` |
| `999.999.999.999 text 192.168.1.1 end` | Valid: `192.168.1.1` |
| `hello world` | Invalid |
| `...` | Invalid |
| `:::` | Invalid |

## Test Verification

Each test should be run manually and compared against the expected result.

After testing, record whether each case passed or failed.