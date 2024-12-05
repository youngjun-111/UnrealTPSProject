// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	//플레이어 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float speed = 0;

	//매프레임 갱신되는 함수 오버라이딩 
	//오버라이딩은 cpp에서 반드시 구현 해줘야 함 그래야 빌드가 가능해짐.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
