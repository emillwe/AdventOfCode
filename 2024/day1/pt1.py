#test = True
test = False
split_seq = "''"

def main():
	fn = "input.txt"
	
	if test:
		fn = "test.txt"
		
	line_a = list()
	line_b = list()
	
	with open(fn) as f:
		for line in f:
			# clean line
			vals = line.split('\n')
			vals = [elem for elem in vals if elem != '']
			for elem in vals:
				e = elem.split('  ')
				# save line vals
				line_a.append(int(e[0]))
				line_b.append(int(e[1]))
	
	line_a.sort()
	line_b.sort()
	
	if test:
		print(line_a)
		print(line_b)
	
	net_diff = 0
	
	for a, b in zip(line_a, line_b):
		net_diff += abs(a - b)
	
	print(f"Net diff: {net_diff}")
	
	
if __name__ == "__main__":
	main()
