from assets import *


# initial setup
print('\n########## Solitaire Accordion ##########\n\nRead the instructions bellow!\nThe goal for this game is putting all cards on the same stack.\n  -- You can perform only 2 moves:\n        1. Stack a card on its immediately before card;\n        2. Stack a card on its third before card.\n  -- So that a move can be performed, one of the following should be true:\n        1. Both cards have the same rank\n        2. Both cards have the same suit.\nPress [Enter] to begin the game...')
if input('') == '':
    running = True

# main loop
while running == True:
    deck = create_deck()
    while True:
        can_move = any_moves_left(deck)
        if can_move == False:
            break
        position_list = range(len(deck))

        # show the deck
        print('Your deck is displayed like:')
        for p in position_list:
            card = deck[p] # get position and card info
            print(f'{p}. {card}') # print each card

    # prompt the next move for the player
        try:
            card_choice = int(input(f'Choose a card (type a number between 0 and {max(position_list)}): '))
        except:
            card_choice = int(input(f'Choose a card (type a number between 0 and {max(position_list)}): '))
        if card_choice not in position_list: # the choice is not in the deck
            continue
        move_list = moves_left(deck, card_choice)
        if move_list == []:
            continue # the choice can not make a move

        # stack the choice on other card
        if len(move_list) == 1: # stack the selected card on the only possible move
            deck = stack(deck, card_choice, card_choice-move_list[0])
        elif len(move_list) == 2: # prompt for which possible stack should be used
            print(f'Which card do you want to stack {deck[card_choice]} on?')
            print(f'1. {deck[card_choice-1]}')
            print(f'2. {deck[card_choice-3]}')
            stack_choice = 1 if int(input('Choose 1 or 2: ')) == 1 else 3
            deck = stack(deck, card_choice, card_choice-stack_choice)

    # when game ended, print the result and ask for a new game
    endgame_message = 'Congrats, you won!' if len(deck) == 1 else 'Train more, you lost.'
    print(endgame_message)
    next_state = input('Wanna play again (y/n)? ')
    running = next_state == 'y'
