import sys
import subprocess
import traceback
import logging
import os.path
import submission_lists

"""filename = sys.argv[1]
if filename[-5:] == '.nand':
    filename = filename[:-5]"""

KEYFILE = './keyMed.csv'

TEST_PREFIX = './submissions/'
TO_TEST = submission_lists.ALL

SKIP_TRANSPILE = True
def transpile(filename):

    if SKIP_TRANSPILE:
        print 'Skipping transpilation...'
        return 0

    with open(filename + '.nand', 'r') as inFile:
        with open(filename + '.nnd', 'w') as outFile: 
            lineCount = 0

            for x in inFile:
                x = x.rstrip().lstrip()
                if not x: continue
                if not x[0].isalnum():
                    # Assume comment
                    continue

                parts = x.split()
                identifiers = []
                numId = 0
                seenNAND = False
                out = ''
                for part in parts:
                    if part.lower() != 'nand' and (not '=' in part):
                        identifiers.append(part)
                        numId += 1
                        if numId == 3:
                            break
                    else:
                        seenNAND = True
                if numId != 3:
                    if seenNAND:
                        raise 'Something weird is going on'
                    else:
                        continue

                out += ','.join(identifiers) + '\n'
                lineCount += 1

                outFile.write(out)

    return lineCount

SKIP_INTERPRET = False
def interpret(filename):
    if SKIP_INTERPRET:
        print 'Skipping interpretation...'
        return
    toCall = ['./autograde', filename + '.nnd', KEYFILE]
    print ' '.join(toCall)
    result = subprocess.check_output(toCall, stderr=subprocess.STDOUT)
    print result

if __name__ == '__main__':
    submissions = TO_TEST.split('\n')
    for filename in submissions:
        print filename

        pathNoExt = TEST_PREFIX + filename
        if pathNoExt[-5:] == '.nand':
            pathNoExt = pathNoExt[:-5]

        try:
            print transpile(pathNoExt), 'lines transpiled'
        except Exception as e:
            print 'Transpilation failed'
            logging.error(traceback.format_exc())
        print 'Interpreting', pathNoExt
        try:
            interpret(pathNoExt)
        except Exception as e:
            print 'Interpretation failed'
            logging.error(traceback.format_exc())
        print ''

