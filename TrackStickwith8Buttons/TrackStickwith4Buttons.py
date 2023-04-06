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


while True:
    if keyboard.is_pressed("x"):
        pyautogui.moveTo(PanelY)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("c"):
        pyautogui.moveTo(PanelCh)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("q"):
        pyautogui.moveTo(PanelCh1)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("w"):
        pyautogui.moveTo(PanelCh2)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("e"):
        pyautogui.moveTo(PanelCh3)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("r"):
        pyautogui.moveTo(PanelCh4)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("a"):
        pyautogui.moveTo(PanelCh5)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("s"):
        pyautogui.moveTo(PanelCh6)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("d"):
        pyautogui.moveTo(PanelCh7)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("f"):
        pyautogui.moveTo(PanelCh8)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("g"):
        pyautogui.moveTo(PanelChPg)
        pyautogui.mouseDown()
        pyautogui.mouseUp()

    time.sleep(0.03)