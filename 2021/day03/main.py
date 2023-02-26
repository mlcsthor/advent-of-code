from utils.utils import load_data, print_answer
from numpy import unique, array, invert, ndarray


def get_most_common_bit(column: ndarray) -> int:
    unique_char, counts = unique(column, return_counts=True)
    count = dict(zip(unique_char, counts))

    return 1 if count['0'] == count['1'] else max(count, key=count.get)


def calc_gamma_and_epsilon_rate(data: ndarray) -> int:
    data_bin = array([list(line) for line in data])
    gamma_rate = array([get_most_common_bit(column) for column in data_bin.T])
    epsilon_rate = invert(gamma_rate.astype(bool)).astype(int)

    return int(''.join(map(str, gamma_rate)), 2) * int(''.join(map(str, epsilon_rate)), 2)


def calc_oxygen_and_co2_rate(data: ndarray) -> int:
    oxygen_data = co2_data = data

    for i in range(0, len(data[0])):
        oxygen_data = keep_correct_lines(oxygen_data, i)
        co2_data = keep_correct_lines(co2_data, i, is_co2=True)

    return int(oxygen_data[0], 2) * int(co2_data[0], 2)


def keep_correct_lines(data: ndarray, index: int, is_co2: bool = False) -> [str]:
    if len(data) == 1:
        return data

    binary = array([list(line) for line in data])
    maximum = int(get_most_common_bit(binary[:, index]))

    if is_co2:
        maximum = 1 - maximum

    data = [line for line in data if line[index] == str(maximum)]

    return data


DAY = "03"
example_data, input_data = load_data(DAY)

example_gamma_epsilon = calc_gamma_and_epsilon_rate(example_data)
input_gamma_epsilon = calc_gamma_and_epsilon_rate(input_data)

example_oxygen_co2 = calc_oxygen_and_co2_rate(example_data)
input_oxygen_co2 = calc_oxygen_and_co2_rate(input_data)

print_answer((example_gamma_epsilon, input_gamma_epsilon), DAY, part=1)
print_answer((example_oxygen_co2, input_oxygen_co2), DAY, part=2)
