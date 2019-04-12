# Text Compression - Huffman Coding
Text Lossless Compression using Huffman Coding

## Project Summary
The program takes a text file as input. Then the Huffman binary tree is found and using the arising bitstrings we get a new compressed text file. More about Huffman Coding can be found [here](https://en.wikipedia.org/wiki/Huffman_coding).

## Procedure with Example
### Encoding
Input text: **Madagascar**
As output we got two text files. The first one is the Huffman tree in text form. It is used as a mapper between the original and the encoded text:\
11\
a\
101\
s\
001\
d\
000\
M\
010\
c\
100\
g\
011\
r

It means that a = 11, s = 101, ... , r = 011\
Because of the above, the matching between input and output will be:\
**M**a**d**a**g**a**s**c**a**r\
**000**11**001**11**100**11**101**010**11**011

Someone can say that we are now ready to save those bits into a file and that's it. But wait, computer memories are organized in bytes. Therefore we cannot save any bitstring that is not multiple of 8. Let's look again our bitstring from a different perspective:
00011001**11100111**01010110**11**
It is easy to understand that the problem (if it exists) will be with the last incomplete byte. The solution for this is just to fill the last byte with 0's or 1's:

00011001111001110101011011**000000**

But how we know where the 'garbage' bits start? We state it. Where? At the beginning of the bitstring we always bind a byte for the number of useful bits of the last byte. Apparently this number ∈[0,7).
**00000010**00011001111001110101011011000000

Now we can save the file.

### Decoding
It's the inverse process of the encoding. The program removes the suffix bits using the prefix byte and then removes it too. Then using the mapper file we find the original string

## Time Complexity
### Encoding
#### Finding the Huffman Tree
1. Find all letter's frequencies using a hashtable n*O(1) = O(n)
2. Add each letter into a priority queue n*O(logn) = O(nlogn)
3. Remove the two minimum values from the queue each time and add their new parent.\
n*[O(logn) + O(logn)+ O(logn)] = O(nlogn)

#### Get Encoding Pairs
Finds the bitstring foreach character of the input, traversing until every tree's leaf. Therefore n*O(logn) = O(nlogn)

#### Deleting the Tree
He visit every node. Therefore O(n)

#### Every other function
Obviously takes O(n) time for manipulating the bitstring and saving it.

Considering the above time complexity for the encoding is **O(nlogn)**.

### Decoding
In a similar way takes also O(nlogn).

## Compression Efficiency
input
- text: 1MB

output
- mapper: 2KB
- text: 600KB

Average compression size is about 60% of the original

## Prerequisites
What you need is a C++11 compiler and linker.

g++ tested and working.

## How to Run - Windows
##### Encoding
```
g++ -std=c++11 encode.cpp help_library.cpp -o encode
encode.exe input.txt encoded_text.txt mapper.txt
```
##### Decoding
```
g++ -std=c++11 decode.cpp help_library.cpp -o decode
decode.exe encoded_text.txt mapper.txt output.txt
```

## Built With
C++11
