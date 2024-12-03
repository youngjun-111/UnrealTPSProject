// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TPSPROJECT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�߻�ü �̵� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category=Movement)
		class UProjectileMovementComponent* movementComp;
	UPROPERTY(VisibleAnywhere, Category=Collision)
		class USphereComponent* collisionComp;
	UPROPERTY(VisibleAnywhere, Category=BodyMesh)
		class UStaticMeshComponent* bodyComp;
	//�Ѿ˼ӵ��� ó�����ֱ����� ����
	UPROPERTY(EditAnywhere, Category = Settings)
		float speed = 5000;

	//������ Ư�� �Ӽ��� �����ϸ� ȣ��Ǵ� �̺�Ʈ �Լ�
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	//�ν��Ͻ� ���� 2
	//�Ѿ� ���� �Լ� ����
	//void Die();
};
