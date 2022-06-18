
lines1 = set()
lines2 = set()

with open("s_1000_10_intersects.txt", "r") as file:
    lines = file.readlines()
    lines = [l.strip() for l in lines]
    lines = set(lines)
    lines1 = lines


with open("s_1000_10_intersects_bruteforce.txt", "r") as file:
    lines = file.readlines()
    lines = [l.strip() for l in lines]
    lines = set(lines)
    lines2 = lines

print(len(lines1))
print(len(lines2))

print(lines2-lines1)