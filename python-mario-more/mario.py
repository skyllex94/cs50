from cs50 import get_int

def main():
    # Print height and catch in not integer
    try:
        count = get_int("Height: ")
    except:
        print("Not an Integer, try again")

    # Catch if the integer in not between the scope, if not
    # re-prompt the user as you write a message for it
    try:
        if count >= 1 and count <= 8:
            for i in range(1, (count + 1)):
                # Function taking the current iterator, and total count
                generate_pyramid(count, i)
        else:
            print("Enter a number between 1 and 8 inclusively.")
            main()
    except:
        return 1

# Generate a single row
def generate_pyramid(num, iteration):
    # Recursively generate the white spaces
    generate_space(num - iteration)
    # Recursively generate the amount of hashes
    generate_hash(num - (num - iteration))
    print("  ", end="")
    generate_hash(num - (num - iteration))
    print("")


def generate_space(spaces):
    # Base case
    if spaces == 0:
        return 0
    print(" ", end="")
    # Deductive recursion of amount of spaces
    spaces = generate_space(spaces - 1)

def generate_hash(hashes):
    # Base case
    if hashes == 0:
        return 0
    print("#", end="")
    # Deductive recursion of amount of hashes
    generate_hash(hashes - 1)

if __name__ == "__main__":
    main()