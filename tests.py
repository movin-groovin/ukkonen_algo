#!/usr/bin/python
#-*- coding: utf-8 -*-



import sys, \
	   random, \
	   time
	   
	   

def main ():
	sequence = []
	number = 100
	
	for val in xrange (0, 26):
		sequence.append (chr (val + ord ('a')))
	for val in xrange (0, 10):
		sequence.append (chr (val + ord ('0')))
	sequence *= 1024 / len (sequence)
	sequence *= 100
	
	random.seed (int (time.time ()))
	random.shuffle (sequence)
	strr = "".join(sequence)
	
	print "String length: {0}".format (len (strr))
	f_out = open ("100000_chars.txt", "a+")
	f_out.write (strr)
	
	return 0



main ()
