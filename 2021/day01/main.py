from utils.utils import load_data, print_answer
from numpy import ndarray
from math import inf


def calc_number_of_increase(data: ndarray) -> int:
    previous_value = inf
    counter = 0

    for line in data:
        if (value := int(line)) > previous_value:
            counter += 1

        previous_value = value

    return counter


def calc_number_of_increase_with_window(data: ndarray, window_size: int) -> int:
    previous_value = inf
    counter = 0

    for index in range(0, len(data) - window_size + 1):
        value = 0

        for nextIndex in range(0, window_size):
            value += int(data[index + nextIndex])

        if value > previous_value:
            counter += 1

        previous_value = value

    return counter


DAY = "01"
example_data, input_data = load_data(DAY)

example_count = calc_number_of_increase(example_data)
input_count = calc_number_of_increase(input_data)

print_answer((example_count, input_count), DAY, part=1)

example_count = calc_number_of_increase_with_window(example_data, window_size=3)
input_count = calc_number_of_increase_with_window(input_data, window_size=3)

print_answer((example_count, input_count), DAY, part=2)
