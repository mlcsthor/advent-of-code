from re import search
from typing import Tuple

class Node():
  def __init__(self, name: str, type: str, value = 0, parent = None):
    self.name = name
    self.parent = parent
    self.type = type
    self.children = []
    self.value = value

  def add_child(self, name: str, type: str, value = 0):
    child = Node(name, type, parent=self, value=value)
    self.children.append(child)
    return child

  @property
  def size(self):
    return self.value + sum([child.size for child in self.children])

  def __str__(self, level=0):
    ret = "  " * level + f"- {self.name} ({self.type}, size: {self.size})\n"
    
    for child in self.children:
      ret += child.__str__(level+1)

    return ret

  def __repr__(self):
    return f"({self.name}, size={self.size})"

def calc_size(lines: list[str]) -> Tuple[int, list[Node]]:
  cmd_idxs = [i for i in range(len(lines)) if lines[i].startswith('$')] + [len(lines)]
  commands = [lines[cmd_idxs[i]:cmd_idxs[i + 1]] for i in range(len(cmd_idxs) - 1)]

  root = Node('/', 'dir')
  current: Node = root
  folders = [root]

  for command in commands:
    cmd, output = command[0], command[1:]

    if cmd.startswith('$ cd'):
      dir_search = search(r"\$ cd (.+)", cmd)

      if dir_search:
        dir = dir_search.groups()[0]

        match dir:
          case '/':
            current = root
          case '..':
            if current.parent:
              current = current.parent
          case _:
            current = current.add_child(dir, 'dir')
            folders.append(current)
    elif cmd.startswith('$ ls'):
      for line in output:
        if not line.startswith('dir'):
          size, name = line.split(' ')
          current.add_child(name, type='file', value=int(size))

  return sum([folder.size for folder in folders if folder.size < 100000]), folders

def find_folder_to_delete(folders: list[Node]) -> int:
  root, other_folders = folders[0], folders[1:]

  total_space = 70000000
  unused_needed = 30000000
  unused_space = total_space - root.size

  other_folders.sort(key=lambda x: x.size)
  to_delete = next(x for x in other_folders if unused_space + x.size > unused_needed)

  return to_delete.size

print('### Advent of Code Day 7 ###\n')

with open('example.txt') as file:
  lines = [line.strip() for line in file.readlines()]
  size, folders = calc_size(lines)
  print(f'Example for Part 1: {size}')
  
  to_delete = find_folder_to_delete(folders)
  print(f'Example for Part 2: {to_delete}\n')

with open('input.txt') as file:
  lines = [line.strip() for line in file.readlines()]
  size, folders = calc_size(lines)
  print(f'Input for Part 1: {size}')

  to_delete = find_folder_to_delete(folders)
  print(f'Input for Part 2: {to_delete}')