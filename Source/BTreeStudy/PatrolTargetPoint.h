// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "PatrolTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class BTREESTUDY_API APatrolTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	int32 Position;
	
	
};
