#pragma once

namespace Gs2::UE5::Util
{
	class EZGS2_API FGatewaySetting
	{
	public:
		FString GatewayNamespaceName;
		bool AllowConcurrentAccess;

		explicit FGatewaySetting(
			const FString GatewayNamespaceName = "default",
			const bool AllowConcurrentAccess = true
		):
			GatewayNamespaceName(GatewayNamespaceName),
			AllowConcurrentAccess(AllowConcurrentAccess)
		{
			
		}
	};
    typedef TSharedPtr<FGatewaySetting> FGatewaySettingPtr;
}
