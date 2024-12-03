test = False
limits = (1, 3)

def main():
	fn = ""
	if test:
		fn = "test.txt"
	else:
		fn = "input.txt"
	
	with open(fn) as f:
		num_safe = 0
		
		for line in f:
			# clean line
			line = line[:-1].split(' ')
			line = [int(elem) for elem in line]
			
			is_incr = set()
			out_of_bounds = False
			
			for i in range(len(line) - 1):
				curr = line[i]
				next = line[i+1]
				is_incr.add(next > curr)
				
				# all incr or decr?
				if len(is_incr) > 1:
					break
					
				delta = abs(curr - next)
				if delta < limits[0] or delta > limits[-1]:
					out_of_bounds = True
			
			# safe?
			if len(is_incr) == 1 and not out_of_bounds:
				num_safe += 1
				
	print(f"Safe: {num_safe}")
				
if __name__ == "__main__":
	main()

