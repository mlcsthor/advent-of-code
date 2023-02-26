from collections import deque

def get_height(value):
  height = 0

  match value:
    case 'S':
      height = ord('a')
    case 'E':
      height = ord('z')
    case _:
      height = ord(value)

  return height

def get_neighbours(grid, i, j):
  height = get_height(grid[i][j])
  neighbours = []
  height = get_height(grid[i][j])
  
  if i > 0 and height - get_height(grid[i - 1][j]) >= -1:
    neighbours.append((i - 1) * len(grid[i]) + j)

  if j > 0 and height - get_height(grid[i][j - 1]) >= -1:
    neighbours.append(i * len(grid[i]) + (j - 1))

  if i < len(grid) - 1 and height - get_height(grid[i + 1][j]) >= -1:
    neighbours.append((i + 1) * len(grid[i]) + j)

  if j < len(grid[i]) - 1 and height - get_height(grid[i][j + 1]) >= -1:
    neighbours.append(i * len(grid[i]) + (j + 1)) 

  return sorted(neighbours)

def find_shortest_path(graph, start, goal):
  queue = deque()
  queue.append(start)
  node = None

  came_from = {
    start: None
  }

  while queue:
    node = queue.popleft()

    if node == goal:
      break

    for neighbour in graph[node]:
      if neighbour not in came_from:
        queue.append(neighbour)
        came_from[neighbour] = node

  if node != goal:
    return []

  current = goal
  path = []
  while current != start:
    path.append(current)
    current = came_from[current]

  return path

def calc_fewest_steps_from_start(grid):
  graph = {}
  start, goal = None, None

  for i in range(len(grid)):
    for j in range(len(grid[i])):
      coord = i * len(grid[i]) + j

      match grid[i][j]:
        case 'S':
          start = coord
        case 'E':
          goal = coord
        case _:
          pass

      graph[coord] = get_neighbours(grid, i, j)  

  shortest_path = find_shortest_path(graph, start, goal)
  return len(shortest_path)

def calc_fewest_steps_from_every_lowest(grid):
  graph = {}
  goal = None
  starts = []

  for i in range(len(grid)):
    for j in range(len(grid[i])):
      coord = i * len(grid[i]) + j

      match grid[i][j]:
        case 'S':
          starts.append(coord)
        case 'a':
          starts.append(coord)
        case 'E':
          goal = coord
        case _:
          pass

      graph[coord] = get_neighbours(grid, i, j)  

  fewest_steps = []
  for start in starts:
    shortest_path = find_shortest_path(graph, start, goal)

    if shortest_path:
      fewest_steps.append(len(shortest_path))

  return min(fewest_steps)

print('### Advent of Code Day 12 ###\n')

with open('example.txt') as file:
  grid = [list(line.strip()) for line in file.readlines()]
  fewest_steps = calc_fewest_steps_from_start(grid)
  print(f'Example for Part 1: {fewest_steps}')

  fewest_steps = calc_fewest_steps_from_every_lowest(grid)
  print(f'Example for Part 1: {fewest_steps}\n')

with open('input.txt') as file:
  grid = [list(line.strip()) for line in file.readlines()]
  fewest_steps = calc_fewest_steps_from_start(grid)
  print(f'Answer for Part 1: {fewest_steps}')

  fewest_steps = calc_fewest_steps_from_every_lowest(grid)
  print(f'Example for Part 1: {fewest_steps}\n')