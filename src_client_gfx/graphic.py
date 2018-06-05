#! /usr/bin/env python3

import pygame
from pygame.locals import *


pygame.init()

BLOCK_SIZE = 50
WIDTH = 100
HEIGHT = 300
COLOR = (255, 255, 255)


class Camera(object):
    def __init__(self, camera_func, width, height):
        self.camera_func = camera_func
        self.state = Rect(0, 0, width, height)

    def apply(self, target):
        return target.rect.move(self.state.topleft)

    def update(self, target):
        self.state = self.camera_func(self.state, target.rect)

window = pygame.display.set_mode(
    (BLOCK_SIZE*WIDTH, BLOCK_SIZE*HEIGHT), RESIZABLE)
for y in range(HEIGHT):
    for x in range(WIDTH):
        rect = pygame.Rect(x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
        pygame.draw.rect(window, COLOR, rect, 1)

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            exit()
    pygame.display.flip()
    continue
