# Theory-of-Algorithms

### Student Name: Neil Byrne


## Introduction to SHA512
The National Institute of Standards and Technology (NIST) have a suite of hash algorithms under the 
Secure Hash Standard (SHS). The one being discussed and impleneted here is SHA-512 which is part 
of a group of hasing algorithms called SHA-2. This algorithm is an iterative, one-way hash function 
that takes an input string of any length and produce a fixed length string called a message digest.
The key feature of the algorithm is that it is pseudo random and any slight change to the message 
will, with a very high probability, result in a completely different message digest. That is to say
that every possible message digest has the same probability to be produced for any given input string.
This algorithm like all other hash function is Collision Resistant: It is not feasible to 
find two distinct input strings that produce the same message digest.
While this is algorithm is not so useful with encryption it is excellent to verify that digital 
signatures on certificates haven't been changed, message authentication, and to generate what 
appears to be random bits. More recently it's used on blockchains for cryptocurrency. 

 
## How the program works


https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1