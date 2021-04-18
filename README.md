# Theory-of-Algorithms: Sha-512 Algorithm

### Student Name: Neil Byrne
### Student Number: G00343624


## Introduction to SHA512
The National Institute of Standards and Technology (NIST) have a suite of hash algorithms under the
Secure Hash Standard (SHS) [1]. The one being discussed and implemented here is SHA-512 which is part
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
Before the hash computation begins and initial hash value H(0) must be set to a 64 bit word. _These words were obtained
by taking the first sixty-four bits of the fractional parts of the square root of the first eight prime numbers_ [1].

PICTURE OF CODE

## Running The Programme
### Environment
The only requirements to run this programme is a C compiler.


# Questions
### 1. Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
The idea of hashes is that they are irreversible. A good hash algorithm is much simpler going forwards than backwards [5]. Unlike encryption algorithms which require you to be able to retrieve the value back (to decrypt). Since we do not need to reverse the hash we can lose some information about the original message. All the addition within the algorithm is done without any overflow modulo <2128. Modulo can be imagined as a clock face that goes from 0 to N. Meaning everything between 0 and N is modular N. If an arithmetic is performed with modular N, no matter the size of it. You will simply go around the clock face.  In the scenario below N=17, there is no real way to dertimine where the answer will land on the clock [3].

![](images/Modulo1.png)

Even if you know the position of your answer on the clock you still don't know how many times that calculation went around the clock to get there. The only way to solve these equations is with brute force for an infeasible amount of time. In order to produce a known length message digest of any size some data will be lost. The input can be any length but the length of the output is set by the algorithm. So, a lot of data is lost making it impossible to determine the orignal data with just resulting hash [4].

![](images/Modulo2.png)

If you reach the 64 bit maximum word size then you simply wrap back around again losing information.
### 2. Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
While there is an infinite about of inputs of varying length to put through SHA512, there is only <2512 possible outputs. This is known as the pigeonhole principle. If n items are put into m containers and n>m. Then at least one of the containers must contain more than one item. Inevitably there are some hashes that could be derived from two distinct input strings. Given the output of a SHA512, it is NOT possible to unambiguously recover the original input used. But given enough time it is possible to compute an input which yields the same output. This is called a Hash Collision. A requirement for all hash algorithms is to make this inevitability to be astronomically unlikely. The probability for a collision in SHA512 is <1.4x1077 [6]. Collision resistance does not mean that no collisions exist, only that they are extremely hard to find. Preimage attacks are an attempt to find an input that has a specific hash value. Older hash algorithms such as MD5 are now broken because of the increase in computing power and can be cracked with this kind of attack.

### 3. How difficult is it to find a hash digest beginning with at least twelve zeros?
Finding a hash with n amount of leading zeros is how the difficulty in Bitcoin mining is adjusted. A high difficulty means that it will take more computing power to mine the same number of blocks. The difficulty adjustment is directly related to the total estimated mining power estimated in the Total Hash Rate (TH/s) chart [7]. Bitcoin uses SHA256 so the message digest is half of SHA512 but the calculation is the same. The maximum target is a SHA512 digest with at least twelve zeros in front, which in hex is:
0x000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF

Then we divide it by the maximum value of a 512-bit number, which in hex is:
0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF

To perform this calculation I used Wolframalpha [8]
This is the probability of a single hash solving a block with twelve leading zeros.
Target / max512 = 3.06818x10-92

Take the reciprocal of the probability to get the average number of hashes performed to solve this block.
1/3.0618x-92 = 3.2594524e+91

# References
1 https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

2 https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1

3 https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/what-is-modular-arithmetic

4 https://privacycanada.net/hash-functions/why-are-hashes-irreversible/

5 https://security.stackexchange.com/questions/11717/why-are-hash-functions-one-way-if-i-know-the-algorithm-why-cant-i-calculate-t

6 https://stackoverflow.com/questions/35954964/is-sha-512-collision-resistant

7 https://www.blockchain.com/en/charts/difficulty

8 https://www.wolframalpha.com/input/?i=0x000000000000ffffffffffffffffffffffffffffffffffffffffffffffffffff+%2F+0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

9

10

11

12