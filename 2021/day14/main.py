from utils.utils import load_data, print_answer
from collections import Counter
from numpy import delete, ndarray


def extract_data(data: ndarray) -> [str, dict]:
    template = data[0]
    data = delete(data, 0)
    data = delete(data, 0)

    rules = {}
    for line in data:
        elements = line.split('->')
        rules[elements[0].strip()] = elements[1].strip()

    return template, rules


def init(template: str) -> [Counter, Counter]:
    pairs = Counter()
    letters = Counter()

    for pair in [template[i:i+2] for i in range(len(template) - 1)]:
        pairs[pair] += 1

    for letter in template:
        letters[letter] += 1

    return pairs, letters


def insert_pair(pairs: Counter, letters: Counter, rules: dict) -> [Counter, Counter]:
    new_pairs = Counter()

    for pair, occurrence in pairs.items():
        inserted: str = rules.get(pair)

        if inserted:
            new_pairs[f"{pair[0]}{inserted}"] += occurrence
            new_pairs[f"{inserted}{pair[1]}"] += occurrence
            letters[inserted] += occurrence
        else:
            new_pairs[pair] += occurrence

    return new_pairs, letters


def polymerize(data: ndarray, step: int) -> Counter:
    template, rules = extract_data(data)
    pairs, letters = init(template)

    for _ in range(step):
        pairs, letters = insert_pair(pairs, letters, rules)

    return max(letters.values()) - min(letters.values())


DAY = "14"
example_data, input_data = load_data(DAY)

example_part1 = polymerize(example_data, step=10)
answer_part1 = polymerize(input_data, step=10)

example_part2 = polymerize(example_data, step=40)
answer_part2 = polymerize(input_data, step=40)

print_answer((example_part1, answer_part1), DAY, part=1)
print_answer((example_part2, answer_part2), DAY, part=2)
