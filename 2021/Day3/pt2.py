num_bits = 5

# class for traversal of binary strings
class bin_node:
	def __init__(self):
		self.vals = list()
		self.zero = None
		self.one = None
		
	def __str__(self):
#		return f"{''.join([val for val in self.vals])}"
		return str(self.vals)
		
class diagnostics:
	def __init__(self):
		self.lines = list()
		self.bit_count = {i: [0, 0] for i in range(num_bits)}
		self.gamma = ""
		self.epsilon = ""
		self.power = 0
		self.o2_rating = "not found"
	
	def __str__(self):
		return f"{str(self.bit_count)} Gamma: {self.gamma} Epsilon: {self.epsilon} Power: {self.power}"
	
	def save_line(line):
		self.lines.append(line)
		
	# read one line of bits
	def read_bits(self, bits: str):
		for i in range(num_bits):
			this_bit = bits[i]
			self.bit_count[i][int(this_bit)] += 1
			
	# gamma, epsilon: most/least common bit in each position
	# update string vals
	def get_gamma_epsilon_str(self):
		gamma = list()
		epsilon = list()
		for count in self.bit_count.values():
			if count[0] > count [1]:
				gamma.append('0')
				epsilon.append('1')
			else:
				gamma.append('1')
				epsilon.append('0')
		gamma_str = ''.join([c for c in gamma])
		epsilon_str = ''.join([c for c in epsilon])
		
		self.gamma = gamma_str
		self.epsilon = epsilon_str
		
		# save as decimal
#		self.gamma = int(gamma_str, base = 2)
#		self.epsilon = int(epsilon_str, base = 2)
		
	def get_power_consumption(self):
		self.power = self.gamma * self.epsilon
	
	def get_o2_rating(self, root_zero, root_one):
		this_node = None
		these_vals = list()
		num_zeros = 0
		num_ones = 0
		
		for i in range(num_bits - 1):
			# start at root for first bit
			if i == 0:
				# todo: use num_zeros, num_ones as before to initialize those variables
				if self.bit_count[i][0] > self.bit_count[i][1]:
					this_node = root_zero
				else:
					this_node = root_one
			else:
				for val in this_node.vals:
					if val[i] == '0':
						num_zeros += 1
					else: # val[i] == '1'
						num_ones += 1
						
			these_vals = this_node.vals
			print(f"Now at: {this_node}")
			
			if len(these_vals) == 1: # done?
				self.o2_rating = these_vals
				return
				
#			if self.bit_count[i+1][0] > self.bit_count[i+1][1]:
			print(f"0: {num_zeros} 1: {num_ones}")
			if num_zeros > num_ones:
				this_node = this_node.zero
			else:
				this_node = this_node.one
		
		# didn't return: check last
		print(f"Now at: {this_node}")
		self.o2_rating = this_node.vals
		return

def main():
	fn = "test.txt"
#	fn = "day3.txt"
	d = diagnostics()
	root_zero = bin_node()
	root_one = bin_node()
	
	with open(fn) as f:
		for line in f:
			d.read_bits(line)
			
			# place this binary num in tree
			this_node = root_zero
			for i in range(num_bits - 1):
				this_bit = line[i]
				if i == 0:
					if this_bit == '1':
						this_node = root_one
				this_node.vals.append(line[:num_bits])
				next_bit = line[i+1]
				if next_bit == '0':
					if not this_node.zero:
						this_node.zero = bin_node()
					this_node = this_node.zero
				else: # next_bit == '1'
					if not this_node.one:
						this_node.one = bin_node()
					this_node = this_node.one
			
			# save vals for last node
			this_node.vals.append(line[:num_bits])
		
		d.get_gamma_epsilon_str()
		#	d.get_power_consumption()
		print(d)
	
		d.get_o2_rating(root_zero, root_one)
		print(d.o2_rating)

	
	
if __name__ == "__main__":
	main()
