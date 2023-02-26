from operator import sub, add

def calc_visited_position(lines, nb_knots):
  knots = [(0, 0) for _ in range(nb_knots)]
  visited = set([knots[-1]])

  for line in lines:
    direction, step = line.split(' ')

    match direction:
      case 'R':
        movement = (0, 1)
      case 'L':
        movement = (0, -1)
      case 'U':
        movement = (1, 0)
      case 'D':
        movement = (-1, 0)
      case _:
        movement = (0, 0)
    
    for _ in range(int(step)):
      knots[0] = tuple(map(add, knots[0], movement))

      for k in range(1, nb_knots):
        dist_x, dist_y = tuple(map(sub, knots[k - 1], knots[k]))

        move = (0, 0)
        if dist_x == 0 and not -1 <= dist_y <= 1:
          move = (0, -1 if dist_y < 0 else 1)
        elif dist_y == 0 and not -1 <= dist_x <= 1:
          move = (-1 if dist_x < 0 else 1, 0)
        elif (dist_x != 0 and not -1 <= dist_y <= 1) or (dist_y != 0 and not -1 <= dist_x <= 1):
          move = (-1 if dist_x < 0 else 1, -1 if dist_y < 0 else 1)

        knots[k] = tuple(map(add, knots[k], move))

      visited.add(knots[-1])
    
  return len(visited)

print('### Advent of Code Day 09 ###\n')

with open('example.txt') as file:
  lines = [line.strip() for line in file.readlines()]
  visited = calc_visited_position(lines, nb_knots=2)
  print(f'Example for Part 1: {visited}')

with open('example2.txt') as file:
  lines = [line.strip() for line in file.readlines()]
  visited = calc_visited_position(lines, nb_knots=10)
  print(f'Example for Part 2: {visited}\n')

with open('input.txt') as file:
  lines = [line.strip() for line in file.readlines()]
  visited = calc_visited_position(lines, nb_knots=2)
  print(f'Answer for Part 1: {visited}')

  visited = calc_visited_position(lines, nb_knots=10)
  print(f'Answer for Part 1: {visited}')