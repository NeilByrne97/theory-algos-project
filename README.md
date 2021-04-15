# Theory-of-Algorithms: Sha-512 Algorithm

### Student Name: Neil Byrne
### Student Number: G00343624


## Introduction to SHA512
The National Institute of Standards and Technology (NIST) have a suite of hash algorithms under the 
Secure Hash Standard (SHS) [1]. The one being discussed and impleneted here is SHA-512 which is part 
of a group of hashing algorithms called SHA-2. This algorithm is an iterative, one-way hash function 
that takes an input string of any length and produce a fixed length string called a message digest.
The key feature of the algorithm is that it is pseudo random and any slight change to the message 
will, with a very high probability, result in a completely different message digest. That is to say
that every possible message digest has the same probability to be produced for any given input string.
This algorithm like all other hash function is Collision Resistant: It is not feasible to 
find two distinct input strings that produce the same message digest.
While this is algorithm is not so useful with encryption it is excellent to verify that digital 
signatures on certificates haven't been changed, message authentication, and to generate what 
appears to be random bits. More recently it's used on blockchain for Bitcoin. 

 
# How the program works
Under the standard, each algorithm has it's own basic properties. The table below is the basic properties for SHA-512.

| Algorithm | Message Size (bits) | Block Size (bits) | Word Size (bits) | Message Digest Size (bits) |
| --------- | ------------------- | ----------------- | ---------------- | -------------------------- |
| SHA-512   | <2<sup>128</sup>    | 1024              | 64               | 512                        |


## Preprocessing
Certain steps must be taken before an input can be put through the hash. Each of these steps are outlined in Section 5 Preprocessing.
### 1. Padding The Message
The reason for padding is to ensure that the message is a multiple of 1024 bits

PICTURE OF CODE

### 2. Parse message into the message blocks
Once padded the message must be broke into blocks of 1024 bits 

PICTURE OF CODE


### 3. Set initial hash value
Before the hash computation begines and initial hash value H<sup>(0)</sup> must be set to a 64 bit word. _These words were obtained
by taking the first sixty-four bits of the fractional parts of the square root of the first eight prime numbers_ [1].

PICTURE OF CODE

## Running The Programme
### Environment
The only requirements to run this programme is a C compiler.


# Questions
### 1. Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
The idea of hashes is that they are irreversible. Unlike encryption algorithms which require you to be able to retrieve the value back (to decrypt). Since we do not need to reverse the hash we can lose some information about the original message. All the addition within the algorithm is done without any overflow modulo <2<sup>128</sup>. Modulo can be imagined as a clock face that goes from 0 to N. Meaning everything between 0 and N is modular N. If an arithmetic is performed with modular N, no matter the size of it. You will simply go around the clock face. 

![](images/Modulo1.png)

Even if you know the position of your answer on the clock you stil don't know how many times that calculation went around the clock to get there. 

![](images/Modulo2.png)

If you reach the 64 bit maximum word size then you simply wrap back around again. 
### 2. Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
md5
### 3. How difficult is it to find a hash digest beginning with at least twelve zeros?




# References
1 https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

2 https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1

3

4

5

6