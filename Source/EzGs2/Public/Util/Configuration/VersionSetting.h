#pragma once
#include "Version/Model/Gs2VersionEzTargetVersion.h"

namespace Gs2::UE5::Util
{
	class EZGS2_API FVersionSetting
	{
	public:
		FString VersionNamespaceName;
		TArray<Version::Model::FEzTargetVersionPtr> TargetVersions;

		explicit FVersionSetting(
			const FString VersionNamespaceName,
			const TArray<Version::Model::FEzTargetVersionPtr> TargetVersions
		):
			VersionNamespaceName(VersionNamespaceName),
			TargetVersions(TargetVersions)
		{
			
		}
	};
    typedef TSharedPtr<FVersionSetting> FVersionSettingPtr;
}
