import numpy as np
from enum import Enum

isTest = True

class direction(Enum):
	NORTH = 0
	EAST = 1
	SOUTH = 2
	WEST = 3

class map():
	dirs = [direction.NORTH,
			direction.EAST,
			direction.SOUTH,
			direction.WEST]
	dir_index = 0
	grid = list()
	obstacles = set()
	visited = set()
	x = 0
	y = 0
	
	def __init__(self, fn):
		with open(fn) as f:
			for i, line in enumerate(f):
				this_line = list()
				for j, c in enumerate(line):
					if c == '\n':
						continue
					if c == '#': # obstacle
						self.obstacles.add((i, j))
					elif c == '^':
						self.y = i
						self.x = j
					this_line.append(c)
				self.grid.append(this_line)
		f.close()
		
	def __str__(self):
		result = ""
		for line in self.grid:
			result = result + ''.join(line) + '\n'
		return result
		
	def show_obstacles(self):
		print("Obstacles:")
		for t in self.obstacles:
			print(t)
		
	def show_guard(self):
		print("Guard:")
		print(f"{self.y}, {self.x}")
		
	def show_dir(self):
		print("Direction:")
		print(self.dirs[self.dir_index])
		
	def set_loc(self, x, y):
		self.x = x
		self.y = y
	
	def guard_in_bounds(self):
		nrows, ncols = np.shape(self.grid) # N rows x M columns
		return (self.y >= 0 and self.y < nrows and self.x >= 0 and self.x < ncols)
	
	def is_obstacle(self, loc):
#		i, j = loc
#		return self.grid[i][j] == '#'
		return loc in self.obstacles
		
	# get direction of guard
	def guard_dir(self):
		return self.dirs[self.dir_index % len(self.dirs)]
		
	# move till guard walks off map
	def move_guard(self, quiet=True):
		is_in_bounds = self.guard_in_bounds()
		while is_in_bounds:
			self.visited.add((self.y, self.x)) # been there
			if not quiet:
				print(f"Guard at {self.y, self.x}")
			
			dir = self.guard_dir()
			# TODO: check obstacle before movement!!
			if dir == direction.NORTH:
                if not quiet:
                    print("North")
				self.y -= 1
			elif dir == direction.EAST:
                if not quiet:
                    print("North")
				self.x += 1
			elif dir == direction.SOUTH:
				if not quiet:
                    print("North")
				self.y += 1
			elif dir == direction.WEST:
				if not quiet:
                    print("North")
				self.x -= 1
			else:
				print(f"Direction: {dir}")
			
			# still in bounds?
			is_in_bounds = self.guard_in_bounds()
			
			# hit an obstacle?
			if self.is_obstacle((self.y, self.x)):
				if not quiet:
					print(f"Hit obstacle at {self.x}, {self.y}")
				# turn right 90 deg. and continue
				self.dir_index += 1
				
		# out of bounds
		return
		
	def num_visited(self):
		return len(self.visited)
		
def main():
	fn = "input.txt"
	if isTest:
		fn = "test.txt"
		
	m = map(fn)
	print(m)
	m.show_obstacles()
	m.show_guard()
	m.show_dir()
	m.move_guard(quiet=False)
#	print(m.num_visited())
	
if __name__ == ("__main__"):
	main()
