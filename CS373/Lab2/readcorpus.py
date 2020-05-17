#!/usr/bin/python

import json, sys, getopt, os

def usage():
  print("Usage: %s --file=[filename]" % sys.argv[0])
  sys.exit()

def main(argv):

  file=''
 
  myopts, args = getopt.getopt(sys.argv[1:], "", ["file="])
 
  for o, a in myopts:
    if o in ('-f, --file'):
      file=a
    else:
      usage()

  if len(file) == 0:
    usage()
 
  corpus = open(file)
  urldata = json.load(corpus, encoding="latin1")


  total = 0;
  safe = 0;
  bad = 0;

  undetected = 0;
  falsepos = 0;
  correct = 0;

  ports = [22, 23, 25, 53, 69, 80, 110, 143, 443]
  safeExt = ["css", "flv", "shtml", "mp4"]
  badExt = ["htm", "exe", "zip", "msi", "jar"]

  for record in urldata:
    score = 0;


    # Get age with days and assign points
    if(int(record["domain_age_days"]) != 0):
      score += (1000//int(record["domain_age_days"]))
    else:
      score += 1000

    # Check if the connection is attempting to use a common port, else add points
    if(int(record["port"]) not in ports):
      score += 80

    # Check if the ip address and location are being shown to us
    if(record["ips"] == None):
    	score += 120;
    # Had problems grabing individual ips connections with json file	
    #else:
    	#print record["ips"]
    	#if "null" in record["ips"]:
    		#score += 60

    # Check extensions for the file
    if record["file_extension"] != None:
    	if record["file_extension"] in safeExt:
    		score += -50
    	if record["file_extension"] in badExt:
    		score += 100

    # Check Alexa Rank
    if record["alexa_rank"] != None:
    	score += (1000/(int(record["alexa_rank"])) * -1)
    else: 
    	score += 80

    score += (int(record["num_path_tokens"]) * 10)

    # Determine the score and add to the total
    total += 1;    
    if(score >= 100):
      if int(record["malicious_url"] == 1):
        correct += 1
      else:
      	falsepos += 1
      bad += 1
    else:
      if int(record["malicious_url"] == 0):
      	correct += 1
      else:
      	undetected += 1
      safe += 1
    
    # Assign points for ammount of file extensions


  corpus.close()

  # Print results for the user to look at
  print "----------"
  print "Total number tested: " + str(total)
  print "Safe: " + str(safe)
  print "Bad:  " + str(bad)
  print "----------"
  print "Total missed: " + str(falsepos + undetected)
  print "Undetected: " + str(undetected)
  print "False Positives: " + str(falsepos)
  print "Precentage Correct: " + str((100 * ((total) - (falsepos + undetected))) / total)
  print "----------"
if __name__ == "__main__":
  main(sys.argv[1:])
