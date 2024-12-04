import numpy as np
import re

isTest = False

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
	num_hits = 0

	# convert lines to lists of chars
	char_list  = [list(line) for line in lines]
	lr_diagonals = list()

	for i in range(-len(char_list)+1, len(char_list[0])):
		lr_diagonals.append(np.diagonal(char_list, offset=i))

	# convert back to array of strings
	lr_diagonals = [''.join(line) for line in lr_diagonals]
	num_hits += search_horizontal(lr_diagonals)

	rotated = list(zip(*reversed(lines)))
	rotated = [''.join(line) for line in rotated]
	char_liist = [list(line) for line in rotated]
	rl_diagonals = list()

	for i in range(-len(char_list)+1, len(char_list[0])):
		rl_diagonals.append(np.diagonal(char_list, offset=i))

	# convert back to array of strings
	rl_diagonals = [''.join(line) for line in rl_diagonals]
	num_hits += search_horizontal(rl_diagonals)

	return num_hits

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
	num_hits += search_diagonal(lines)

	print(f"Found: {num_hits}")

if __name__ == "__main__":
	main()
