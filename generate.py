
import random

def generateEx1(length, bound):
	output = set()
	maximum = -1

	while len(output) < length:
		n = random.randint(1, bound)

		if n not in output:
			output.add(n)

			if n > maximum:
				maximum = n

	return (random.randint(1, maximum), sorted(list(output)))

def generateEx2(length, bound):
	output = set()

	while len(output) < length:
		n = random.randint(-bound, bound)
		output.add(n)

	s = sorted(output)

	if len(s) % 2 == 0:
		m = (s[len(s)//2 + 1] + s[len(s)//2 - 1]) // 2
	else:
		m = s[len(s)//2]

	return (m, list(output))

def generateEx3():
	pass

print generateEx2(50, 500)