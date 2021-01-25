import cs50
import csv
import sys
import re


if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

strCounts = {}
strList = []
dna_seq = ""
database = {}
match = ""

# open csv file
with open(sys.argv[1], "r") as csvfile:
    reader = csv.DictReader(csvfile)
    database = list(reader)

# generate list of all present str codes
    strList = list(reader.fieldnames)
    strList.pop(0)

# open sequence txt file
with open(sys.argv[2], "r") as f:
    dna_seq = f.read()


# calculate maximum str count - regex code taken from geekforgeeks.org (maximum consecutive substring occurence)
for target in strList:
    group = len(max(re.findall('((?:' + re.escape(target) + ')*)', dna_seq), key=len))
    strCounts[target] = int(group / len(target))

# compare str counts with database of possible matches
for row in database:
    result = []
    for element in strList:
        result.append(str(row[element]) == str(strCounts[element]))
    if all(result):
        match = (row['name'])

if not match:
    print("No match")
else:
    print(match)