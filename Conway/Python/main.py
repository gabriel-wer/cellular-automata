#!/usr/bin/env python
import random 
import pygame
import argparse

parser = argparse.ArgumentParser(description='TEste')
parser.add_argument("-e", "--empty", action='store_true', help="set this flag if you wanna draw")
parser.add_argument("-r", "--rows",  type=int, default=10, help="set the number of rows")
parser.add_argument("-c", "--columns",  type=int, default=10, help="set the number of columns")
parser.add_argument("-cs", "--cell",  type=int, default=20, help="set the cell size")
args = parser.parse_args()

CELLSIZE = args.cell
ROWS = args.rows
COLUMNS = args.columns

def draw_map(canvas, i, j):
        pygame.draw.rect(canvas, (0,255,0),
                         pygame.Rect(i*CELLSIZE, j*CELLSIZE, CELLSIZE-2, CELLSIZE-2))

def calculate(neigh, c):
    if neigh == 2:
        return c
    if neigh == 3:
        return 1
    if neigh > 3 or neigh < 2:
        return 0

def detect_collision(arr, i, j, c):
    count = 0
    for x in range(i-1, i+2):
        for y in range(j-1, j+2):
            try:
                if arr[x][y] == 1:
                    count += 1
                    continue
            except IndexError:
                pass
    if c == 1:
        count -= 1
    return calculate(count, c)

pygame.init()
canvas = pygame.display.set_mode(((CELLSIZE *  COLUMNS), (CELLSIZE * ROWS)))
pygame.display.set_caption("Conway's Game of Life")

if args.empty:
    arr = [[0 for _ in range(ROWS)] for _ in range(COLUMNS)]
    drawing = False
else:
    #populates array with values from 0-1
    drawing = True
    arr = [[random.randint(0,1) for _ in range(ROWS)] for _ in range(COLUMNS)]

clock = pygame.time.Clock()
running = True
while running:
    canvas.fill((0,0,0))
    if drawing: clock.tick(10)
    for i, _ in enumerate(arr):
        for j, c in enumerate(arr[i]):
            if drawing:
                arr[i][j] = detect_collision(arr, i, j, c)
            if arr[i][j] == 1:
                draw_map(canvas, i, j)
    pygame.display.update()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False 
            if event.key == pygame.K_SPACE: drawing = not drawing
        if pygame.mouse.get_pressed()[0]:
            mouse_pos = pygame.mouse.get_pos()
            i = mouse_pos[0] // CELLSIZE
            j = mouse_pos[1] // CELLSIZE
            arr[i][j] = 1
            draw_map(canvas, i, j)
