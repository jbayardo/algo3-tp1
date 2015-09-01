import os
import re
import pandas as pd
# Este script larga output.csv, con el formato que buscamos para que lo tome
# el software para graficar, Tableau.

dataset = []

files = map(lambda x: 'experiments/'+x, os.listdir('experiments'))

for fname in files:
    if fname[-2:] != 'in':
        continue

    if not os.path.isfile(fname[:-2] + 'expected'):
        print "Falta archivo de salida expected para " + fname
        continue

    matches = re.match(r"^experiments\/test_([1-3])(.*)$", fname)

    method = matches.group(1).strip()
    outf = fname[:-2] + 'out'

    os.system('./tp1 {method} {fname} {outf}'.format(method=method, fname=fname, outf=outf))

    with open(outf, 'r') as handle:
        output = handle.read().strip()

    with open(fname[:-2] + 'expected', 'r') as handle:
        expected = handle.read().strip()

    for line1, line2 in zip(output.split('\n'), expected.split('\n')):
        if line1.strip() != line2.strip():
            print "Failure: ", line1, line2

for fname in files:
    if fname[-3:] != 'sts':
        continue

    matches = re.match(r"^experiments\/test_([1-3])_?(.*)?\.out\.sts$", fname)
    method = matches.group(1).strip()
    name = matches.group(2).strip()

    with open(fname, 'r') as handle:
        data = handle.read()

    data = data.strip().split('\n')

    for line in data:
        line = line.strip().split('\t\t\t')
        line[1] = line[1].strip().split(' ')

        for index, measure in enumerate(line[1]):
            output = {
                'name': name,
                'method': method,
                'number': index,
                'timer': line[0],
                'value': measure,
            }

            dataset.append(output)

df = pd.DataFrame(dataset)
df.to_csv('output.csv', index=False)
