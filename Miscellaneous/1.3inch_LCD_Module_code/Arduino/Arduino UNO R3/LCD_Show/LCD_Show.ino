#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  LCD_SetBackLight(80);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_SetRotate(180);
  Paint_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);
  Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
  Paint_DrawString_CN(50,180, "微雪电子",  &Font24CN, WHITE, RED);
  Paint_DrawRectangle(125, 10, 225, 58, RED,DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  Paint_DrawLine(125, 10, 225, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
  Paint_DrawLine(225, 10, 125, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
  
  Paint_DrawCircle(150,100, 25, BLUE,  DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  Paint_DrawCircle(180,100, 25, BLACK,    DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  Paint_DrawCircle(210,100, 25, RED, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  Paint_DrawCircle(165,125, 25, YELLOW,   DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  Paint_DrawCircle(195,125, 25, GREEN,   DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  
  Paint_DrawImage(gImage_70X70, 20, 80, 70, 70); 

}
void loop()
{
  
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

