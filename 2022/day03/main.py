from typing import TextIO
from functools import reduce
from operator import ior

def get_rucksacks(file: TextIO) -> list[list]:
  return [list(line.strip()) for line in file.readlines()]

def get_priorities(item: str) -> int:
  return ord(item) - (ord('`') if item.islower() else ord('&'))

def calc_priorities_part1(rucksacks: list[list]) -> int:
  priorities: int = 0

  for rucksack in rucksacks:
    first_compartment = rucksack[:len(rucksack)//2]
    second_compartment = rucksack[len(rucksack)//2:]
    common_items = set(first_compartment) & set(second_compartment)

    for item in common_items:
      priorities += get_priorities(item)

  return priorities

def calc_priorities_part2(rucksacks: list[list]) -> int:
  priorities: int = 0
  groups = [rucksacks[idx:idx + 3] for idx in range(0, len(rucksacks), 3)]

  for group in groups:
    badge = reduce(lambda x, y: x & y, map(set, group)).pop()
    priorities += get_priorities(badge)

  return priorities

print('### Advent of Code Day 3 ###\n')

with open('example.txt') as file:
  rucksacks = get_rucksacks(file)
  priorities = calc_priorities_part1(rucksacks)
  print(f'Example for Part 1: {priorities}')

  priorities = calc_priorities_part2(rucksacks)
  print(f'Example for Part 2: {priorities}\n')

with open('input.txt') as file:
  rucksacks = get_rucksacks(file)
  priorities = calc_priorities_part1(rucksacks)
  print(f'Answer for Part 1: {priorities}')

  priorities = calc_priorities_part2(rucksacks)
  print(f'Answer for Part 2: {priorities}\n')