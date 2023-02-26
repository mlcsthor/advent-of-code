from utils.utils import load_data, print_answer
from numpy import where, append, array, ndarray


def calc_number_of_fish(data: ndarray, days: int) -> int:
    for _ in range(days):
        new = [8 for _ in where(data - 1 == -1)[0]]

        for i in range(len(data)):
            d = data[i] - 1
            data[i] = d if d != -1 else 6

        data = append(data, new).astype(int)

    return len(data)


DAY = "06"
example_data, input_data = load_data("06")
example_data = array(example_data[0].split(',')).astype(int)
input_data = array(input_data[0].split(',')).astype(int)

example_answer1 = calc_number_of_fish(example_data, 80)
input_answer1 = calc_number_of_fish(input_data, 80)

print_answer((example_answer1, input_answer1), DAY, part=1)
