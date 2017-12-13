import sys

filename = sys.argv[1]

with open(filename, 'r') as inFile:

    currentSub = None
    nextIsScore = False
    for line in inFile:
        line = line.rstrip().lstrip()
        if not line: continue
        
        if nextIsScore:
            scoreParts = line.split('/')
            print ','.join([currentSub, scoreParts[0], scoreParts[1]])
            nextIsScore = False
            continue

        if line.split('.')[-1].lower() == 'nand':
            currentSub = line

        if line == 'Results:':
            nextIsScore = True
