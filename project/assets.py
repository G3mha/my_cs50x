import random


def create_deck():
    suits = ['♠', '♣', '♦', '♥']
    ranks = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
    deck = [rank + suit for rank in ranks for suit in suits]
    random.shuffle(deck)
    return deck

def moves_left(deck, position):
    move_list, selection, before_selection, three_before_selection = [], deck[position], deck[position-1], deck[position-3]
    if position > 0:
        if (get_rank(before_selection) == get_rank(selection)) or (get_suit(before_selection) == get_suit(selection)):
            move_list.append(1)
    if position > 2:
        if (get_rank(three_before_selection) == get_rank(selection)) or (get_suit(three_before_selection) == get_suit(selection)):
            move_list.append(3)
    return move_list

def any_moves_left(deck):
    for i in range(len(deck)): # iterate over the deck
        if not(bool(moves_left(deck, i))): # check if the list is empty
            return True # if empty, no moves left
    return False

def stack(deck, selected_card, stackable_card):
    deck[stackable_card] = deck.pop(selected_card) # stack a card on another
    return deck

def get_rank(card):
    if card[:2] == '10': # card rank
        return '10'
    return card[0]

def get_suit(card):
    if card[:2] == '10': # card rank
        return card[2]
    return card[1]
