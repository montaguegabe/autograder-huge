## The .nnd file format
- Simply comma-delimited triples of identifiers representing a program
- Besides this, only rules are that inputs of x_0, x_1, ... and outputs are y_0, y_1, ...
- To grade massive NAND programs you transpile the NAND files to .nnd format, then run them through the C++ autograder, which is much faster

## Autograding massive NAND programs
0. Set the NAND program input/output length in the global variables of cpp/main.cpp. Then build the C++ autograder in the cpp directory with `make`, then move the binary out to be in the same folder as autograde.py
1. Place submission .nand files in /submissions.
2. Modify keygen.py to create suitable key. Each line of the key should be a comma-delimited pair of the input followed by expected output. Then run `python keygen.py > yourkeyname.py`
3. Modify submission_lists.py to contain the subset of submissions you wish to run the autograder on
4. Set flags in autograde.py to tell whether you wish to transpile to .nnd, run the autograder on the .nnd files, or do both. Usually you just need to transpile once.
5. Run `python autograde.py` and save the output (of all channels) to a log file like example.log.
6. To get a CSV of the attempts results run `python parse_output.py example.log > examplePerf.csv`
7. To get submission line lengths use `python get_linecounts.py > linecounts.csv`
8. To combine the separate CSV files into a single nice result I used MATLAB to make a big table. This also enabled me to quickly sort/filter by line count.

## Diagnosing failing programs
For programs that fail 100% of the time here are things to try to get them to work:

This process is tedious and could use some more automation.

Inspect the output of the expected result vs. the actual result for the first test case by putting them both in Sublime Text together.

1. Visually inspect. Many times there are tons of 0's indicating they did not solve the problem for the correct number of bits. If so  run on smaller input lengths as appropriate. Tip: Use regular expression matching in sublime text e.g. `\d{1024}` to see how long strings of binary are to see which key to use.

2. Run with the reversed key. Maybe they were reading the inputs backwards so try the code with a key designed for that (e.g. keyRevLong.csv).

3. Search for random substrings of the expected output in the actual output to see if the output is offset or only partially matching.

4. Do the same as step 3 but with a reversed substring (in the case that the output is backwards combined with being shifted or offset)

5. Inspect the actual .nand file to see if they are doing anything illegal that could mess up the transpilation to .nnd (like sweetened code). Also maybe look at the .nnd file for comparison. Here you can also search to see which outputs are actually assigned and which inputs are actually used.

6. Give up

