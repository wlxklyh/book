// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUICpp.h"
#include "ImageUtils.h"




void UMainUICpp::NativeConstruct()
{	
	if (UImage* img = Cast<UImage>(GetWidgetFromName(FName(TEXT("MainImage")))))
	{
		MainImage = img;
	}


}
//
//void UMainUICpp::Update(float InDeltaTime)
//{
//	TArray<FColor> SrcData;
//	/*for (int i = Device.ScreenHeight; i >= 0; i--)
//	{
//		for (int j = Device.ScreenWidth; j >= 0; j--)
//		{
//			SrcData.Add(FColor(Device.FrameBuff[i * Device.ScreenWidth + j],
//				Device.FrameBuff[i * Device.ScreenWidth + j + 1],
//				Device.FrameBuff[i * Device.ScreenWidth + j + 2],
//				Device.FrameBuff[i * Device.ScreenWidth + j + 3]));
//		}
//	}
//		
//
//	MainTexture = FImageUtils::CreateTexture2D(1024, 1024, SrcData, this, "TextureMain",
//		EObjectFlags::RF_ArchetypeObject, FCreateTexture2DParameters());
//
//	if (MainImage)
//	{
//		MainImage->SetBrushFromTexture(MainTexture);
//	}*/
//}
