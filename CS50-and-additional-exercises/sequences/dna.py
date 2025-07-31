import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: programName database sequence")
        exit()

    # TODO: Read database file into a variable
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        
        clm_names = reader.fieldnames[1:]

        people = []

        for row in reader:
            person = {
                "name": row["name"],
                "str_count": {str_name: int(row[str_name]) for str_name in clm_names}
            }
            people.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence_file:
        sequence = sequence_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    sequence_longest_str = {clm_name: longest_match(sequence, clm_name) for clm_name in clm_names}

    # TODO: Check database for matching profiles
    for person in people:
        if person["str_count"] == sequence_longest_str:
            print(person["name"])
            exit()
    
    print("No match")

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
