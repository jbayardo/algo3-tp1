
import random
import string
import itertools
import sys

def generateEx1(length, bound):
    output = set()
    maximum = -1

    while len(output) < length:
        n = random.randint(1, bound)

        output.add(n)
        if n > maximum:
            maximum = n

    return str(random.randint(1, maximum)) + "\n" + " ".join(str(s) for s in sorted(list(output)))


def generateEx2(length, bound):
    output = []

    while len(output) < length:
        n = random.randint(-bound, bound)
        output.append(n)

    # s = sorted(output)

    # if len(s) % 2 == 0:
    #     m = (s[len(s)//2 + 1] + s[len(s)//2 - 1]) // 2
    # else:
    #     m = s[len(s)//2]

    return " ".join(str(output).strip("[").strip("]").split(", "))


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
    return res[:-1]


def write_to_test_file(filename, data):
    with open(filename, "w") as file:
        file.writelines(data)

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print "Numero problema, max size"
        exit()
    problem = int(sys.argv[1])
    top = int(sys.argv[2])
    data = []
    gen = None
    if problem == 1:
        filename = "ex1.in"
        gen = generateEx1
    elif problem == 2:
        filename = "ex2.in"
        gen = generateEx2
    else:
        filename = "ex3.in"
        gen = generateEx3

    print filename
    x = 10
    while x < top:
        data.append(gen(x, x))
        x *= 10

    # top = 10 ** 8
    write_to_test_file(filename, "\n".join(data))
