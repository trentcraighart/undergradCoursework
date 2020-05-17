#!/usr/bin/python
##############################
# Programed by Trent Vasquez #
# Programing Assignment 3    #
# CS 331                     #
# Naive Bayes Net            #
##############################

import sys
import io

#This code will remove all capitals and punctuation and write the results
#to a specified file
def refineInput(filename, outputfile):
	f = open(filename)
	contents = f.read()
	#Convert to lowercase
	lowercase = ''
	for character in contents:
		if(ord(character) < 91 and ord(character) > 64):
			character = chr(ord(character) + 32)
		lowercase += character
	#Strip punctuation
	striped = ''
	for character in lowercase:
		#Conditional allowing spaces, lowercase, and the numbers 0 and 1
		if((ord(character) == 32) or (ord(character) > 96 and ord(character) < 123) or (ord(character) == 48 or ord(character) == 49)):
			striped += character
	f.close()
	f = open(outputfile, "w+")
	f.write(striped)
	f.close()

#This will take input from a refined file and build a vocabulary
#of all the words from a - z
def buildVocab(filename):
	f = open(filename)
	contents = f.read() 
	words = contents.split(" ")
	orginized = [words[0]]
	#Removing spaces
	for word in words:
		if word != '':
			orginized.append(word)
	#Orginizing
	orginized.sort()
	orginizedReduced = []
	#Removing Duplicate words
	i = 0
	while(i < len(orginized) - 1):
		if orginized[i] != orginized[i+1]:
			orginizedReduced.append(orginized[i])
		i += 1	
	#Removing numerical words
	i = 0
	while True:
		if(orginizedReduced[i][0] == '0' or orginizedReduced[i][0] == '1'):
			i += 1
		else:
			break
	refined = orginizedReduced[i:]						
	#Convert to string
	newlist = ''
	for word in refined:
		newlist += word
		newlist += ','
	newlist += "classlabel"
	f.close()
	return newlist


#This function will serve to take the conents of a refined file and 
#turn them into vectors of 0's and 1's coresponding to if a word is
#in the sentence
def makeWordVectors(refinedFile, outputfile, originalRefinedList):
	vocabulary = buildVocab(originalRefinedList)
	rf = open(refinedFile)
	of = open(outputfile, "w+")
	of.write(vocabulary + "\n")
	vocabList = vocabulary.split(",")
	totalWords = len(vocabList)
	refinedWords = (rf.read()).split(" ")

	sentence = ['0'] * totalWords
	for word in refinedWords:
		if word == '0' or word == '1':
			sentence[totalWords - 1] = word
			of.write(",".join(sentence))
			of.write("\n")
			sentence = ['0'] * totalWords
		else:
			try:
				index = vocabList.index(word)
				sentence[index] = '1'
			except:
				index = 0
	rf.close()
	of.close()

#takes the preprocessed and refined data in order to build
#the target vector for the naive bayes
def trainingNaiveBayes(preprocessedfile, refinedfile, outputfile):
	totalWords = len(buildVocab(refinedfile).split(','))
	positiveCount = [0] * totalWords
	negativeCount = [0] * totalWords
	wordCount = [0] * totalWords
	f = open(preprocessedfile)
	line = f.readline()
	vocab = line.split(',')
	line = f.readline()
	while line:
		positive = 0
		#check if the comment was positive
		numberArray = line.split(',')
		if numberArray[totalWords - 1][0] == '1':
			positive = 1
		i = 0
		while i < totalWords:
			if numberArray[i][0] == '1':
				wordCount[i] += 1
				if(positive == 1):
					positiveCount[i] += 1
				else:
					negativeCount[i] += 1
			i += 1
		line = f.readline()
	precentageTrue  = []
	precentageFalse = []
	#applied Uniform Dirichlet Priors
	i = 0

	while i < totalWords:
		precentageTrue.append((positiveCount[i]+1) / (wordCount[i] + 2))
		i += 1
	i = 0
	while i < totalWords:		
		precentageFalse.append((negativeCount[i]+1) / (wordCount[i] + 2))
		i += 1
	f.close()
	f = open(outputfile, "w+")

	formatedTrue = ','.join(['{:8f}'.format(x) for x in precentageTrue])
	formatedFalse = ','.join(['{:8f}'.format(x) for x in precentageFalse])	
	f.write(formatedTrue)
	f.write('\n')
	f.write(formatedFalse)
	#'{:4f}'.format(x) for x in precentageFalse
	f.close()

def testBayes(preprocessedfile, inputfile, outputfile):
	f = open(inputfile)
	precentageTrue  = f.readline()
	precentageFalse = f.readline()
	arrayTrue  = precentageTrue.split(',')
	arrayFalse = precentageFalse.split(',')
	totalWords = len(arrayTrue)
	f.close()

	f = open(preprocessedfile)
	vocab = f.readline()
	line = f.readline()
	correct = 0
	incorrect = 0
	while line:
		trueval = 1
		falseval = 1
		templine = line.split(',')
		i = 0
		while i < (totalWords - 1):
			if templine[i] == '1':
				trueval  = trueval * float(arrayTrue[i])
				falseval = falseval * float(arrayFalse[i])
			i += 1
		anwser = '0'
		if(trueval > falseval):
			anwser = '1'
		if templine[totalWords - 1][0] == anwser:
			correct += 1
		else:
			incorrect += 1
		line = f.readline()
	outputstring = ("\nUsing the training set: " + inputfile + "\nUsing the sentences from: " + preprocessedfile)
	outputstring += "\nCorrect " + str(correct)
	outputstring += "\nWrong " + str(incorrect)
	outputstring += "\nPrecentage " + str(float(correct)/float(correct + incorrect))
	f.close()
	f = open(outputfile, "w+")
	f.write(outputstring)
	f.close()
	print(outputstring)


def main():
	refineInput("trainingSet.txt", "refinedTrain.txt")
	makeWordVectors("refinedTrain.txt", "preprocessed_train.txt", "refinedTrain.txt")
	trainingNaiveBayes("preprocessed_train.txt", "refinedTrain.txt", "training_output.txt")
	testBayes("preprocessed_train.txt", "training_output.txt", "final_train_output.txt")

	refineInput("testSet.txt", "refinedTest.txt")
	makeWordVectors("refinedTest.txt", "preprocessed_test.txt", "refinedTrain.txt")
	testBayes("preprocessed_test.txt", "training_output.txt", "final_test_output.txt")

	print("\nFor the Naive Bayes tests, look at the files final_train_output.txt and final_test_output.txt\n")

main()