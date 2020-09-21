#!/usr/bin/python3
import random

NUM_AMOUNT_PER_LINE = 3
LINES = 500
VALUES = [-255, 255]

if __name__ == "__main__":
    file = open("sample_big.cnf", "w+")
    file.write("c  sample_big.cnf\n")
    file.write("p cnf {} {}\n".format(VALUES[0], LINES))
    for k in range(LINES):
        num = random.randrange(0, NUM_AMOUNT_PER_LINE)
        for p in range(NUM_AMOUNT_PER_LINE):
            num = random.randrange(VALUES[0], VALUES[1])
            if num == 0:
                continue
            file.write("{} ".format(num))
        file.write("0\n")
