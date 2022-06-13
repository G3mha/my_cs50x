def get_height():
    while True:
        try:
            height = int(input('Height: '))
            if (height > 0 and height < 9):
                break
        except ValueError:
            a = 0
    return height


def draw(height, h):
    if height == 0:
        return
    draw(height - 1, h)
    print(' ' * (h - height), end='')
    print('#' * height)


height = get_height()
draw(height, height)