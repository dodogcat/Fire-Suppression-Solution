#include "BoxActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ABoxActor::ABoxActor()
{
	PrimaryActorTick.bCanEverTick = false;

    
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
    
}

void ABoxActor::SetColor(float Percent)
{
  
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), Percent);
        // DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), Percent);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("DynamicMaterial is NULL"));
    }
    /*
    float BlendValue = ParsedDataSum / (75.f);
    DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), BlendValue);
    */
}

// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
	Super::BeginPlay();
	
    UMaterialInterface* BoxMaterial = MeshComponent->GetMaterial(0);

    DynamicMaterial = UMaterialInstanceDynamic::Create(BoxMaterial, this);
    MeshComponent->SetMaterial(0, DynamicMaterial);
    if (DynamicMaterial)
    {
        MeshComponent->SetMaterial(0, DynamicMaterial);
    }
}

