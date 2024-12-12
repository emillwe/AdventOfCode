isTest = True

def read_rest(f):
    result = list()

    for line in f:
        line = line.split(',')
        line = [int(elem) for elem in line]
        result.append(line)

    return result

def main():
    fn  = "input.txt"
    if isTest:
        fn = "test.txt"

    # pages: [pages_after_this_page]
    orders = dict()
    page_lists = list()

    with open(fn) as f:
        for line in f:
            if isTest:
                print(line)
            if '|' not in line:
                if(line == "\n"):
                    # save proposed orders
                    page_lists = read_rest(f)
                    break
            else:
                this_order = line.split('|')
                this_order = [int(page) for page in this_order]

                this_page = this_order[0]
                following_page = this_order[1]

                # save this order
                if this_page not in orders:
                    orders[this_page] = {following_page}
                else:
                    orders[this_page].add(following_page)
    f.close()

    if isTest:
        print(orders)
        print()
        print(page_lists)



if __name__ == "__main__":
    main()
