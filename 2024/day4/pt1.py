import re

isTest = True

def search_horizontal(lines):
	num_hits = 0
	pattern = "XMAS"
	for line in lines:
		hits = re.findall(pattern, line)
		num_hits += len(hits)
	pattern = "SAMX"
	for line in lines:
		hits = re.findall(pattern, line)
		num_hits += len(hits)
	
	return num_hits
	
def search_vertical(lines):
	rotated = list(zip(*reversed(lines)))
	rotated = [''.join(line) for line in rotated]
	return search_horizontal(rotated)
		
def search_diagonal(lines):
	return

def main():
	fn = "input.txt"
	if isTest:
		fn = "test.txt"
		
	with open(fn) as f:
		lines = list()
		for line in f:
			# clean line
			line = line[:-1]
			lines.append(line)
	
	num_hits = 0
	num_hits += search_horizontal(lines)
	num_hits += search_vertical(lines)
	
if __name__ == "__main__":
	main()
