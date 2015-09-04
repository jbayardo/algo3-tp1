import os
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

    return str(random.randint(1, maximum)) + "\n" + " ".join(str(s) for s in sorted(list(output))) + "\n"

if not os.path.isfile("experiments/test_1_complejidad.in"):
    print "Generating ex1.1"

    paramsEx1 = [(10 + x*5, 100*x) for x in range(1, 1000)]

    print "Generating ex1.2"

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

## Lista ordenada de forma alternada
def generateEx2Best(length, bound):
    output = set()

    while len(output) < length+1:
        n = random.randint(-bound, bound)
        output.append(n)

    output = sorted(list(output))

    toutput = []

    for x in range(length):
        if x % 2 == 0:
            toutput.append(output[x//2])
        else:
            toutput.append(output[-((x//2) + 1)])

    return " ".join(str(output).strip("[").strip("]").split(", ")) + "\n"

## Lista estrictamente ordenada
def generateEx2Worst(length, bound):
    output = set()

    while len(output) < length:
        n = random.randint(-bound, bound)
        output.append(n)

    output = sorted(list(output))

    return " ".join(str(output).strip("[").strip("]").split(", ")) + "\n"

print "Generating ex2.1"
paramsEx2 = [(x, 3*x) for x in range(10, 5000)]

if not os.path.isfile("experiments/test_2_complejidad.in"):
    print "Generating ex2.2"

    output = ""
    for (length, bound) in paramsEx2:
        output += generateEx2(length, bound)

    write_to_test_file("experiments/test_2_complejidad_random.in", output.strip())

    output = ""
    for (length, bound) in paramsEx2:
        output += generateEx2Best(length, bound)

    write_to_test_file("experiments/test_2_complejidad_best.in", output.strip())

    output = ""
    for (length, bound) in paramsEx2:
        output += generateEx2Worst(length, bound)

    write_to_test_file("experiments/test_2_complejidad_worst.in", output.strip())

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

if not os.path.isfile("experiments/test_3_complejidad.in"):
    print "Generating ex3.1"

    paramsEx3 = [(e, a) for e in range(3, 27) for a in range(1, e*(e-1)/2 + 1)]

    print "Generating ex3.2"

    output = ""
    for (explorers, friendships) in paramsEx3:
        print explorers, friendships
    	output += generateEx3(explorers, friendships)

    write_to_test_file("experiments/test_3_complejidad.in", output.strip())

########################################################################~
#Best and Worst cases###################################################~
########################################################################~

def generateBest1(cities,dis):
	cable = dis
	n = cable + 1
	output = []
	now = n
	while len(output) < cities:
		output.append(now)
		now += n

	return str(cable) + "\n" + " ".join(str(s) for s in output) + "\n"

def generateWorst1(cities,dis):
	distance = dis
	cable = distance * cities
	n = distance - 1
	output = []
	now = n
	while len(output) < cities - 1:
		output.append(now)
		now += n
	output.append(now + cable)

	return str(cable) + "\n" + " ".join(str(s) for s in output) + "\n"

if not os.path.isfile("experiments/test_1_complejidad_best.in") or not os.path.isfile("experiments/test_1_complejidad_worst.in"):
	dis = random.randint(1, 500)
	print "Generating WB1.1"

	paramsEx1 = [(10 + x*5) for x in range(1, 1000)]

	print "Generating WB1.2"

	outputB = ""
	outputW = ""
	for (cities) in paramsEx1:
		outputB += generateBest1(cities, dis)
		outputW += generateWorst1(cities, dis)

	write_to_test_file("experiments/test_1_complejidad_best.in", outputB.strip())
	write_to_test_file("experiments/test_1_complejidad_worst.in", outputW.strip())


if not os.path.isfile("experiments/test_3_complejidad_worst.in"):
    print "Generating ex3.1W"

    paramsEx3 = [(e, a) for e in range(3, 15) for a in range(1, e*(e-1)/2 + 1)]

    print "Generating ex3.2W"

    output = ""
    for (explorers, friendships) in paramsEx3:
        print explorers, friendships
    	output += generateEx3(explorers, friendships)

    write_to_test_file("experiments/test_3_complejidad_worst.in", output.strip())