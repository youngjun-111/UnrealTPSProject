// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1.���̷�Ż�޽� �����͸� �ҷ�����ʹ�.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh
	(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		//2. Mesh ������Ʈ�� ��ġ�� �����ϰ� �ʹ�.
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	//3.TPS ī�޶� ���̰� �ʹ�.
	//3-1. SpringArm������Ʈ ���̱�
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringAtmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	//�ش� ��Ʈ�ѷ� �����̼��� Ʈ���
	springArmComp->bUsePawnControlRotation = true;
	//3-2. Camera������Ʈ�� ���δ�.

	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	//�ش� ��Ʈ�ѷ��� Yaw�� Ʈ��� ���� Yaw�� z�� ȸ�� Roll�� X�� ȸ�� Pich�� Y�� ȸ��
	tpsCamComp->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = true;
	JumpMaxCount = 2;

	// 4. �� ���̷�Ż�޽� ������Ʈ ���
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	// 4-1. �θ� ������Ʈ�� Mesh ������Ʈ�� ����
	gunMeshComp->SetupAttachment(GetMesh());
	// 4-2. ���̷�Ż�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	if(TempGunMesh.Succeeded())
	{
		//4-4 ���̷�Ż �޽� ������ �Ҵ�
		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);
		//4-5 ��ġ �����ϱ�
		gunMeshComp->SetRelativeLocation(FVector(-14, 52, 120));
	}
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsystem)
		{
			subsystem->AddMappingContext(imc_TPS, 0);
		}
	}
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerMove();
}

void ATPSPlayer::PlayerMove()
{
	//�÷��̾� �̵�ó��
	//��� �
	//P(��� ��ġ) = P0(���� ��ġ) + V(�ӵ�) X T(�ð�)
	//direction = FTransform(GetControlRotation()).TransformVector(direction);
	//FVector P0 = GetActorLocation();
	//FVector vt = direction * walkSpeed * DeltaTime;
	//FVector P = P0 + vt;
	//SetActorLocation(P);
	//�ش� ������ ���� ���ִ� �Լ��� ���������
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerInput)
	{
		PlayerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &ATPSPlayer::Turn);
		PlayerInput->BindAction(ia_LookUp, ETriggerEvent::Triggered, this, &ATPSPlayer::LookUp);
		PlayerInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &ATPSPlayer::Move);
		//������ ���ε� ��ų�� Ʈ�� �޽� �̱⶧���� Started�� ���ش�.
		PlayerInput->BindAction(ia_Jump, ETriggerEvent::Started, this, &ATPSPlayer::InputJump);
		//PlayerInput->BindAction(ia_Fire, ETriggerEvent::Started, this, &ATPSPlayer::Fire);
	}
}

void ATPSPlayer::Turn(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	AddControllerYawInput(value);
}

void ATPSPlayer::LookUp(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	AddControllerPitchInput(value);
}

void ATPSPlayer::Move(const FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();
	//���� �Է� �̺�Ʈ ó��
	direction.X = value.X;
	//�¿� �Է� �̺�Ʈ ó��
	direction.Y = value.Y;
}

void ATPSPlayer::InputJump(const FInputActionValue& inputValue)
{
	Jump();
}
//
//void ATPSPlayer::Fire(const FInputActionValue& inputValue)
//{
//
//}
