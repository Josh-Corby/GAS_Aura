

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	void DetermineDebuff(const FGameplayEffectSpec& Spec, const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters& EvalParams, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToCaptureDefs) const;
	
};
