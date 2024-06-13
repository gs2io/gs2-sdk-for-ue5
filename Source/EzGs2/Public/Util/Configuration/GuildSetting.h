#pragma once

namespace Gs2::UE5::Util
{
	class EZGS2_API FGuildSetting
	{
	public:
		FString GuildNamespaceName;
		FString GuildModelName;

		explicit FGuildSetting(
			const FString GuildNamespaceName,
			const FString GuildModelName
		):
			GuildNamespaceName(GuildNamespaceName),
			GuildModelName(GuildModelName)
		{
			
		}
	};
    typedef TSharedPtr<FGuildSetting> FGuildSettingPtr;
}
