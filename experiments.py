import os
import re

files = map((lambda x: 'experiments/'+x), os.listdir('experiments'))

for fname in files:
    if fname[-2:] != 'in':
        continue

    matches = re.match(r"^experiments\/test_([1-3])_(.*)\.in$", fname)

    method = matches.group(1).strip()
    outf = fname[:-2] + 'out'

    print "Corriendo para ", fname
    os.system('./tp1 {method} {fname} {outf} 100'.format(method=method, fname=fname, outf=outf))