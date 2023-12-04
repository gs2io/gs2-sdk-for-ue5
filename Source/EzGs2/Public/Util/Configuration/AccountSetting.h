#pragma once

namespace Gs2::UE5::Util
{
	class EZGS2_API FAccountSetting
	{
	public:
		FString AccountNamespaceName;
		FString KeyId;

		explicit FAccountSetting(
			const FString AccountNamespaceName = "default",
			const FString KeyId = "grn:gs2:{region}:{ownerId}:key:default:key:default"
		):
			AccountNamespaceName(AccountNamespaceName),
			KeyId(KeyId)
		{
			
		}
	};
    typedef TSharedPtr<FAccountSetting> FAccountSettingPtr;
}
