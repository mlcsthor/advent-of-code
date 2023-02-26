import re
import matplotlib.pyplot as plt

from utils.utils import load_data, print_answer
from numpy import split, where, delete, full, amax, ndarray, flip, count_nonzero


def create_paper(points: ndarray) -> ndarray:
    points = [list(map(int, point.split(','))) for point in points]
    width, height = amax(points, axis=0)

    paper = full([height + 1, width + 1], dtype=int, fill_value=0)
    for point in points:
        paper[point[1]][point[0]] = 1

    return paper


def parse_folds(folds: ndarray) -> []:
    fold_list = []

    for fold in folds:
        fold_infos = re.findall(r"(x|y)=([0-9]+)", fold)[0]
        fold_axis = 0 if fold_infos[0] == 'y' else 1
        fold_list.append((fold_axis, int(fold_infos[1])))

    return fold_list


def fold_paper(paper: ndarray, fold: tuple) -> ndarray:
    axis, position = fold

    if axis:
        first_half = paper[:, 0:position]
        second_half = paper[:, position + 1:]
    else:
        first_half = paper[0:position]
        second_half = paper[position + 1:]

    second_half = flip(second_half, axis)
    paper = first_half + second_half

    return paper


def get_paper_and_folds(data: ndarray) -> [ndarray, []]:
    empty_line = where(data == '')[0]
    data = delete(data, empty_line)
    points, folds = split(data, empty_line)

    paper = create_paper(points)
    folds = parse_folds(folds)

    return paper, folds


def count_points(data: ndarray) -> int:
    paper, folds = get_paper_and_folds(data)

    folded_paper = fold_paper(paper, folds[0])
    return count_nonzero(folded_paper)


def get_code(data: ndarray) -> None:
    paper, folds = get_paper_and_folds(data)

    for fold in folds:
        paper = fold_paper(paper, fold)

    points = where(paper != 0)
    plt.subplots(figsize=(16, 2))
    plt.scatter(points[1], -points[0], s=300)
    plt.show()


DAY = "13"
example_data, input_data = load_data(DAY)

example_points = count_points(example_data)
input_points = count_points(input_data)
print_answer((example_points, input_points), DAY, part=1)

get_code(input_data)
