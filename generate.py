
import random
import string
import itertools
import sys

def write_to_test_file(fname, data):
	with open(fname, 'w') as handle:
		handle.write(data)

def generateEx1(length, bound):
    output = set()
    maximum = -1

    while len(output) < length:
        n = random.randint(1, bound)

        output.add(n)
        if n > maximum:
            maximum = n

    return str(random.randint(1, maximum)) + "\n" + " ".join(str(s) for s in sorted(list(output)))

paramsEx1 = [(10 + x*5, 100*x) for x in range(1, 10)]

output = ""
for (length, bound) in paramsEx1:
	output += generateEx1(length, bound)

write_to_test_file("experiments/test_1_complejidad.in", output.strip())

def generateEx2(length, bound):
    output = []

    while len(output) < length:
        n = random.randint(-bound, bound)
        output.append(n)

    return " ".join(str(output).strip("[").strip("]").split(", ")) + "\n"

paramsEx2 = [(x, 3000) for x in range(10, 100)]

output = ""
for (length, bound) in paramsEx2:
	output += generateEx2(length, bound)

write_to_test_file("experiments/test_2_complejidad.in", output.strip())

def generateEx3(e, a):
    res = ""
    letters = list(string.ascii_lowercase[0:e])
    relationships = {}
    allrel = list(itertools.product(letters, letters))
    for letter in letters:
        relationships[letter] = set()
    actualA = 0
    while (actualA < a):
        s = random.sample(allrel, 1)[0]
        if s[0] != s[1] and (s[1] not in relationships[s[0]]):
            relationships[s[0]].add(s[1])
            relationships[s[1]].add(s[0])
            actualA += 1
    for index in relationships:
        res += index + " " + "".join(str(r) for r in relationships[index]) + ";"
    return res[:-1] + "\n"

paramsEx3 = [(e, a) for e in range(3, 25) for a in range(1, e*(e-1)/2)]

output = ""
for (explorers, friendships) in paramsEx3:
	print "Generando ex3: ", explorers, friendships
	output += generateEx3(explorers, friendships)

write_to_test_file("experiments/test_3_complejidad.in", output.strip())
