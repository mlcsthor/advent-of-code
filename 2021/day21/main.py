from utils.utils import load_data, print_answer
from numpy import ndarray


def get_initial_positions(data: ndarray) -> [int, int]:
    _, player1 = data[0].split(': ')
    _, player2 = data[1].split(': ')

    return [int(player1), int(player2)]


def play_with_deterministic_dice(initial_positions: [int, int]) -> int:
    players_position = initial_positions
    players_score = [0, 0]

    roll = 1
    roll_count = 0

    while players_score[0] < 1000 and players_score[1] < 1000:
        roll_count += 3
        player = (roll + 1) % 2
        roll_score = sum([roll, roll + 1, roll + 2])

        move_to = (players_position[player] + roll_score) % 10
        move_to = move_to if move_to != 0 else 10

        players_position[player] = move_to
        players_score[player] += move_to

        next_throw = (roll + 3) % 100
        roll = next_throw if next_throw != 0 else 100

    losing_score = min(players_score[0], players_score[1])
    return losing_score * roll_count


DAY = "21"
example_data, input_data = load_data(DAY)

example_positions = get_initial_positions(example_data)
example_answer = play_with_deterministic_dice(example_positions)

input_positions = get_initial_positions(input_data)
input_answer = play_with_deterministic_dice(input_positions)

print_answer((example_answer, input_answer), DAY, part=1)
