from re import search
from enum import Enum

class Mover(Enum):
  CRATE_MOVER_9000 = 9000
  CRATE_MOVER_9001 = 9001

def transpose(matrix: list[list]) -> list[list]:
  return [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]

def strip(matrix: list[list[str]]) -> list[list]:
  stripped = []

  for line in matrix:
    stripped.append([x for x in line if x != ' '])

  return stripped

def rearrange(lines: list[str], mover: Mover):
  i: int = 0
  stacks: list[list[str]] = []

  while not lines[i].startswith(' 1'):
    stacks.append(list(lines[i]))
    i += 1

  stacks = transpose(stacks)
  stacks = [stacks[i] for i in range(1, len(stacks), 4)]
  stacks = strip(stacks)

  i += 2

  instructions = []
  for line in lines[i:]:
    instruction = search(r"move ([0-9]+) from ([0-9]) to ([0-9])", line.strip())

    if instruction:
      instructions.append(list(map(int, instruction.groups())))

  for move, source, target in instructions:
    effective_move = min(len(stacks[source - 1]), move)
    to_move = stacks[source - 1][:effective_move]
    
    if mover is mover.CRATE_MOVER_9000:
      to_move.reverse()
    
    stacks[target - 1] = to_move + stacks[target - 1]
    stacks[source - 1] = stacks[source - 1][effective_move:]

  return ''.join([line[0] for line in stacks])

print('### Advent of Code Day 5 ###\n')

with open('example.txt') as file:
  lines = file.readlines()
  print(f'Example for Part 1: {rearrange(lines, mover=Mover.CRATE_MOVER_9000)}')
  print(f'Example for Part 2: {rearrange(lines, mover=Mover.CRATE_MOVER_9001)}\n')

with open('input.txt') as file:
  lines = file.readlines()
  print(f'Answer for Part 1: {rearrange(lines, mover=Mover.CRATE_MOVER_9000)}')
  print(f'Answer for Part 2: {rearrange(lines, mover=Mover.CRATE_MOVER_9001)}')