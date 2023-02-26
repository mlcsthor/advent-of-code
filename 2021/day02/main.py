from utils.utils import load_data, print_answer
from numpy import ndarray


def calc_pos_and_depth(data: ndarray) -> int:
    position = 0
    depth = 0

    for line in data:
        direction, value = line

        if direction == "forward":
            position += int(value)
        else:
            depth += int(value) * (-1 if direction == "up" else 1)

    return position * depth


def calc_pos_and_depth_with_aim(data: ndarray) -> int:
    position = 0
    depth = 0
    aim = 0

    for line in data:
        direction, value = line

        if direction == "forward":
            position += int(value)
            depth += aim * int(value)
        else:
            aim += int(value) * (-1 if direction == "up" else 1)

    return position * depth


DAY = "02"
example_data, input_data = load_data(DAY)

example_data = [line.split() for line in example_data]
input_data = [line.split() for line in input_data]

example_pos_depth = calc_pos_and_depth(example_data)
input_pos_depth = calc_pos_and_depth(input_data)

print_answer((example_pos_depth, input_pos_depth), DAY, part=1)

example_pos_depth = calc_pos_and_depth_with_aim(example_data)
input_pos_depth = calc_pos_and_depth_with_aim(input_data)

print_answer((example_pos_depth, input_pos_depth), DAY, part=2)
