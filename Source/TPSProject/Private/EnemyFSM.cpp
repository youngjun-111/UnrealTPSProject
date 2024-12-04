// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "TPSPlayer.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include "TPSProject.h"
#include <Components/CapsuleComponent.h>

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	//���忡�� ATPSPlayer Ÿ�� ã�ƿ���
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
	//ATPSPlayer Ÿ������ ĳ����
	target = Cast<ATPSPlayer>(actor);
	//���� ��ü ��������
	me = Cast<AEnemy>(GetOwner());
}

// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	default:
		break;
	}

	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, logMsg);
}

//���̵�
void UEnemyFSM::IdleState()
{
	//1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. ���� ��� �ð��� ��� ����� �ʰ��ߴٸ�
	if (currentTime > idleDelayTime)
	{
		//3. �̵� ���·� ��ȯ
		mState = EEnemyState::Move;
		//��� �ð� �ʱ�ȭ
		currentTime = 0;
	}
}

//�̵�
void UEnemyFSM::MoveState()
{
	//1. Ÿ�� �������� �Ҵ�
	FVector destination = target->GetActorLocation();
	//2. ������ �ʿ�
	FVector dir = destination - me->GetActorLocation();
	//3. ���� �������� �̵��ϰ� �ʹ�.
	me->AddMovementInput(dir.GetSafeNormal());
	//Ÿ��� ��������� ���� ���·� ����
	if (dir.Size() < attackRange)
	{
		mState = EEnemyState::Attack;
	}
}

//����
void UEnemyFSM::AttackState()
{
	//��ǥ: ���� �ð��� �� ���� �����ϰ� �Ѵ�.
	//1. �ð��� �귯�� �Ѵ�.
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. ���� �ð��� �����ϱ�
	if (currentTime > attackDelayTime)
	{
		//3. �����ϰ� �ʹ�.
		PRINT_LOG(TEXT("Attack!!"));
		//��� �ð� �ʱ�ȭ
		currentTime = 0;
	}

	//1. Ÿ����� �Ÿ��� �ʿ�
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	//2. Ÿ����� �Ÿ��� ���� ������ ������ϱ�
	if (distance > attackRange)
	{
		//3. ���¸� �̵����� ��ȯ
		mState = EEnemyState::Move;
	}

}

//�ǰ�
void UEnemyFSM::DamageState()
{
	//1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. ��� �ð��� ��� �ð��� �ʰ� �ߴٸ�
	if (currentTime > damageDelayTime)
	{
		//3. ���¸� ���̵�� ����
		mState = EEnemyState::Idle;
		//��� �ð� �ʱ�ȭ
		currentTime = 0;
	}
}

void UEnemyFSM::OnDamageProcess()
{
	//ü�� ����
	hp--;
	//ü���� �����ִٸ�
	if (hp > 0)
	{
		//�ǰݻ��·� ��ȯ
		mState = EEnemyState::Damage;
	}
	//ü���� ���ٸ�
	else
	{
		//���� ���·� ����
		mState = EEnemyState::Die;
		//ĸ�� �浹ü ��Ȱ��ȭ
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

//����
void UEnemyFSM::DieState()
{
	//��� �Ʒ��� �������� �ʹ�..
	//��ӿ ���� P=P0+vt
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaRealTimeSeconds;
	FVector p = P0 + vt;
	me->SetActorLocation(p);

	if (p.Z < -200.0f)
	{
		me->Destroy();
	}
}