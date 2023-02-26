from typing import TextIO

def extract_rounds(file: TextIO) -> list[list]:
  return [line.strip().split(' ') for line in file.readlines()]

def calc_score_part1(rounds: list[list]) -> int:
  bonus = [3, 0, 6]
  score = 0

  for round in rounds:
    opponent = ord(round[0]) - ord('@')
    player = ord(round[1]) - ord('W')
    diff = (opponent - player)%3
    score += player + bonus[diff]

  return score

def calc_score_part2(rounds: list[list]) -> int:
  lose = [3, 1, 2]
  score = 0

  for round in rounds:
    opponent = ord(round[0]) - ord('@')
    player = ord(round[1]) - ord('W')

    # Draw
    if player == 2:
      score += opponent + 3
    # Win
    elif player == 3:
      score += (opponent%3 + 1 + 6)
    # Lose
    else:
      score += (lose[opponent - 1])
  
  return score

print('### Advent of Code Day 2 ###\n')

with open('example.txt') as file:
  rounds = extract_rounds(file)
  score: int = calc_score_part1(rounds)
  print(f'Example for Part 1: {score}')

  score2: int = calc_score_part2(rounds)
  print(f'Example for Part 2: {score2}\n')

with open('input.txt') as file:
  rounds = extract_rounds(file)
  score: int = calc_score_part1(rounds)
  print(f'Answer for Part 1: {score}')

  score2: int = calc_score_part2(rounds)
  print(f'Answer for Part 2: {score2}\n')