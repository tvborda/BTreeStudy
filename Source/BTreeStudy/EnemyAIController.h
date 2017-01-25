// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BTREESTUDY_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	virtual void Possess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = AI)
	void CheckNearbyEnemy();

	UFUNCTION(BlueprintCallable, Category = AI)
	void UpdateNextTargetPoint();

	UFUNCTION(BlueprintCallable, Category = AI)
	EPathFollowingRequestResult::Type MoveToEnemy();

protected:
	UPROPERTY(BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTree;
	
	
	
};
