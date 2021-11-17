#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "DEV_Config.h"
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"
#include "DEV_Config.h"


void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:Program  End\r\n");
    DEV_ModuleExit();

    exit(0);
}


int main(int argc, char **argv)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    
	if(DEV_ModuleInit()==1)
		return 1;

	LCD_SetBackLight(500);
    printf("Jetson Nano  Test program\r\n");
    printf("Longer refresh time\r\n");
    printf("Please wait for the screen\r\n");
	LCD_Init();
	LCD_Clear(0x0000);
	Paint_NewImage(LCD_WIDTH, LCD_HEIGHT,0,WHITE);
	Paint_Clear(WHITE);
	Paint_SetRotate(180);
	Paint_DrawString_EN(30, 10, "123", &Font24, 0x000f, 0xfff0);
	Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
	Paint_DrawString_CN(50,180, "Î¢Ñ©µç×Ó",  &Font24CN, WHITE, RED);
	Paint_DrawRectangle(125, 10, 225, 58, RED,DRAW_FILL_EMPTY, DOT_PIXEL_2X2 );
	Paint_DrawLine(125, 10, 225, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
	Paint_DrawLine(225, 10, 125, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);

	Paint_DrawCircle(150,100, 25, BLUE,  DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
	Paint_DrawCircle(180,100, 25, BLACK,    DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
	Paint_DrawCircle(210,100, 25, RED, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
	Paint_DrawCircle(165,125, 25, YELLOW,   DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
	Paint_DrawCircle(195,125, 25, GREEN,   DRAW_FILL_EMPTY, DOT_PIXEL_2X2);

	Paint_DrawImage(gImage_100X100, 10, 75,100, 100); 
	DEV_Delay_ms(2000);
	Paint_DrawImage(gImage_240X240, 0, 0, 240, 240); 
	
	while(1){

	}
	DEV_ModuleExit();
}
