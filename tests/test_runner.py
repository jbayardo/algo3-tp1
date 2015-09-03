from subprocess import check_output


def string_to_int_list(line):
    return map(int, line.strip().split())


def parse_input(problem_number):
    filename = "Tp1Ej%d.in" % problem_number
    cases = []
    with open(filename, "r") as f:

        for line in f:
            if problem_number == 1:
                k = int(line)
                stations = string_to_int_list(f.next())
                n = len(stations)
                cases.append([n, k].extend(stations))

            if problem_number == 2:
                numbers = map(int, line.strip().split())
                cases.append(numbers)

            if problem_number == 3:
                friendship_list = line.strip().split(";")
                cases.append([len(friendship_list), friendship_list])
    return cases


def read_out_file(problem_number):
    if problem_number < 4:
        out_file = "Tp1Ej%d.out" % problem_number
        output = []
        with open(out_file, "r") as f:
            for l in f:
                output.append(l)
        return output


def run_problem(number, cases):
    program = "./Tp1"
    output = []
    for case in cases:
        output.append(check_output(program, number, case))
    return output


def compare_results(problem_number):
    cases = parse_input(problem_number)
    output = run(problem_number, cases)
    correct_output = read_out_file(problem_number)
    for o, c in zip(output, correct_output):
        if o != c:
            print "Error!"
            print o, " is different from ", c
        else:
            print "OK ! :D"


if __name__ == '__main__':
    print "Ingrese ejercicio a testear"
    problem_number = input()
    compare_results(problem_number)
