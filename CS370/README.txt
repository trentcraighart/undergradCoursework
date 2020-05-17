Trent Vasquez
CS370 - Bloomfilter
10/26/2018

Overview:
Currently the bloom filter has been created from the dictionary provided
There are two sets of commands, one to build a new bloomfilter, and one to use a prexisting filter

Compile Commands:

 + Building new filter  : python bloomfilter.py -d dictionary.txt -i input.txt -o output3.txt output5.txt
 + Using existing filter: python bloomfilter.py -i input.txt -o output.txt -b bloomfilter3 bloomfilter5

Questions

a) Currently I only used cryptographically secure hashfunctions, the following were used:
	sha256
	sha224
	sha1
	sha384
	md5
The output would be a string of hex that I would convert to an integer and mod by the length of the bitarray

b) To check a password is incredibly quick, it takes nanoseconds to compute if its in the filter or not

c) With the dataset and size of the bloomfilter, I have aproximetnly a 1 in 10 chance of a false positive
The only way for there to be a false negative was if it wasn't inside the dictionary fed to the bloomfilter

d) to reduce the rate of false positives:
I could increase the bitarray's length from 2,998,041 (365.97Kib) to 4,070,760 (496.92Kib) for 1 in 20
