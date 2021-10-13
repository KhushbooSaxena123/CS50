import csv
import sys


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database/filemane.csv sequence/number.txt")

    # open dna sequence from text file
    with open(sys.argv[2]) as text:
        dna_seq = text.read()

    databases = []  # defining list containing all data
    # open these data from csv file
    with open(sys.argv[1]) as sequence:
        reader = csv.DictReader(sequence)  # data for each person will be in the form of dictionary in object reader
        for f in reader:
            databases.append(f)

    # accessing all keys in the csv file
    lst_str_seq = list(databases[0].keys())
    # creating dictionary of str values for given person
    person_str_dic = all_str(dna_seq, lst_str_seq)
    # finally comparing above person's dictionary in given databases for finding the person's name
    compare(person_str_dic, databases)


# this function give maximum count for a given STR
def single_STR(dna_seq, str_seq):
    seq = []
    count = 0
    n = len(dna_seq)
    m = len(str_seq)  # length of given STR
    for i in range(0, n - m):
        if dna_seq[i:i + m] == str_seq:
            count += 1
            if i > m - 1:
                seq.append(seq[i - m] + 1)
            else:
                seq.append(count)
            count = 0
        else:
            seq.append(count)
    # returning the maximum value in the list seq
    return str(max(seq))


# fuction creats dictionary of str for a person
def all_str(dna_seq, lst_str_seq):
    del lst_str_seq[0]
    person_dic = {}
    for i in lst_str_seq:
        person_dic[i] = single_STR(dna_seq, i)

    return person_dic

# fuction check if persons dna is present in databases or not


def compare(person_str_dic, databases):
    flage = 0
    count = 0
    i = 0
    keys = list(person_str_dic.keys())
    for data in databases:
        for key in keys:
            if data[key] == person_str_dic[key]:
                count += 1
        if count == len(keys):
            flage = 1
            # will return name of person from csv file of databases
            print(databases[i]['name'])
            count = 0
        else:
            count = 0
        i += 1
    if flage == 0:
        # if person is not in databases
        print("No match")


# calling the main function
main()