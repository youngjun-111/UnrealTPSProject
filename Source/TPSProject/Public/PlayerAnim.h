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
	//�÷��̾� �յ� �̵� �ӵ� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float speed = 0;
	//�÷��̾� �¿� �̵� �ӵ� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float direction = 0;

	//�������� ���ŵǴ� �Լ� �������̵� 
	//�������̵��� cpp���� �ݵ�� ���� ����� �� �׷��� ���尡 ��������.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//�÷��̾ ���߿� �ִ��� ���� �Ǵ� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		bool isInAir = false;

	//����� ���� ���ϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
		class UAnimMontage* attackAnimMontage;

	//���� �ִϸ��̼� ��� �Լ�
	void PlayAttackAnim();
};
