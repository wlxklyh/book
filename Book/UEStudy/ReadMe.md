# UE

## 一、相机
大致流程是APlayerCameraManager 去UpdateViewTarget 然后AActor::CalcCamera UCameraComponent::GetCameraView 
而SpringArmComponent下面挂载了UCameraComponent 通过SpringArmComponent去调节UCameraComponet