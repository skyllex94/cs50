import csv
import sys


def main():

    # TODO: Check for command-line usage
    if(len(sys.argv) != 3):
        sys.exit("Usage: Input a dataset and a DNA sample to check")

    # TODO: Read database file into a variable
    header_genomes = []
    dna_compare = []
    # Read the file and safe the first field names
    # and loop through each row and save it to a list of dicts
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        header_genomes = reader.fieldnames
        # print(header_genomes[2])
        for row in reader:
            dna_compare.append(row)
        # print(dna_compare)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as txtfile:
        dna_strand = txtfile.readlines()

    # TODO: Find longest match of each STR in DNA sequence
    dna_string = dna_strand[0]
    # print(f"{dna_string}")

    longest_run = []
    # Create a loop to call the longest match function for the sequence
    # and each header field without the name field
    for i in range(1, len(header_genomes)):
        longest_run.append(longest_match(dna_string, header_genomes[i]))
    # print(f"{longest_run}")

    # TODO: Check database for matching profiles
    dna_match = ""

    # Take each dict item from the list of dicts
    for i in range(0, len(dna_compare)):
        dict_values_list = list(dna_compare[i].values())
        # Split the list in half to compare only the numbers
        name_part = dict_values_list[:1]
        dna_part = dict_values_list[1:]

        # Convert each element into a number
        for j in range(len(dna_part)):
            dna_part[j] = int(dna_part[j])
        # Compare the longest run list with the dna_part of the list
        if dna_part == longest_run:
            dna_match = name_part[0]

    if dna_match == "":
        print("No match")
    else:
        print(dna_match)
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0
        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
