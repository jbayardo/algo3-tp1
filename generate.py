
import random
import string
import itertools

def generateEx1(length, bound):
	output = set()
	maximum = -1

	while len(output) < length:
		n = random.randint(1, bound)

		if n not in output:
			output.add(n)

			if n > maximum:
				maximum = n

	return str(random.randint(1, maximum)) + "\n" + " ".join(str(pito) for pito in sorted(list(output)))

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

	return str(list(output))

def generateEx3(e, a):
	res = ""
	letters = list(string.ascii_lowercase[0:e])
	relationships = {}
	allrel = list(itertools.product(letters,letters))
	for letter in letters:
		relationships[letter] = set()
	actualA = 0
	while (actualA < a):
		s = random.sample(allrel,1)[0]
		if s[0] != s[1] and (s[1] not in relationships[s[0]]):
			relationships[s[0]].add(s[1])
			relationships[s[1]].add(s[0])
			actualA += 1
	for index in relationships:
		res += index + " " +  "".join(str(r) for r in relationships[index]) + ";"
	return res[:-1]

print generateEx1(6, 100)