# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            team_dict = {"team": row["team"], "rating": int(row["rating"])}
            teams.append(team_dict)
            # print(team_dict['rating'])

# TODO: Simulate N tournaments and keep track of win counts
    counts = {}
    for i in range(0, N):
        torn_winner = simulate_tournament(teams)
        if torn_winner["team"] in counts:
            counts[torn_winner["team"]] += 1
        else:
            counts[torn_winner["team"]] = 1
    # print(counts)

    # # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    round_winner = teams
    for i in range(4):
        round_winner = simulate_round(round_winner)
    return round_winner[0]

    # print(f"{round_winner[0]}")


if __name__ == "__main__":
    main()
