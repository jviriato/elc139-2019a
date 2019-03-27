import os
import glob
import re
for filename in glob.glob('*.txt'):
    lines = list(map(float, [line.rstrip('\n') for line in open(filename)]))
    print(lines)
    print(filename)
    result = sum(lines)/len(lines)
    with open(filename, 'a') as file:
        file.write('media:' + str(result))
