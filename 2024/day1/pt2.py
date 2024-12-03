#test = True
test = False

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
	
	if test:
		print(line_a)
		print(line_b)
	
	sim_score = 0
	hist = dict()
	
	for elem in line_b:
		if elem not in hist.keys():
			hist[elem] = 1
		else:
			hist[elem] += 1
			
	if test:
		print(hist)
		
	for elem in line_a:
		if elem not in hist:
			continue
		sim_score += elem * hist[elem]
	
	print(f"Similarity: {sim_score}")
	
	
if __name__ == "__main__":
	main()
