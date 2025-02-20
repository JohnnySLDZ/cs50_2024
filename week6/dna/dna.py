import csv
import sys


def main():
#Check for command-line usage
    if len(sys.argv) != 3:
        print("No command-line argument")
        sys.exit(1)


    #Read database file into a variable
    rows = []
    sequence = ""
    try:
        with open(sys.argv[1]) as table:
            reader = csv.DictReader(table)
            for row in reader:
                rows.append(row)


    except FileNotFoundError:
        print("DataBase Loading Error")
        sys.exit(1)

    #Read DNA sequence file into a variable
    try:
        with open(sys.argv[2]) as txt:
            sequence = txt.read()


    except FileNotFoundError:
        print("Sequence Loading Error")
        sys.exit(1)


    #Find longest match of each STR in DNA sequence
    person = {}

    headers = list(rows[0].keys())


    for i in range(1, len(headers)):
        person[headers[i]] = longest_match(sequence, headers[i])

    # Check database for matching profiles

    mtch = ""
    for i in rows:
        for x in range(1, len(headers)):
            if person[headers[x]] != int(i[headers[x]]):
                break
        else:
            mtch = i[headers[0]]
            break


    if mtch == "":
        print("No match")

    else:
        print(mtch)

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
