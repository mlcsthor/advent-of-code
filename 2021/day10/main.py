from utils.utils import load_data, print_answer
from numpy import ndarray

OPEN_CHAR = ["(", "[", "{", "<"]
CLOSE_CHAR = [")", "]", "}", ">"]

ERROR_POINTS = [3, 57, 1197, 25137]
INCOMPLETE_POINTS = [1, 2, 3, 4]


def is_corrupted(string_to_check) -> [bool, [str]]:
    stack = []

    for character in string_to_check:
        if character in OPEN_CHAR:
            stack.append(character)
        else:
            last_opened = OPEN_CHAR.index(stack[-1])
            expected_close = CLOSE_CHAR[last_opened]

            if character == expected_close:
                stack.pop()
            else:
                return True, [character]

    stack.reverse()
    return False, stack


def calc_syntax_error_score(data: ndarray) -> int:
    score = 0

    for line in data:
        corrupted, wrong_char = is_corrupted(line)
        if corrupted:
            score += ERROR_POINTS[CLOSE_CHAR.index(wrong_char[0])]

    return score


def calc_middle_score(data: ndarray) -> int:
    scores = []

    for line in data:
        score = 0
        corrupted, incomplete_stack = is_corrupted(line)

        if not corrupted:
            for character in incomplete_stack:
                score *= 5
                score += INCOMPLETE_POINTS[OPEN_CHAR.index(character)]

            scores.append(score)

    scores.sort()
    return scores[int(len(scores)/2)]


DAY = "10"
example_data, input_data = load_data("10")

example_error_score = calc_syntax_error_score(example_data)
input_error_score = calc_syntax_error_score(input_data)

example_middle_score = calc_middle_score(example_data)
input_middle_score = calc_middle_score(input_data)

print_answer((example_error_score, input_error_score), DAY, part=1)
print_answer((example_middle_score, input_middle_score), DAY, part=2)
