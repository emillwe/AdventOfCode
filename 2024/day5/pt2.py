import copy

isTest = False

def read_pages(f):
	result = list()
	for line in f:
		line = line.split(',')
		line = [int(page) for page in line]
		result.append(line)
	return result

def get_order(page_order, seen):
	order = list()
	while len(order) < len(seen):
		next = 0
		s = set.intersection(*(page_order.values()))
		if s:
			next = s.pop()
		else:
			for k, v in page_order.items():
				if not v:
					next = k
					page_order.pop(k)
					break
		order.append(next)
		if next in page_order.keys():
			page_order.pop(next)
		else:
			for s in page_order.values():
				if next in s:
					s.remove(next)
	return order
	
def is_ordered(l, order):
	j = 0
	target = l[j]
	for elem in order:
		if elem == target:
			j += 1
			if j == len(l):
				return True
			target = l[j]
	return False
	
def is_good_line(l, page_order):
	for i in range(len(l) - 1, 0, -1):
		this_page = l[i]
		for j in range(i-1, -1, -1):
			next = l[j]
			if this_page not in page_order:
				page_order[this_page] = set()
			if next in page_order[this_page]:
				return False
	return True
	
def get_middle_page(l):
	return l[len(l)//2]

def print_data(page_lists, page_order):
	for l in page_lists:
		print(l)
	print()
	for k, v in page_order.items():
		print(k, v)
		
def order_line(l, page_order):
	result = list()
	sets = list()
	order = dict()
	
	for page in l:
		order[page] = set.intersection(page_order[page], set(l))
		sets.append(order[page])
	
	while len(result) < len(l):
		next = -1
		s = set.intersection(*sets)
		if s:
			next = s.pop()
		else:
			for k, v in order.items():
				if not v:
					next = k
					order.pop(k)
					break
		result.append(next)
		
		if next in order.keys():
			order.pop(next)
			
		for s in order.values():
			if next in s:
				s.remove(next)
				
	result.reverse()
	return result
	
def main():
	fn = "input.txt"
	if isTest:
		fn = "test.txt"
	
	page_lists = list()
	page_order = dict()
	seen = set()
	sum_of_middle_pages = 0
	
	with open(fn) as f:
		for line in f:
			if '|' in line:
				line = line.split('|')
				line = [int(page) for page in line]
				if line[0] not in page_order:
					page_order[line[0]] = set([line[1]])
					seen.add(line[0])
					seen.add(line[1])
				else:
					page_order[line[0]].add(line[1])
			elif line == '\n' or '|' not in line:
				page_lists = read_pages(f)
		f.close()
				
#		print_data(page_lists, page_order)
		
		# check for invalid orders
		for l in page_lists:
			if not is_good_line(l, page_order):
				ordered = order_line(l, page_order)
				sum_of_middle_pages += get_middle_page(ordered)
				
		print(f"sum: {sum_of_middle_pages}")
		
if __name__ == "__main__":
    main()
