
def is_brother(kmer_1 , kmer_2, nbr_of_changes):
    	""" tests if kmer1 and kmer2 are brothers:
		brothers: means they are the same except for a number of elements (nbr_of_change)
		"""







def correct1mm(read,	k,	kmerhist,	alpha,	thresh):
	'''	Return	an	error-corrected	version	of	read.		k	=	k-mer	length.
		kmerhist	is	kmer	count	map.		alpha	is	alphabet.		thresh	is
		count	threshold	above	which	k-mer	is	considered	correct.	'''
	#	Iterate	over	k-mers	in	read
	for	i	in xrange(0,	len(read)-(k-1)):
		kmer	=	read[i:i+k]
		#	If	k-mer	is	infrequent...
		if	kmerhist.get(kmer,	0)	<=	thresh:
			#	Look	for	a	frequent	neighbor
			for	newkmer	in	neighbors1mm(kmer,	alpha):
				if	kmerhist.get(newkmer,	0)	>	thresh:
					read	=	read[:i]	+	newkmer	+	read[i+k:]
					break
				#	Return	possibly-corrected	read
	return	read