text = input("Text: ")
words = 1
chars = 0
sentences = 0

for i in text:
    if i == " ":
        words += 1
    if i.isalpha():
        chars += 1
    if i in "?!.":
        sentences += 1

grade = 0.0588 * (chars / words * 100) - 0.296 * (sentences / words * 100) - 15.8
grade = round(grade)

if grade > 16:
    print("Grade 16+")
elif grade < 1:
    print("Before grade 1")
else:
    print(f"Grade {grade}")

