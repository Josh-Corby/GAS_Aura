
#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"


FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& InAbilityTag, bool bLogNotFound) const
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbiltyTag.MatchesTagExact(InAbilityTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for AbilityTad [%s] on AbilityInfo [%s]"), *InAbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAbilityInfo();
}
