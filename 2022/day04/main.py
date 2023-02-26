from typing import TextIO

def get_assignments(file: TextIO) -> list[list]:
  assignments = []

  for line in file.readlines():
    assignment = []
    pairs = line.strip().split(',')

    for pair in pairs:
      start, end = map(int, pair.split('-'))
      assignments.append([x for x in range(start, end + 1)])

    assignments.append(assignment)

  return assignments

def get_overlapping(assignments: list[list]) -> int:
  overlapping: int = 0

  for first_half, second_half in assignments:
    first_check = all(item in first_half for item in second_half)
    second_check = all(item in second_half for item in first_half) 

    if first_check or second_check:
      overlapping += 1

  return overlapping

def get_overlapping_at_all(assignments: list[list]) -> int:
  overlapping: int = 0

  for first_half, second_half in assignments:
    first_check = any(item in first_half for item in second_half)
    second_check = any(item in second_half for item in first_half) 

    if first_check or second_check:
      overlapping += 1

  return overlapping

print('### Advent of Code Day 4 ###\n')

with open('example.txt') as file:
  assignments = get_assignments(file)
  overlapping = get_overlapping(assignments)
  print(f'Example for Part 1: {overlapping}')

  overlapping = get_overlapping_at_all(assignments)
  print(f'Example for Part 2: {overlapping}\n')

with open('input.txt') as file:
  assignments = get_assignments(file)
  overlapping = get_overlapping(assignments)
  print(f'Answer for Part 1: {overlapping}')

  overlapping = get_overlapping_at_all(assignments)
  print(f'Answer for Part 2: {overlapping}')