# Ascii85 Encoder and Decoder
Encodes and decodes Ascii85. 

### What is Ascii85?
**Ascii85**, also called **Base85**, is a form of binary-to-text encoding developed by Paul E. Rutter. 

It uses five ASCII characters to represent four bytes of binary data (making the encoded size 1⁄4 larger than the original, assuming eight bits per ASCII character).

### Compilation
`$ gcc encasc85.c -o encasc85`

`$ gcc decasc85.c -o decasc85`
### Usage
For encoding example.txt:

`$ ./encasc85 < example.txt`

For decoding example.txt:

`$ ./decasc85 < example.txt`
