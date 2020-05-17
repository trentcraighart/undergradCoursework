#!/usr/bin/env python

from __future__ import print_function
import sys
import hashlib


BITLEN = 2998041 # Amount needed for 1 in 10 accuracy in 3 hash

def main():
	bitlist3 = [("0" * BITLEN)]
	bitlist5 = [("0" * BITLEN)]

	if getArgsPos("-b") != 0:
		print("Getting from file")
		bitlist3file = open(sys.argv[getArgsPos("-b") + 1], "r")
		bitlist5file = open(sys.argv[getArgsPos("-b") + 2], "r")
		bitlist3[0] = bitlist3file.readline()
		bitlist5[0] = bitlist5file.readline()
	else:
		buildBloomFilterLists(bitlist3, bitlist5)

	testInput(bitlist3, bitlist5)


	if getArgsPos("-b") == 0:
		print("Making new bloomfilter file")
		filterstring3 = open("bloomfilterstring3", "w")
		filterstring5 = open("bloomfilterstring5", "w")
		filterstring3.write(bitlist3[0])
		filterstring5.write(bitlist5[0])
		filterstring3.close()
		filterstring5.close()
		print("Bloomfilter complete")

def testInput(bitlist3, bitlist5):
	print("Testing input file:")
	sys.stdout.flush()	
	inputfile = open(sys.argv[getArgsPos("-i") + 1], "r")
	output3 = open(sys.argv[getArgsPos("-o") + 1], "w")
	output5 = open(sys.argv[getArgsPos("-o") + 2], "w")
	line = inputfile.readline() # to ignore the first line
	line = inputfile.readline()
	while line:
		if not testTripleHash(bitlist3, line):
			output3.write("bad   " + line)			
		else:
			output3.write("maybe " + line)
		
		if not testFiveHash(bitlist5, line):
			output5.write("bad   " + line)			
		else:
			output5.write("maybe " + line)
		line = inputfile.readline()
	print("Done")
	output3.close()
	output5.close()



#Will build bloomfilter lists for 3 hashes and 5 hashes
#First input will be the bitlist for the 3 hash
#Second input will be the bitlist for the 5 hash
def buildBloomFilterLists(bitlist3, bitlist5):
	print("Building bloomfilters:\n", end='')
	sys.stdout.flush()
	passwordlist = open(sys.argv[getArgsPos("-d") + 1], "r")
	line = passwordlist.readline()
	i = 1
	while line:
		if i % 1000 == 0:
			print(i)
		i = i + 1
		tripleHashBitString(bitlist3, line)
		fiveHashBitString(bitlist5, line)
		line = passwordlist.readline()
	print(" Done")
	passwordlist.close()


def testTripleHash(bitlist3, line):
	if bitlist3[0][int(hashlib.sha256(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	if bitlist3[0][int(hashlib.sha224(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	if bitlist3[0][int(hashlib.sha1(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	return False

def tripleHashBitString(bitlist3, line):
	val = int(hashlib.sha256(line).hexdigest(), 16) % BITLEN
	bitlist3[0] = bitlist3[0][:val] + "1" + bitlist3[0][(val+1):]
	val = int(hashlib.sha224(line).hexdigest(), 16) % BITLEN
	bitlist3[0] = bitlist3[0][:val] + "1" + bitlist3[0][(val+1):]	
	val = int(hashlib.sha1(line).hexdigest(), 16) % BITLEN
	bitlist3[0] = bitlist3[0][:val] + "1" + bitlist3[0][(val+1):]


def testFiveHash(bitlist5, line):
	if bitlist5[0][int(hashlib.sha256(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	if bitlist5[0][int(hashlib.sha224(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	if bitlist5[0][int(hashlib.sha1(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	if bitlist5[0][int(hashlib.sha384(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	if bitlist5[0][ int(hashlib.md5(line).hexdigest(), 16) % BITLEN] == "0":
		return True
	return False

def fiveHashBitString(bitlist5, line):
	val = int(hashlib.sha256(line).hexdigest(), 16) % BITLEN
	bitlist5[0] = bitlist5[0][:val] + "1" + bitlist5[0][(val+1):]
	val = int(hashlib.sha224(line).hexdigest(), 16) % BITLEN
	bitlist5[0] = bitlist5[0][:val] + "1" + bitlist5[0][(val+1):]	
	val = int(hashlib.sha1(line).hexdigest(), 16) % BITLEN
	bitlist5[0] = bitlist5[0][:val] + "1" + bitlist5[0][(val+1):]
	val = int(hashlib.sha384(line).hexdigest(), 16) % BITLEN
	bitlist5[0] = bitlist5[0][:val] + "1" + bitlist5[0][(val+1):]
	val = int(hashlib.md5(line).hexdigest(), 16) % BITLEN
	bitlist5[0] = bitlist5[0][:val] + "1" + bitlist5[0][(val+1):]


# Will take flag as input, will return the position of that flag in input
# python bloomfilter.py -c hello -j world -p 
# getArgsPos(-c)   return 1
def getArgsPos(flag):
	arguments = len(sys.argv)
	for x in xrange(1,arguments):
		if sys.argv[x] == flag:
			return x
	print("flag doesn't exist " + str(flag))
	return 0



main()
