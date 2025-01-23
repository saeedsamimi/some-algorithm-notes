import argparse
import random

def main():
    parser = argparse.ArgumentParser(description='Generate random numbers')
    parser.add_argument('-a', type=int, default=1, help='start range')
    parser.add_argument('-b', type=int, default=100, help='end range')
    parser.add_argument('-n', type=int, default=10, help='count')
    parser.add_argument('-o', type=str, default='random_numbers.txt', help='output file')
    parser.add_argument('-l', action='store_true', help='use newline separator')
    
    args = parser.parse_args()

    separator = '\n' if args.l else ' '
    with open(args.o, 'w') as f:
        for count in range(args.n):
            f.write(str(random.randint(args.a, args.b)))
            f.write(separator)
            print(f"\rgenerated: ({count}/{args.n})", end='', flush=True)

    print(f"Generated {args.n} random numbers between {args.a} and {args.b} in {args.o}")

if __name__ == '__main__':
    main()