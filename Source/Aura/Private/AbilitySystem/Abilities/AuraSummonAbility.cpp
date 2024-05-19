

#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations() const
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnAngle / NumMinions;
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnAngle / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;

	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation + FVector(0.f, 0.f, -400.f), ECC_Visibility);
		if (HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}
