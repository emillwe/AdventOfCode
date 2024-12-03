def main():
	f = open("pt1.txt")
	window_sz = 3
	prev_depth = 0
	num_incr = 0
	lines = list()
	
	# read each line into list:
	# index = line no.
	for line in f:
		lines.append(line)
	
	for i in range(len(lines) - 2): # stop at 2 lines before last
		if i == 0:
			prev_sum = sum([int(lines[i]), int(lines[i+1]), int(lines[i+2])])
			continue
		this_sum = sum([int(lines[i]), int(lines[i+1]), int(lines[i+2])])
		if this_sum > prev_sum:
			num_incr += 1
		prev_sum = this_sum
	
	print(num_incr)
if __name__ == "__main__":
	main()


