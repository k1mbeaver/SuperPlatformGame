// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCamera.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"
#include "Capstone_TestCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomCamera::ACustomCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
}

// Called when the game starts or when spawned
void ACustomCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomCamera::UseCamera()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		FTimerHandle CameraSwitchTimerHandle;

		// Set a timer to switch back to the original camera
		float CameraSwitchDelay = 0.1f; // The duration after which the camera will switch back
		GetWorldTimerManager().SetTimer(CameraSwitchTimerHandle, [this, PlayerController]() {
			// Switch back to the original camera
			PlayerController->SetViewTargetWithBlend(this, 0.1f);
			}, CameraSwitchDelay, false);

		UWorld* World = GetWorld();

		if (World)
		{
			TArray<AActor*> FoundActors;

			FString PlayerTag = "Player";

			UGameplayStatics::GetAllActorsWithTag(World, FName(*PlayerTag), FoundActors);

			if (FoundActors.Num() > 0)
			{
				AActor* PlayerActor = FoundActors[0];
				GetPlayer = PlayerActor;

				if (ACapstone_TestCharacter* MyPlayerActor = Cast<ACapstone_TestCharacter>(PlayerActor))
				{
					float Duration = 2.0f; // Duration in seconds
					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PlayerController]()
						{
							PlayerController->SetViewTargetWithBlend(GetPlayer, 0.1f);
						}, Duration, false);
				}
			}
		}
	}
}

