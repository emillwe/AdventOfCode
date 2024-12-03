test = False
limits = (1, 3)

# determine whether line, a list of ints, is safe
def isSafe(line: list):
	is_incr = set()
	out_of_bounds = False

	for i in range(len(line) - 1):
		curr = line[i]
		next = line[i+1]
		is_incr.add(next > curr)

		# all incr or decr?
		if len(is_incr) > 1:
			return False
			
		delta = abs(curr - next)
		if delta < limits[0] or delta > limits[-1]:
			return False
			
	# end of line: safe!
	return True

def main():
	fn = ""
	if test:
		fn = "test.txt"
	else:
		fn = "input.txt"
	
	with open(fn) as f:
		num_safe = 0
		failed = []
		i = 0
		for line in f:
			# clean line
			line = line[:-1].split(' ')
			line = [int(elem) for elem in line]
			
			if isSafe(line):
				num_safe += 1
			else:
				failed.append(line)
			
			i += 1
		
		# test removals on failed lines
		for line in failed:
			# try removing each failing index, continuing if we get a success
			for ind in range(len(line)):
				# slice line accordingly
				new_line = []
				if ind == len(line) - 1:
					new_line = line[:ind]
				else:
					new_line = line[:ind] + line[ind+1:]
				
				# does removing this element work?
				if isSafe(new_line):
					num_safe += 1
					break # don't count removals twice!
				
		print(f"Safe: {num_safe}")
				
if __name__ == "__main__":
	main()

