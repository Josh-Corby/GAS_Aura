
#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(const int32& InXP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInformation stored in One-based indexing
		// LevelUpInformation[0] = null Level
		// LevelUpInformation[1] = Level 1 Information
		if (LevelUpInformation.Num() -1 <= Level) return Level;

		if (InXP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;

}
