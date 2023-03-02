# coding: utf-8

import pyautogui
import keyboard
import pygame

print("QuizKnockSTADIUM スタンプチャット補助用スクリプト")
print("終了するにはCtrlキーを押しながらCを押すか、ウインドウを閉じてください")
#SetupPart:
ScreenRez = pyautogui.size()
print("画面解像度： {}x{}".format(ScreenRez[0], ScreenRez[1]))
if ScreenRez[0] != 1920:
    rezScale = ScreenRez[0]/1920
    print("スケール倍率： {}倍".format(rezScale))
else:
    rezScale = 1

PanelA = (850 * rezScale, 850 * rezScale)
PanelB = (1100 * rezScale, 850 * rezScale)
PanelC = (1340 * rezScale, 850 * rezScale)
PanelD = (1600 * rezScale, 850 * rezScale)
PanelY = (1650 * rezScale, 1000 * rezScale)
PanelCh = (1850 * rezScale, 1000 * rezScale)
PanelCh1 = (1650 * rezScale, 100 * rezScale)
PanelCh2 = (1850 * rezScale, 100 * rezScale)
PanelCh3 = (1650 * rezScale, 250 * rezScale)
PanelCh4 = (1850 * rezScale, 250 * rezScale)
PanelCh5 = (1650 * rezScale, 450 * rezScale)
PanelCh6 = (1850 * rezScale, 450 * rezScale)
PanelCh7 = (1650 * rezScale, 600 * rezScale)
PanelCh8 = (1850 * rezScale, 600 * rezScale)
PanelChPg = (1700 * rezScale, 800 * rezScale)


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
