// Fill out your copyright notice in the Description page of Project Settings.

#include "BTreeStudy.h"
#include "EnemyAIController.h"
#include "BTTask_UpdateNextTargetPoint.h"


UBTTask_UpdateNextTargetPoint::UBTTask_UpdateNextTargetPoint()
{
	NodeName = "UpdateNextTargetPoint";
}

EBTNodeResult::Type UBTTask_UpdateNextTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyAIController->UpdateNextTargetPoint();
	return EBTNodeResult::Succeeded;
}

FString UBTTask_UpdateNextTargetPoint::GetStaticDescription() const
{
	return TEXT("Update next target point for patrol");
}
