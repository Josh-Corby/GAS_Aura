#include "Checkpoint/Checkpoint.h"

#include "Interaction/PlayerInterface.h"
#include "Components/SphereComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ACheckpoint::ACheckpoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointMesh");
	CheckpointMesh->SetupAttachment(GetRootComponent());
	CheckpointMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Block);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(CheckpointMesh);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CheckpointMesh->SetCustomDepthStencilValue(CustomDepthStencilOverride);
	CheckpointMesh->MarkRenderStateDirty();

	MoveToComponent = CreateDefaultSubobject<USceneComponent>("MoveToComponent");
	MoveToComponent->SetupAttachment(GetRootComponent());
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	if (bBindOverlapCallback)
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnSphereOverlap);
	}
}

void ACheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;

		if (AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			AuraGM->SaveWorldState(GetWorld());
		}

		IPlayerInterface::Execute_SaveProgress(OtherActor, PlayerStartTag);
		HandleGlowEffects();
	}
}

void ACheckpoint::HandleGlowEffects()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(CheckpointMesh->GetMaterial(0), this);
	CheckpointMesh->SetMaterial(0, DynamicMaterialInstance);
	CheckpointReached(DynamicMaterialInstance);
}

void ACheckpoint::LoadActor_Implementation()
{
	if (bReached)
	{
		HandleGlowEffects();
	}
}

void ACheckpoint::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	OutDestination = MoveToComponent->GetComponentLocation();
}

void ACheckpoint::HighlightActor_Implementation()
{
	if (!bReached)
	{
		CheckpointMesh->SetRenderCustomDepth(true);
	}
}

void ACheckpoint::UnHighlightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(false);
}
