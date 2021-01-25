import csv
import sys
import cs50


# ensure correct usage
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)

# open file for SQLite
db = cs50.SQL("sqlite:///students.db")

# open csv file
with open(sys.argv[1], "r") as csvfile:

    reader = csv.DictReader(csvfile)

# iterate over each row of the csv file, splitting name column up
    for row in reader:
        house = row["house"]
        birth = row["birth"]
        nameList = row["name"].split()
        if len(nameList) == 3:
            first = nameList[0]
            middle = nameList[1]
            last = nameList[2]
        else:
            first = nameList[0]
            middle = None
            last = nameList[1]

# insert each row into the database
        db.execute("INSERT into students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
