#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxActor.generated.h"

UCLASS()
class BOXVOLUME_API ABoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoxActor();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UMaterialInstanceDynamic* DynamicMaterial;

	UFUNCTION(BlueprintCallable, Category = "Color")
	void SetColor(float Percent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
