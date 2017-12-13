from autograde import TEST_PREFIX, TO_TEST

if __name__ == '__main__':
    submissions = TO_TEST.split('\n')
    for filename in submissions:
        path = TEST_PREFIX + filename
        if path[-5:] == '.nand':
            path = path[:-5] + '.nnd'

        numLines = sum(1 for line in open(path))
        print ','.join([filename, str(numLines)])
