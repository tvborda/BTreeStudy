// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateNextTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class BTREESTUDY_API UBTTask_UpdateNextTargetPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_UpdateNextTargetPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	
	
};
