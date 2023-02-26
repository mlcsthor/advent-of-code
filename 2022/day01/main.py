from typing import TextIO

def calc_calories_per_elf(file: TextIO) -> list[int]:
  elves = []
  count = 0

  for line in file.readlines():
    line = line.strip()
    
    if line == '':
      elves.append(count)
      count = 0
      continue

    count += int(line)

  elves.append(count)
  return elves

def get_top_three_calories(elves: list[int]) -> int:
  elves.sort(reverse=True)
  return sum(elves[:3])

print('### Advent of Code Day 1 ###\n')

with open('example.txt') as file:
  elves: list = calc_calories_per_elf(file)
  print(f'Example for Part 1: {max(elves)}')

  calories: int = get_top_three_calories(elves)
  print(f'Example for Part 2: {calories}\n')

with open('input.txt') as file:
  elves: list = calc_calories_per_elf(file)
  print(f'Answer for Part 1: {max(elves)}')

  calories: int = get_top_three_calories(elves)
  print(f'Answer for Part 2: {calories}')