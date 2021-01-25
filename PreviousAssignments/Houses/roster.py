import csv
import sys
import cs50


# ensure correct usage
if len(sys.argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

list = []

# open file for SQLite
db = cs50.SQL("sqlite:///students.db")

# perform SELECT query on database to extract all records associated to entered house
list = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last, first", sys.argv[1])

# print off list of students that belong to entered house
for row in list:
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))
        