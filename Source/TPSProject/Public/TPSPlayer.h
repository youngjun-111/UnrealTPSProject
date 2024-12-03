// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputMappingContext* imc_TPS;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* ia_LookUp;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* ia_Turn;
	//�¿� ȸ�� �Է� ó��
	void Turn(const struct FInputActionValue& inputValue);
	//���� ȸ�� �Է� ó��
	void LookUp(const struct FInputActionValue& inputValue);

	//�̵� �Է� ó��
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* ia_Move;
	//�̵� �ӵ� ó��
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		float walkSpeed = 600;
	//�̵� ����
	FVector direction;
	//�̵� �Լ� ���� �Լ�
	void Move(const struct FInputActionValue& inputValue);
	//���� �̵� �Լ��� �ۼ�
	void PlayerMove();
	//���� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* ia_Jump;
	//���� �Լ� �𸮾󿡼� Jump�Լ��� �����ϱ⿡ �Լ����� InputJump�� �ۼ�
	void InputJump(const struct FInputActionValue& inputValue);

	////�߻� Ŭ����
	//UPROPERTY(EditDefaultsOnly, Category = "Input")
	//	class UInputAction* ia_Fire;
	////�߻� �Լ�
	//void Fire(const struct FInputActionValue& inputValue);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* tpsCamComp;
	//�� ���̷�Ż�޽� Ŭ����
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
		class USkeletalMeshComponent* gunMeshComp;
};
