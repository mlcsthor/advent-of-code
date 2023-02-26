from utils.utils import load_data, print_answer, clamp
from numpy import array, count_nonzero


def calc_risk_level_sum(data):
    columns = len(data[0])
    lines = len(data[:, 0])
    risk_sum = 0

    for line in range(lines):
        for column in range(columns):
            element = data[line][column]

            column_prev = clamp(column - 1, 0, columns)
            column_next = clamp(column + 1, 0, columns)

            line_prev = clamp(line - 1, 0, lines)
            line_next = clamp(line + 1, 0, lines)

            horizontal = data[line, column_prev:column_next + 1]
            vertical = data[line_prev:line_next + 1, column]

            is_unique_horizontal = count_nonzero(horizontal == element) == 1
            is_unique_vertical = count_nonzero(vertical == element) == 1
            is_unique = is_unique_vertical and is_unique_horizontal

            if is_unique and element == min(horizontal) and element == min(vertical):
                risk_sum += (element + 1)

    return risk_sum


DAY = "09"
example_data, input_data = load_data(DAY)
example_data = array([list(line) for line in example_data]).astype(int)
input_data = array([list(line) for line in input_data]).astype(int)

example_answer = calc_risk_level_sum(example_data)
input_answer = calc_risk_level_sum(input_data)

print_answer((example_answer, input_answer), DAY, part=1)
