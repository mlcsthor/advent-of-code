import numbers
import os
import numpy
from numpy import ndarray


def load_data(day: str) -> [ndarray, ndarray]:
    return open_file(day, "example"), open_file(day, "input")


def open_file(day: str, filename: str) -> ndarray:
    script_dir = os.path.dirname(__file__)
    file_path = os.path.join(script_dir, "..", f"day{day}", f"{filename}.txt")

    with open(file_path, 'r') as file:
        lines = file.readlines()

    lines = numpy.array([line.strip() for line in lines])
    return lines


def clamp(num: numbers, min_value: numbers, max_value: numbers) -> numbers:
    return max(min(num, max_value), min_value)


def print_answer(answers: tuple, day: str, part: int) -> None:
    if part == 1:
        print(f'##### Advent of Code 2021 Day {day} #####')

    print(f'# Part {part}')
    print(f'Example : {answers[0]}')
    print(f'Answer : {answers[1]}')
