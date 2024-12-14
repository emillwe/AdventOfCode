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
	[1, 4, 2, 5, 7]
	[4, 5, 7]
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
				
		
		print_data(page_lists, page_order)
		
		# get order
#		order = get_order(page_order, seen)
#		order.reverse()
#		print("order:", order)
		
		
		# check for valid orders
		for l in page_lists:
			if is_good_line(l, page_order):
#				print("ordered!")
				sum_of_middle_pages += get_middle_page(l)
#			if is_ordered(l, order):
#				print("ordered!")
#				sum_of_middle_pages += get_middle_page(l)
#			else:
#				print("not ordered:", l)
				
		print(f"sum: {sum_of_middle_pages}")
if __name__ == "__main__":
    main()
