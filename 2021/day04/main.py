from utils.utils import load_data, print_answer
from numpy import empty, full, where, concatenate, ndarray, delete


def create_boards(data: ndarray) -> [[ndarray], [ndarray]]:
    boards = []
    board_line = 0
    board = empty([5, 5], dtype=int)

    for line in data:
        if not line:
            boards.append(board)
            board = empty([5, 5], dtype=int)
            board_line = 0
        else:
            board[board_line] = line.split()
            board_line += 1

    boards.append(board)
    marked = [full([5, 5], False, dtype=bool) for _ in boards]

    return boards, marked


def check_board(board: ndarray, marked: ndarray, value: int):
    indexes = concatenate(where(board == value))

    if len(indexes):
        marked[indexes[0]][indexes[1]] = True


def is_board_win(marked: ndarray) -> int:
    return len(where(marked.all(axis=1))[0]) or len(where(marked.all(axis=0))[0])


def play_bingo(boards: [ndarray], marked: [ndarray], draws: [int]) -> [int, int, int, int]:
    boards_finished = []
    numbers_drawn_after_win = []
    number_boards = len(boards)

    for draw in draws:
        for b in range(0, number_boards):
            if b in boards_finished:
                continue

            if not is_board_win(marked[b]):
                check_board(boards[b], marked[b], draw)

            if is_board_win(marked[b]):
                boards_finished.append(b)

        if len(boards_finished):
            numbers_drawn_after_win.append(draw)

        if len(boards_finished) == number_boards:
            break

    return boards_finished[0], numbers_drawn_after_win[0], boards_finished[-1], numbers_drawn_after_win[-1]


def calc_score(winning_board: ndarray, winning_marked: ndarray, last_draw: int) -> int:
    index_where = where(~winning_marked)
    indexes = list(zip(index_where[0], index_where[1]))
    win_sum = 0

    for index_tuple in indexes:
        win_sum += winning_board[index_tuple[0]][index_tuple[1]]

    return win_sum * last_draw


def play(data: ndarray) -> [int, int]:
    draws = list(map(int, data[0].split(',')))
    data = delete(data, [0, 1])
    boards, marked = create_boards(data)

    winning, winning_draw, last_winning, last_draw = play_bingo(boards, marked, draws)

    score = calc_score(boards[winning], marked[winning], winning_draw)
    last_score = calc_score(boards[last_winning], marked[last_winning], last_draw)

    return score, last_score


DAY = "04"
example_data, input_data = load_data(DAY)

example_score, example_last_score = play(example_data)
input_score, input_last_score = play(input_data)

print_answer((example_score, input_score), DAY, part=1)
print_answer((input_score, input_last_score), DAY, part=2)
