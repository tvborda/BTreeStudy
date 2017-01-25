// Fill out your copyright notice in the Description page of Project Settings.

#include "BTreeStudy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "PatrolTargetPoint.h"
#include "EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaivorTreeComp"));
}

void AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(InPawn);
	if (EnemyCharacter && EnemyCharacter->BehaviorTree)
	{
		Blackboard->InitializeBlackboard(*EnemyCharacter->BehaviorTree->BlackboardAsset);
		BehaviorTree->StartTree(*EnemyCharacter->BehaviorTree);
	}
}

void AEnemyAIController::CheckNearbyEnemy()
{
	APawn *Pawn = GetControlledPawn();
	FVector MultiSphereStart = Pawn->GetActorLocation();
	FVector MultiSphereEnd = MultiSphereStart + FVector(0, 0, 15.0f);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Pawn);
	TArray<FHitResult> OutHits;

	bool Result = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		MultiSphereStart,
		MultiSphereEnd,
		700,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true);

	Blackboard->SetValue<UBlackboardKeyType_Object>("TargetActorToFollow", NULL);

	if (Result == true)
	{
		for (int32 i = 0; i < OutHits.Num(); i++)
		{
			FHitResult Hit = OutHits[i];
			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (Hit.GetActor() == Character)
			{
				Blackboard->SetValue<UBlackboardKeyType_Object>("TargetActorToFollow", Character);
				GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, "Enemy Found!");
			}
		}
	}
}

void AEnemyAIController::UpdateNextTargetPoint()
{
	int32 TargetPointNumber = Blackboard->GetValue<UBlackboardKeyType_Int>("TargetPointNumber");

	if (TargetPointNumber >= 4)
	{
		TargetPointNumber = 0;
		Blackboard->SetValue<UBlackboardKeyType_Int>("TargetPointNumber", TargetPointNumber);
	}

	for (TActorIterator<APatrolTargetPoint> It(GetWorld()); It; ++It)
	{
		APatrolTargetPoint* TargetPoint = *It;
		if (TargetPointNumber == TargetPoint->Position)
		{
			Blackboard->SetValue<UBlackboardKeyType_Vector>("TargetPointPosition", TargetPoint->GetActorLocation());
			break;
		}
	}
	Blackboard->SetValue<UBlackboardKeyType_Int>("TargetPointNumber", (TargetPointNumber + 1));
}

EPathFollowingRequestResult::Type AEnemyAIController::MoveToEnemy()
{
	AActor* PlayerCharacterActor = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>("TargetActorToFollow"));
	EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(PlayerCharacterActor);
	return MoveToActorResult;
}
