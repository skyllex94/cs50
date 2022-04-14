from cs50 import get_float

quarter, dime, nickel, pennie = 0.25, 0.10, 0.05, 0.01
change_accumulation = 0.00
amount_of_change = 0


def main():
    global change_accumulation
    global amount_of_change

    change = get_input()
    difference = float(format((change - change_accumulation), ".2f"))

    while (change > change_accumulation):
        if (change - change_accumulation >= quarter):
            add_change(quarter)
        elif (change - change_accumulation >= dime):
            add_change(dime)
        elif (difference >= nickel):
            add_change(nickel)
        else:
            add_change(pennie)

    print(f"{amount_of_change}")


def add_change(change):
    global change_accumulation
    global amount_of_change
    change_accumulation += change
    change_accumulation = float(format(change_accumulation, ".2f"))
    amount_of_change += 1


def get_input():
    reprompt = True
    while(reprompt):
        change = get_float("Your change: ")
        if (change < 0.0):
            reprompt = True
        else:
            reprompt = False
    return change


if __name__ == "__main__":
    main()
