// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUICpp.h"
#include "ImageUtils.h"
#include "Engine/Texture2DDynamic.h"

void UMainUICpp::WriteRawToTexture_RenderThread_My(FTexture2DDynamicResource* TextureResource, const TArray<uint8>& RawData, bool bUseSRGB )
{
	FTexture2DRHIParamRef TextureRHI = TextureResource->GetTexture2DRHI();

	int32 Width = TextureRHI->GetSizeX();
	int32 Height = TextureRHI->GetSizeY();

	uint32 DestStride = 0;
	uint8* DestData = reinterpret_cast<uint8*>(RHILockTexture2D(TextureRHI, 0, RLM_WriteOnly, DestStride, false, false));

	for (int32 y = 0; y < Height; y++)
	{
		uint8* DestPtr = &DestData[(Height - 1 - y) * DestStride];

		const FColor* SrcPtr = &((FColor*)(RawData.GetData()))[(Height - 1 - y) * Width];
		for (int32 x = 0; x < Width; x++)
		{
			*DestPtr++ = SrcPtr->B;
			*DestPtr++ = SrcPtr->G;
			*DestPtr++ = SrcPtr->R;
			*DestPtr++ = SrcPtr->A;
			SrcPtr++;
		}
	}

	RHIUnlockTexture2D(TextureRHI, 0, false, false);
}

void UMainUICpp::NativeConstruct()
{	
	if (UImage* img = Cast<UImage>(GetWidgetFromName(FName(TEXT("MainImage")))))
	{
		MainImage = img;
	}

	MainTexture = UTexture2DDynamic::Create(1024, 1024, FTexture2DDynamicCreateInfo());

}

void UMainUICpp::Update(float InDeltaTime)
{
	TArray<uint8> SrcData;
	for (int i = Device.ScreenHeight; i >= 0; i--)
	{
		for (int j = Device.ScreenWidth; j >= 0; j--)
		{
			SrcData[i * Device.ScreenWidth + j + 0] = Device.FrameBuff[i * Device.ScreenWidth + j + 0];
			SrcData[i * Device.ScreenWidth + j + 1] = Device.FrameBuff[i * Device.ScreenWidth + j + 1];
			SrcData[i * Device.ScreenWidth + j + 2] = Device.FrameBuff[i * Device.ScreenWidth + j + 2];
			SrcData[i * Device.ScreenWidth + j + 3] = Device.FrameBuff[i * Device.ScreenWidth + j + 3];
		}
	}

	//UTexture2D* texture2d = FImageUtils::CreateTexture2D(1024, 1024, SrcData, this, "TextureMain",
	//	EObjectFlags::RF_ArchetypeObject, FCreateTexture2DParameters());
	
	//int32 Width = TextureRHI->GetSizeX();
	//int32 Height = TextureRHI->GetSizeY();

	//uint32 DestStride = 0;
	//uint8* DestData = reinterpret_cast<uint8*>(RHILockTexture2D(TextureRHI, 0, RLM_WriteOnly, DestStride, false, false));

	//for (int32 y = 0; y < Height; y++)
	//{
	//	uint8* DestPtr = &DestData[(Height - 1 - y) * DestStride];
	//	const FColor* SrcPtr = &(SrcData[(Height - 1 - y) * Width]);
	//	for (int32 x = 0; x < Width; x++)
	//	{
	//		*DestPtr++ = SrcPtr->B;
	//		*DestPtr++ = SrcPtr->G;
	//		*DestPtr++ = SrcPtr->R;
	//		*DestPtr++ = SrcPtr->A;
	//		SrcPtr++;
	//	}
	//}

	//RHIUnlockTexture2D(TextureRHI, 0, false, false);

	//WriteRawToTexture_RenderThread_My(new FTexture2DDynamicResource(MainTexture), SrcData);
	//if (MainImage && MainTexture)
	//{
	//	MainImage->SetBrushFromTextureDynamic(MainTexture);
	//}
}

