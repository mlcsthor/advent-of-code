from ast import literal_eval
from functools import reduce

dividers = ['[[2]]', '[[6]]']

def parse(file):
  return [line.strip() for line in file.readlines() if line != '\n']

def compare(left, right):
  match type(left) == int, type(right) == int:
    case True, True:
      return -1 if left > right else 0 if left == right else 1

    case True, False:
      return compare([left], right)

    case False, True:
      return compare(left, [right])

    case _:
      for i in range(min(len(left), len(right))):
        if (result := compare(left[i], right[i])) != 0:
          return result

      return -1 if len(left) > len(right) else 0 if len(left) == len(right) else 1

def count_right_orders(pairs):
  sum = 0
  for i in range(0, len(pairs) - 1, 2):
    left, right = list(map(literal_eval, pairs[i:i+2]))    

    if compare(left, right) > 0:
      sum += (i//2 + 1)

  return sum

def sort(lines):
  size = len(lines)

  for i in range(size):
    for j in range(size - i - 1):
      left, right = list(map(literal_eval, lines[j:j+2]))

      if compare(left, right) != 1:
        lines[j], lines[j + 1] = lines[j + 1], lines[j]

  dividers_idx = [i + 1 for i in range(len(lines)) if lines[i] in dividers]
  return reduce(lambda x, y: x * y, dividers_idx)

print('### Advent of Code Day 13 ###\n')

with open('example.txt') as file:
  lines = parse(file)
  right = count_right_orders(lines)
  print(f'Example for Part 1: {right}')

  lines.extend(dividers)
  distress_signal = sort(lines)
  print(f'Example for Part 2: {distress_signal}\n')

with open('input.txt') as file:
  lines = parse(file)
  right = count_right_orders(lines)
  print(f'Answer for Part 1: {right}')

  lines.extend(dividers)
  distress_signal = sort(lines)
  print(f'Example for Part 2: {distress_signal}')
  