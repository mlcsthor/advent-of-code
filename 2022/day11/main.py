from re import search
from copy import deepcopy
from math import lcm
from operator import add, mul, itemgetter

def parse_file(file):
  lines = [line.strip() for line in file.readlines() if line != '\n']
  monkeys_data = [lines[idx:idx+6] for idx in range(0, len(lines), 6)]
  monkeys = []

  for [_, items, operation, test, if_true, if_false] in monkeys_data:
    items_search = search("Starting items: (.+)", items)
    operation_search = search("Operation: new = old (.) (.+)", operation)
    test_search = search("Test: divisible by (.+)", test)
    if_true_search = search("If true: throw to monkey (.)", if_true)
    if_false_search = search("If false: throw to monkey (.)", if_false)

    if not items_search or not operation_search or not test_search: exit()
    if not if_true_search or not if_false_search: exit()

    items = list(map(int, items_search.groups()[0].split(',')))
    symbol, value = operation_search.groups()
    operation = add if symbol == '+' else mul
    divisor = int(test_search.groups()[0])
    if_true = int(if_true_search.groups()[0])
    if_false = int(if_false_search.groups()[0])

    monkeys.append({
      'items': items,
      'operation': operation,
      'value': value,
      'divisor': divisor,
      'if_true': if_true,
      'if_false': if_false,
      'inspected': 0
    })

  return monkeys

def run_monkey_business(monkeys, round, worry):
  multiple = lcm(*[monkey['divisor'] for monkey in monkeys])

  for _ in range(round):
    for monkey in monkeys:
      monkey['inspected'] += len(monkey['items'])

      for item in monkey['items']: 
        value = item if monkey['value'] == 'old' else int(monkey['value'])
        worry_level = (monkey['operation'](item, value))
        if worry:
          worry_level //= 3
        else:
          worry_level %= multiple

        if worry_level % monkey['divisor'] == 0:
          monkeys[monkey['if_true']]['items'].append(worry_level)
        else:
          monkeys[monkey['if_false']]['items'].append(worry_level)
        
      monkey['items'] = []
  
  monkeys.sort(key=itemgetter('inspected'), reverse=True)
  return monkeys[0]['inspected'] * monkeys[1]['inspected']

print('### Advent of Code Day 11 ###\n')

with open('example.txt') as file:
  monkeys = parse_file(file)
  monkey_business = run_monkey_business(deepcopy(monkeys), round=20, worry=True)
  print(f'Example for Part 1: {monkey_business}')

  monkey_business = run_monkey_business(monkeys, round=10000, worry=False)
  print(f'Example for Part 2: {monkey_business}\n')

with open('input.txt') as file:
  monkeys = parse_file(file)
  monkey_business = run_monkey_business(deepcopy(monkeys), round=20, worry=True)
  print(f'Answer for Part 1: {monkey_business}')

  monkey_business = run_monkey_business(monkeys, round=10000, worry=False)
  print(f'Answer for Part 2: {monkey_business}')
