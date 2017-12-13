from random import * 

OF_EACH = 8

def extend_to_len(n, l):
    b = bin(n)[2:]
    rev_b = b[::-1]
    return (rev_b + ('0' * (l - len(b))))

def rand_input(size): 
    return randint(0, 2 ** size)

def mult_pair_str(inputSize): 
    a = rand_input(inputSize)
    b = rand_input(inputSize)
    c = a * b
    return (extend_to_len(a, inputSize) + extend_to_len(b, inputSize) + ',' + extend_to_len(c, 2 * inputSize)) 

for i in range(0, OF_EACH):
  print mult_pair_str(512)
