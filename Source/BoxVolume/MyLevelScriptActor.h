#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class BOXVOLUME_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AMyLevelScriptActor();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Setup")
	TSubclassOf<class ABoxActor> BPBoxClass;
	TArray<ABoxActor*> SpawnedActors;

	int32 NumBoxesX, NumBoxesY, NumBoxesZ;


	void ParseTXTFile();
	int32 MAXValue;
	TArray<int32> IntValues;

	void ChangeCubeColor();
	
};
