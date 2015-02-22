#!/usr/bin/python
#-*- coding: utf-8 -*-



import sys, \
	   random, \
	   time
	   
	   

def main ():
	sequence = []
	number = 100
	str_num = 28
	
	
	if len(sys.argv) > 1 and sys.argv[1] == '-h':
		print ("Usage: ./gen_test_data.py len_in_string*36 number_of_strings \n"\
			   "Example: ./gen_test_data.py 10 10 - 3600 char length of data"\
			   "Default: ./gen_test_data.py 28 100"
	    )
		return 0
	
	try:
		if len(sys.argv) > 2:
			number = int (sys.argv[2])
			str_num = int (sys.argv[1])
	except Exception as Exc:
		print "An exception: ", Exc
	
	for val in xrange (0, 26):
		sequence.append (chr (val + ord ('a')))
	for val in xrange (0, 10):
		sequence.append (chr (val + ord ('0')))
	sequence *= str_num
	sequence *= number
	
	random.seed (int (time.time ()))
	random.shuffle (sequence)
	strr = "".join(sequence)
	
	print "String length: {0}".format (len (strr))
	f_out = open ("test_chars.txt", "w+")
	f_out.write (strr)
	
	return 0



main ()
