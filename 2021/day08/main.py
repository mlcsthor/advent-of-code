from utils.utils import load_data, print_answer
from numpy import array, ndarray, asarray


def sort_string(string: str):
    return ''.join(sorted(string))


def count_simple_digits(data: ndarray) -> int:
    output_list = []

    for data_line in data:
        _, outputs = data_line.split(' | ')
        output_list.extend(outputs.split(' '))

    output_list = array(output_list)

    number_of_1 = len(filter_by_length(output_list, 2))
    number_of_4 = len(filter_by_length(output_list, 4))
    number_of_7 = len(filter_by_length(output_list, 3))
    number_of_8 = len(filter_by_length(output_list, 7))

    return number_of_1 + number_of_4 + number_of_7 + number_of_8


def contains(list1: [], list2: []) -> bool:
    return all(item in list1 for item in list2)


def find_containing(elements: [], contain: [], invert: bool = False):
    for element in elements:
        if not invert and contains(list(element), contain):
            return element
        elif invert and contains(contain, list(element)):
            return element


def filter_by_length(data: ndarray, length: int) -> []:
    return list(filter(lambda element: len(element) == length, data))


def get_one(data: ndarray) -> str:
    return sort_string(filter_by_length(data, 2)[0])


def get_three(data: ndarray, digit_one: str) -> str:
    five_segments = filter_by_length(data, 5)

    return sort_string(find_containing(five_segments, list(digit_one)))


def get_four(data: ndarray) -> str:
    return sort_string(filter_by_length(data, 4)[0])


def get_seven(data: ndarray) -> str:
    return sort_string(filter_by_length(data, 3)[0])


def get_eight(data: ndarray) -> str:
    return sort_string(filter_by_length(data, 7)[0])


def get_nine(data: ndarray, digit_four: str) -> str:
    six_segments = filter_by_length(data, 6)

    return sort_string(find_containing(six_segments, list(digit_four)))


def get_zero_and_six(data: ndarray, digit_one: str, digit_nine: str) -> [str, str]:
    return deduce(data, 6, digit_nine, digit_one)


def get_two_and_five(data: ndarray, digit_three: str, digit_six: str) -> [str, str]:
    digit_five, digit_two = deduce(data, 5, digit_three, digit_six, invert=True)
    return digit_two, digit_five


def deduce(data: ndarray, seg: int, alr_fnd: str, must_cont: str, invert: bool = False) -> [str, str]:
    digit_segments = [sort_string(e) for e in filter_by_length(data, seg)]
    digit_segments.remove(alr_fnd)

    digit_containing = sort_string(find_containing(digit_segments, list(must_cont), invert))
    digit_segments.remove(digit_containing)

    other_digit = sort_string(digit_segments[0])
    return digit_containing, other_digit


def get_mapping_dict(data: ndarray) -> dict:
    mapping_dict = {}

    one = get_one(data)
    mapping_dict[one] = '1'

    four = get_four(data)
    mapping_dict[four] = '4'

    seven = get_seven(data)
    mapping_dict[seven] = '7'

    eight = get_eight(data)
    mapping_dict[eight] = '8'

    three = get_three(data, one)
    mapping_dict[three] = '3'

    nine = get_nine(data, four)
    mapping_dict[nine] = '9'

    zero, six = get_zero_and_six(data, one, nine)
    mapping_dict[zero] = '0'
    mapping_dict[six] = '6'

    two, five = get_two_and_five(data, three, six)
    mapping_dict[two] = '2'
    mapping_dict[five] = '5'

    return mapping_dict


def output_to_number(output_list: [], mapping_dict: dict) -> int:
    output_number = ''

    for digit in output_list:
        output_number += mapping_dict[sort_string(digit)]

    return int(output_number)


def get_output_sum(data: ndarray) -> int:
    output_sum = 0

    for line in data:
        mapping, output = line.split(' | ')
        mapping = array(mapping.split(' '))
        output = output.split(' ')

        mapping_dict = get_mapping_dict(mapping)
        output_sum += output_to_number(output, mapping_dict)

    return output_sum


DAY = "08"
example_data, input_data = load_data(DAY)

example_simple = count_simple_digits(example_data)
input_simple = count_simple_digits(input_data)

print_answer((example_simple, input_simple), DAY, part=1)

example_sum = get_output_sum(example_data)
input_sum = get_output_sum(input_data)

print_answer((example_sum, input_sum), DAY, part=2)
