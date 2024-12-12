import numpy as np
import re

isTest = False

def print_kernel(c, tl, tr, bl, br):
    print(f"{tl}.{tr}")
    print(f".{c}.")
    print(f"{bl}.{br}")

def slide_window(lines):
    lines = [list(line) for line in lines]
    num_hits = 0

    for i in range(1, len(lines) - 1):
        for j in range(1, len(lines[i]) - 1):
            # define kernel
            c = lines[i][j]
            tl = lines[i-1][j-1]
            tr = lines[i-1][j+1]
            bl = lines[i+1][j-1]
            br = lines[i+1][j+1]

            # check for match at kernel
            if c != 'A':
                continue
            if tl == 'S':
                if br == 'M':
                    if tr == 'S':
                        if bl == 'M':
                            num_hits += 1 # I
                            if isTest:
                                print_kernel(c, tl, tr, bl, br)
                                print()
                        else:
                            continue
                    elif tr == 'M':
                        if bl == 'S':
                            num_hits += 1 # II
                            if isTest:
                                print_kernel(c, tl, tr, bl, br)
                                print()
                        else:
                            continue
                    else:
                        continue
                else:
                    continue
            elif tl == 'M':
                if br == 'S':
                    if tr == 'S':
                        if bl == 'M':
                            num_hits += 1 # III
                            if isTest:
                                print_kernel(c, tl, tr, bl, br)
                                print()
                        else:
                            continue
                    elif tr == 'M':
                        if bl == 'S':
                            num_hits += 1 # IV
                            if isTest:
                                print_kernel(c, tl, tr, bl, br)
                                print()
                        else:
                            continue
                    else:
                        continue
                else:
                    continue
            else: continue

    return num_hits

def main():
    fn = "input.txt"
    if isTest:
        fn = "test.txt"

    lines = list()

    with open(fn) as f:

        for line in f:
            # clean line
            line = line[:-1]
            lines.append(line)
    f.close()

    num_hits = 0
    num_hits += slide_window(lines)

    print(f"Found: {num_hits}")

if __name__ == "__main__":
	main()
