num_bits = 12

class diagnostics:
	def __init__(self):
		self.bit_count = {i: [0, 0] for i in range(num_bits)}
		self.gamma = 0
		self.epsilon = 0
		self.power = 0
	
	def __str__(self):
		return f"{str(self.bit_count)} Gamma: {self.gamma} Epsilon: {self.epsilon} Power: {self.power}"
	
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
		
		self.gamma = int(gamma_str, base = 2)
		self.epsilon = int(epsilon_str, base = 2)
		
	def get_power_consumption(self):
		self.power = self.gamma * self.epsilon

def main():
#	fn = "test.txt"
	fn = "day3.txt"
	d = diagnostics()
	
	with open(fn) as f:
		for line in f:
			d.read_bits(line)
	
	d.get_gamma_epsilon_str()
	d.get_power_consumption()
	print(d)
	
	
if __name__ == "__main__":
	main()
