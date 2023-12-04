/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "IAuthenticator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Configuration/AccountSetting.h"
#include "Util/Configuration/GatewaySetting.h"
#include "Util/Configuration/VersionSetting.h"

namespace Gs2::UE5::Util
{
    DECLARE_EVENT(FGs2AccountAuthenticator, FGs2DetectVersionUpEvent);
    
    class EZGS2_API FGs2AccountAuthenticator final : public IAuthenticator
    {
        FAccountSettingPtr AccountSetting;
        FGatewaySettingPtr GatewaySetting;
        FVersionSettingPtr VersionSetting;

        bool NeedReAuthenticationValue;

        FDelegateHandle OnDisconnectHandle;
        void OnDisconnect();
    public:
        FGs2DetectVersionUpEvent OnDetectVersionUp;
        
        explicit FGs2AccountAuthenticator(
            const FAccountSettingPtr& AccountSetting,
            const FGatewaySettingPtr& GatewaySetting = nullptr,
            const FVersionSettingPtr& VersionSetting = nullptr
        );
        virtual ~FGs2AccountAuthenticator() override = default;
        
        virtual Gs2::Core::Model::FGs2ErrorPtr Authentication(
            const Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            const FString UserId,
            const FString Password,
            const TSharedPtr<Gs2::UE5::Auth::Model::FEzAccessTokenPtr> Result
        ) override;

        virtual bool NeedReAuthentication() override;
    };
    typedef TSharedPtr<FGs2AccountAuthenticator> FGs2AccountAuthenticatorPtr;
}
