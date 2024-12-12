isTest = True

def main():
    fn  = "input.txt"
    if isTest:
        fn = "test.txt"

    with open(fn) as f:
        for line in f:
            print(line)

if __name__ == "__main__":
    main()
