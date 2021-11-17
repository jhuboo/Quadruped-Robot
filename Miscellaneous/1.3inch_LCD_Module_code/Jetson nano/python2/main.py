#!/usr/bin/python
# -*- coding:utf-8 -*-

import ST7789
import time
import config
import traceback

from PIL import Image,ImageDraw,ImageFont

try:
    # 240x240 display with hardware SPI:
    disp = ST7789.ST7789()

    # Initialize library.
    disp.Init()
    print("\r\nJetson Nano Test program")
    print("Longer refresh time")
    # Clear display.
    disp.clear()

    # Create blank image for drawing.
    image1 = Image.new("RGB", (disp.width, disp.height), "WHITE")
    draw = ImageDraw.Draw(image1)
    font = ImageFont.truetype('Font.ttf', 30)
    font10 = ImageFont.truetype('Font.ttf',13)
    print "***draw line"
    draw.line([(40,20),(200,20)], fill = "BLUE",width = 5)
    draw.line([(40,20),(40,200)], fill = "BLUE",width = 5)
    draw.line([(40,200),(200,200)], fill = "BLUE",width = 5)
    draw.line([(200,20),(200,200)], fill = "BLUE",width = 5)
    print "***draw rectangle"
    draw.rectangle([(50,30),(190,70)],fill = "BLUE")

    print "***draw text"
    draw.text((60,30), u'微雪电子 ', font = font, fill = "WHITE")
    draw.text((50, 75), 'Waveshare Electronic ', font = font10, fill = "BLUE")
    draw.text((75, 110), '1.3inch LCD ', font = font10, fill = "BLUE")
    draw.text((72, 140), 'Test Program ', font = font10, fill = "BLUE")
    #image1=image1.rotate(45) 
    disp.ShowImage(image1,0,0)
    time.sleep(3)

    image = Image.open('pic.jpg')	
    disp.ShowImage(image,0,0)
    
except KeyboardInterrupt, Exception:
    print '\r\ntraceback.format_exc():\n%s' % traceback.format_exc()
    config.module_exit()
    exit()

