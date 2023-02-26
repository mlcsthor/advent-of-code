def find_first_marker(buffer: str, sequence_size: int):
  i = 0
  
  while len(set(buffer[i:i + sequence_size])) != sequence_size:
    i += 1

  return i + sequence_size

print('### Advent of Code Day 4 ###\n')

with open('example.txt') as file:
  line = file.readline().strip()
  marker = find_first_marker(line, sequence_size=4)
  print(f'Example for Part 1: {marker}')

  marker = find_first_marker(line, sequence_size=14)
  print(f'Example for Part 2: {marker}\n')

with open('input.txt') as file:
  line = file.readline().strip()
  marker = find_first_marker(line, sequence_size=4)
  print(f'Answer for Part 1: {marker}')

  marker = find_first_marker(line, sequence_size=14)
  print(f'Answer for Part 2: {marker}')
