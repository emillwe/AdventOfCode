isTest = True

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
	
def main():
	fn = "input.txt"
	if isTest:
		fn = "test.txt"
	
	page_lists = list()
	page_order = dict()
	seen = set()
	
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
		
		if isTest:
			print("pages:")
			for plist in page_lists:
				print(plist)
			print("order:")
			for elem in page_order:
				print(elem, page_order[elem])
				
		# get order
		order = get_order(page_order, seen)
		
		# check for valid orders
		
if __name__ == "__main__":
    main()
