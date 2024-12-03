import re

isTest = True

def main():
	fn = "input.txt"
	if isTest:
		fn = "test.txt"
	
	with open(fn) as f:
		l = f.read()
		
		pattern = "mul\\(\\d*,\\d*\\)"
		result = re.findall(pattern, l)
		print(result)
		
	
		
	
if __name__ == "__main__":
	main()
