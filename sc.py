import random

def generate_random_maze(width, height):
    # Initialize the maze with walls (1)
    maze = [['1'] * width for _ in range(height)]

    # Fill the inner cells with random values (0 or 1)
    for y in range(1, height - 1):
        for x in range(1, width - 1):
            maze[y][x] = random.choice(['0', '1'])

    return maze

def print_maze(maze):
    print("{")
    for row in maze:
        print("{" + ",".join(row) + "},")
    print("}")

# Example usage:
width = 20
height = 16
random_maze = generate_random_maze(width, height)

print("Generated Random Maze:")
print_maze(random_maze)