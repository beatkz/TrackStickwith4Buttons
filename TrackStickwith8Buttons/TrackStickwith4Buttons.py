# coding: utf-8

import pyautogui
import keyboard
import pygame

print("QuizKnockSTADIUM 回答補助用スクリプト")
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
PanelCh1 = (1850 * rezScale, 150 * rezScale)


while True:
    '''
    if keyboard.is_pressed("1"):
        pyautogui.moveTo(PanelA)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("2"):
        pyautogui.moveTo(PanelB)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("3"):
        pyautogui.moveTo(PanelC)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("4"):
        pyautogui.moveTo(PanelD)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    '''

    if keyboard.is_pressed("X"):
        pyautogui.moveTo(PanelY)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
    elif keyboard.is_pressed("C"):
        pyautogui.moveTo(PanelCh)
        pyautogui.mouseDown()
        pyautogui.mouseUp()
        pyautogui.moveTo(PanelCh1)