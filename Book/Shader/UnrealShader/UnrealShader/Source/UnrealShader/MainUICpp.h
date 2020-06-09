// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "MainUICpp.generated.h"

/**
 * 
 */



UCLASS()
class UNREALSHADER_API UMainUICpp : public UUserWidget
{
	GENERATED_BODY()
protected:
	//初始化
	void NativeConstruct() override;

	////Update函数
	//UFUNCTION(BlueprintCallable)
	//void Update(float InDeltaTime);

private:
	// Image控件 相当于屏幕
	UImage* MainImage;
	// Image每帧绘制的纹理 会从软渲染器ScreenDevice中取出 FrameBuffer 填充到这个MainTexture
	UTexture2D* MainTexture;
	// 设备
	//ScreenDevice Device;
};
