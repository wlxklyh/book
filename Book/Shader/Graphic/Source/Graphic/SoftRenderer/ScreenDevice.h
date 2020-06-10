// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class  ScreenDevice
{
public:
	ScreenDevice()
	{
		Init();
	};
	~ScreenDevice()
	{
		
	};
	//ÆÁÄ»·Ö±æÂÊ¿í
	int ScreenWidth;
	//ÆÁÄ»·Ö±æÂÊ¸ß
	int ScreenHeight;
	//ÆÁÄ»»º³å
	unsigned char* FrameBuff;

	void Init()
	{
		//ÆÁÄ»ÏñËØ·Ö±æÂÊ
		ScreenWidth = 1024;
		ScreenHeight = 1024;
		//ÆÁÄ»»º³å  Ã¿¸öÏñËØÊÇRGBA ËùÒÔ4×Ö½Ú
		FrameBuff = (unsigned char*)malloc(ScreenWidth * ScreenHeight * 4);

		//Test
		for (int i = ScreenHeight; i >= 0; i--)
		{
			for (int j = ScreenWidth; j >= 0; j--)
			{
				//R
				FrameBuff[i * ScreenWidth + j] = 0x0;
				//G
				FrameBuff[i * ScreenWidth + j + 1] = 0xFF;
				//B
				FrameBuff[i * ScreenWidth + j + 2] = 0x0;
				//A
				FrameBuff[i * ScreenWidth + j + 3] = 0xFF;
			}
		}
	}
};
