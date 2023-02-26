from utils.utils import load_data, print_answer
from numpy import array, percentile, mean, ndarray


def calc_min_fuel(crabs: ndarray) -> int:
    position = int(percentile(crabs, 50))

    fuel = 0
    for crab in crabs:
        fuel += abs(crab - position)

    return fuel


def calc_min_fuel_with_rate(crabs: ndarray) -> int:
    position = int(mean(input_data))

    fuel = 0
    for crab in crabs:
        diff = abs(position - crab)
        fuel += int(diff * (diff + 1) / 2)

    return fuel


DAY = "07"
example_data, input_data = load_data("07")
example_data = array(example_data[0].split(',')).astype(int)
input_data = array(input_data[0].split(',')).astype(int)

example_answer1 = calc_min_fuel(example_data)
input_answer1 = calc_min_fuel(input_data)

example_answer2 = calc_min_fuel_with_rate(example_data)
input_answer2 = calc_min_fuel_with_rate(input_data)

print_answer((example_answer1, input_answer1), DAY, part=1)
print_answer((example_answer2, input_answer2), DAY, part=2)
