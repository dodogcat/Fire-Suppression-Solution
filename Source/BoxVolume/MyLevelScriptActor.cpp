// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScriptActor.h"
#include "BoxActor.h"
#include "UObject/ConstructorHelpers.h"

#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"


AMyLevelScriptActor::AMyLevelScriptActor()
{
	// Find the Blueprint class
	static ConstructorHelpers::FObjectFinder<UClass> BoxActorBP(TEXT("/Game/Blueprints/BP_BoxActor.BP_BoxActor_C"));
	if (BoxActorBP.Succeeded())
	{
		BPBoxClass = BoxActorBP.Object;
		UE_LOG(LogTemp, Log, TEXT("BP_BoxActor Found Success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("BP_BoxActor Found Failed"));
	}
}

void AMyLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	int32 CellSize = 20;
	int32 HalfCellSize = CellSize / 2;
	NumBoxesX = 61; 
	NumBoxesY = 31;
	NumBoxesZ = 31;

	float DistanceBetweenBoxes = 150.0f; 

	if (BPBoxClass)
	{
		for (int32 z = 0; z < NumBoxesZ; ++z)
		{
			for (int32 y = 0; y < NumBoxesY; ++y)
			{
				for (int32 x = 0; x < NumBoxesX; ++x)
				{
					FVector BoxLocation = FVector(x * CellSize, y * CellSize, HalfCellSize + z*CellSize);
					AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BPBoxClass, BoxLocation, FRotator::ZeroRotator);

					if (SpawnedActor)
					{
						SpawnedActors.Add(Cast<ABoxActor>(SpawnedActor));
					}
				}
			}
		}
	}

	MAXValue = 0;

	ParseTXTFile();
	ChangeCubeColor();
}

void AMyLevelScriptActor::ParseTXTFile()
{
	FString FileContent;
	FString FilePath = FPaths::ProjectContentDir() + TEXT("FDS/TEMPERATURE/150.txt");
	FFileHelper::LoadFileToString(FileContent, *FilePath);
	

	TArray<FString> Tokens;
	FileContent.ParseIntoArray(Tokens, TEXT("\n"), true);
	FileContent.ParseIntoArray(Tokens, TEXT(" "), true);
	


	IntValues.Empty();
	for (FString Token : Tokens)
	{
		if (Token.Len() > 0)
		{
			int32 ParsedValue = FCString::Atoi(*Token);
			IntValues.Add(ParsedValue);

			MAXValue = FMath::Max(MAXValue, ParsedValue);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("MAXValue : %d"), MAXValue);
	UE_LOG(LogTemp, Log, TEXT("IntValues Count : %d"), IntValues.Num());
}

void AMyLevelScriptActor::ChangeCubeColor()
{
	UE_LOG(LogTemp, Log, TEXT("SpawnedActors Num : %d"), SpawnedActors.Num());
	/*
	float Percent = 1.0f * IntValues[0] / MAXValue;
	SpawnedActors[0]->SetColor(Percent);
	*/
	
	int32 current = 0;
	for (int32 z = 0; z < NumBoxesZ; ++z)
	{
		for (int32 y = 0; y < NumBoxesY; ++y)
		{
			for (int32 x = 0; x < NumBoxesX; ++x)
			{
				int32 index = z * NumBoxesX * NumBoxesY + x * NumBoxesY + y;
				ABoxActor* CubeActor = SpawnedActors[current];
				float Percent = 1.0f * IntValues[current] / MAXValue;


				CubeActor->SetColor(Percent);
				current++;
			}
		}
	}

	/*
	for (int32 i = 0; i < SpawnedActors.Num(); ++i)
	{
		ABoxActor* CubeActor = SpawnedActors[i];
		float Percent = 1.0f * IntValues[i] / MAXValue;

		
		CubeActor->SetColor(Percent);
	}
	*/
	
	
}
