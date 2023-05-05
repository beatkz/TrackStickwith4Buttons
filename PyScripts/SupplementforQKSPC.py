# coding: utf-8

import pyautogui
import keyboard
import pygame
import time
from decimal import Decimal, ROUND_HALF_UP

print("QuizKnockSTADIUM スタンプチャット補助用スクリプト")
print("終了するにはこのウインドウを閉じてください")

#SetupPart:
ScreenRez = pyautogui.size()
print("画面解像度： {}x{}".format(ScreenRez[0], ScreenRez[1]))

aspect = Decimal(ScreenRez[0]/ScreenRez[1]).quantize(Decimal('0.01'), rounding=ROUND_HALF_UP)
offsetX = 0
offsetY = 0

if (aspect != 1.78):
    rezScale = ScreenRez[1]/1080
    offsetX = (ScreenRez[0] - (1920 * rezScale)) / 2
elif (aspect == 1.78 and ScreenRez[0] != 1920):
    rezScale = ScreenRez[0]/1920
elif (aspect == 1.78 and ScreenRez[0] == 1920):
    rezScale = 1

print("スケール倍率： {}倍".format(rezScale))
    

PanelY = ((1650 + offsetX) * rezScale, (1000 + offsetY) * rezScale)
PanelCh = ((1850 + offsetX) * rezScale, (1000 + offsetY) * rezScale)

PanelCh1 = ((1650 + offsetX) * rezScale, (100 + offsetY) * rezScale)
PanelCh2 = ((1850 + offsetX) * rezScale, (100 + offsetY) * rezScale)
PanelCh3 = ((1650 + offsetX) * rezScale, (250 + offsetY) * rezScale)
PanelCh4 = ((1850 + offsetX) * rezScale, (250 + offsetY) * rezScale)
PanelCh5 = ((1650 + offsetX) * rezScale, (450 + offsetY) * rezScale)
PanelCh6 = ((1850 + offsetX) * rezScale, (450 + offsetY) * rezScale)
PanelCh7 = ((1650 + offsetX) * rezScale, (600 + offsetY) * rezScale)
PanelCh8 = ((1850 + offsetX) * rezScale, (600 + offsetY) * rezScale)
PanelChPg = ((1700 + offsetX) * rezScale, (800 + offsetY) * rezScale)

Keys = ['x', 'c', 'v', '5', '6', 't', 'y', 'g', 'h', 'b', 'n', 'q', 'w', 'e', 'r']
#Keys = ['x', 'c', 'v', '9', '0', 'o', 'p', 'l', ';', '.', '/', 'q', 'w', 'e', 'r']
#Keys = ['x', 'c', 'v', 'q', 'w', 'e', 'r', 'a', 's', 'd', 'f', 'y', 'u', 'i', 'o']


def clickPanel(key,targetXY):
    pyautogui.moveTo(targetXY)
    pyautogui.mouseDown()
    pyautogui.mouseUp()

def forPanelKnock(sendkey):
    keyboard.send(sendkey)

keyboard.add_hotkey(Keys[0], clickPanel, args=(Keys[0],PanelY))
keyboard.add_hotkey(Keys[1], clickPanel, args=(Keys[1],PanelCh))
keyboard.add_hotkey(Keys[2], clickPanel, args=(Keys[2],PanelChPg))
keyboard.add_hotkey(Keys[3], clickPanel, args=(Keys[3],PanelCh1))
keyboard.add_hotkey(Keys[4], clickPanel, args=(Keys[4],PanelCh2))
keyboard.add_hotkey(Keys[5], clickPanel, args=(Keys[5],PanelCh3))
keyboard.add_hotkey(Keys[6], clickPanel, args=(Keys[6],PanelCh4))
keyboard.add_hotkey(Keys[7], clickPanel, args=(Keys[7],PanelCh5))
keyboard.add_hotkey(Keys[8], clickPanel, args=(Keys[8],PanelCh6))
keyboard.add_hotkey(Keys[9], clickPanel, args=(Keys[9],PanelCh7))
keyboard.add_hotkey(Keys[10], clickPanel, args=(Keys[10],PanelCh8))
keyboard.add_hotkey(Keys[11], forPanelKnock, args=('5'))
keyboard.add_hotkey(Keys[12], forPanelKnock, args=('6'))
keyboard.add_hotkey(Keys[13], forPanelKnock, args=('7'))
keyboard.add_hotkey(Keys[14], forPanelKnock, args=('8'))

keyboard.wait()
