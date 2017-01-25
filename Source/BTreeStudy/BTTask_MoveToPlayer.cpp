// Fill out your copyright notice in the Description page of Project Settings.

#include "BTreeStudy.h"
//#include "BehaviorTree/BehaviorTree.h"
//#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "BehaviorTree/BlackboardComponent.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyAIController.h"
//#include "EnemyCharacter.h"
//#include "BTreeStudyCharacter.h"
#include "BTTask_MoveToPlayer.h"

UBTTask_MoveToPlayer::UBTTask_MoveToPlayer()
{
	NodeName = "MoveToPlayer";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	EPathFollowingRequestResult::Type MoveToActorResult = EnemyAIController->MoveToEnemy();
	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		NodeResult = EBTNodeResult::Succeeded;
	}
	return NodeResult;
}

void UBTTask_MoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyAIController* AIEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToEnemy();
	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

FString UBTTask_MoveToPlayer::GetStaticDescription() const
{
	return TEXT("Chase main player character");
}
