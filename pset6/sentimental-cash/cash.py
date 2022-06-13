while True:
    try:
        change = float(input("Cash owed: "))
        if change > 0:
            break
    except ValueError:
        None
cents, coins = round(change * 100), 0
while cents > 0:
    if cents >= 25:
        cents -= 25
    elif cents >= 10:
        cents -= 10
    elif cents >= 5:
        cents -= 5
    else:
        cents -= 1
    coins += 1
print(f"{coins}\n")