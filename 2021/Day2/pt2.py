class sub():
	def __init__(self, **kwargs):
		if not kwargs:
			self.h = 0
			self.d = 0
			self.a = 0
		else:
			self.h = kwargs['h']
			self.d = kwargs['d']
			self.a = kwargs['a']
	
	def __str__(self):
		return f"Horizontal: {self.h} Depth: {self.d} Mult: {self.mult()}"
		
	def move(self, dir: str, dist: int):
		if dir == "forward":
			self.h += dist
			self.d += (self.a * dist)
		elif dir == "up":
			self.a -= dist
		elif dir == "down":
			self.a += dist
	
	def mult(self):
		return self.h * self.d

def main():
	fn = "day2.txt"
#	fn = "test.txt"
	s = sub()
	with open(fn) as f:
		for line in f:
			directions = line.split(' ')
			s.move(dir=directions[0], dist=int(directions[1]))
	
	print(s)
		
if __name__ == "__main__":
	main()
