import csv
import random

def generate_int(min_val, max_val):
    return int(random.random() * (max_val - min_val) + min_val)

id = 1
with open('Module11_v2\starters_02.csv', 'r') as f:
    reader = csv.reader(f, delimiter='\t')
    for row in reader:
        name = row[0]
        position = row[1]
        team = row[2]
        two_point = row[3]
        three_point = row[4]
        defense = row[5]

        if two_point == None or two_point == '':
            two_point = generate_int(50, 90)
        if three_point == None or three_point == '':
            three_point = generate_int(50, 90)
        if defense == None or defense == '':
            defense = generate_int(50, 90)
            

        print '<player id="{}" name="{}">'.format(id, name)
        print '  <team>{}</team>'.format(team)
        print '  <icon>{}</icon>'.format(generate_int(1, 7))
        print '  <offense>'
        print '    <two_point>{}</two_point>'.format(two_point)
        print '    <three_point>{}</three_point>'.format(three_point)
        print '  </offense>'
        print '  <defense>{}</defense>'.format(defense)
        print '</player>'
        id += 1
        
