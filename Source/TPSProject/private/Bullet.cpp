// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1. �浹ü ���
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollComp"));
	//2. �浹�������� ����
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	//3. �浹ü ũ�� ����
	collisionComp->SetSphereRadius(13);
	//4. ��Ʈ�� ���
	RootComponent = collisionComp;
	//5. �ܰ� ������Ʈ ���
	bodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	//6. �θ� ������Ʈ ����
	bodyComp->SetupAttachment(collisionComp);
	//7. �浹 ��Ȱ��ȭ
	bodyComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//8. �ܰ� ũ�� ����
	bodyComp->SetRelativeScale3D(FVector(0.25f));
	//�߻�ü ������Ʈ
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	//movemonet ������Ʈ�� ���Ž�ų ������Ʈ ����
	movementComp->SetUpdatedComponent(collisionComp);
	//�ӵ��� �ѹ��� ó���ϱ����� ����� �ۼ����� ���̴�. 
	
 
	//�ʱ�ӵ�
	//movementComp->InitialSpeed = 5000;
	//�ִ�ӵ�
	//movementComp->MaxSpeed = 5000;
	//�ݵ� ����
	movementComp->bShouldBounce = true;
	//�ݵ� ��
	movementComp->Bounciness = 0.3f;

	//�ν��Ͻ� ���� 1
	//���� �ð� �ֱ�
	//InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	//Die�Լ��� �����Ͽ� 2�ʵڿ� �����ǰԲ� �ϴ� �Լ��� ������ ���� �ִ�.
	FTimerHandle deathTimer;
	//�ν��Ͻ� ���� 2
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);
	//�ν��Ͻ� ���� 3.
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void
		{
			Destroy();
		}), 2.0f, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == TEXT("speed"))
	{
		movementComp->InitialSpeed = speed;
		movementComp->MaxSpeed = speed;
	}
}

//�ν��Ͻ� ���� 2(h���Ͽ� �Լ� ���� �������)
//void ABullet::Die()
//{
//	Destroy();
//}
