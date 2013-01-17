echo -n -e \\x01"H" | nc 127.0.0.1 9999 | od -c
