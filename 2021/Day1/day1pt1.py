def main():
	f = open("pt1.txt")
	prev_depth = 0
	num_incr = 0
	for count, line in enumerate(f):
		# fencepost: no prev. depth
		if count == 0:
			prev_depth = int(line)
			continue
		
		this_depth = int(line)
		
		if this_depth > prev_depth:
			num_incr += 1
		
		prev_depth = this_depth
		
	print(num_incr)
if __name__ == "__main__":
	main()
