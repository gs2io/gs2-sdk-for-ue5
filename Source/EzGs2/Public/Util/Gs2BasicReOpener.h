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
#include "IReOpener.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Version/Domain/Model/Gs2VersionEzAcceptVersionDomain.h"
#include "Version/Model/Status.h"
#include "Version/Model/TargetVersion.h"

namespace Gs2::UE5::Util
{
    class EZGS2_API FGatewaySetting
    {
    public:
        FString GatewayNamespaceName;
        bool AllowConcurrentAccess;
        
        FGatewaySetting(
            const FString GatewayNamespaceName,
            const bool AllowConcurrentAccess
        ):
            GatewayNamespaceName(GatewayNamespaceName),
            AllowConcurrentAccess(AllowConcurrentAccess)
        {
        }
        
        FGatewaySetting(
            const FGatewaySetting& From
        ):
            GatewayNamespaceName(From.GatewayNamespaceName),
            AllowConcurrentAccess(From.AllowConcurrentAccess)
        {
        }
    };
    typedef TSharedPtr<FGatewaySetting> FGatewaySettingPtr;
    
    class EZGS2_API FVersionSetting
    {
    public:
        FString VersionNamespaceName;
        TArray<Version::Model::FEzTargetVersionPtr> TargetVersions;
        
        FVersionSetting(
            const FString VersionNamespaceName,
            const TArray<Version::Model::FEzTargetVersionPtr> TargetVersions
        ):
            VersionNamespaceName(VersionNamespaceName),
            TargetVersions(TargetVersions)
        {
        }
        
        FVersionSetting(
            const FVersionSetting& From
        ):
            VersionNamespaceName(From.VersionNamespaceName),
            TargetVersions(From.TargetVersions)
        {
        }
    };
    typedef TSharedPtr<FVersionSetting> FVersionSettingPtr;
    
    DECLARE_DELEGATE_OneParam(FDetectVersionUpDelegate, TSharedPtr<TArray<Gs2::Version::Model::FStatusPtr>>);
    
    class EZGS2_API FGs2BasicReOpener final : public IReOpener
    {
        FGatewaySettingPtr GatewaySetting;
        FVersionSettingPtr VersionSetting;
        
        IAuthenticatorPtr AuthenticatorValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PasswordValue;
        Auth::Model::FEzAccessTokenPtr AccessTokenValue;

        FDetectVersionUpDelegate DetectVersionUpDelegate;

    public:
        explicit FGs2BasicReOpener(
            const FGatewaySettingPtr GatewaySetting = nullptr,
            const FVersionSettingPtr VersionSetting = nullptr
            );
        FGs2BasicReOpener(
            const FGs2BasicReOpener& From
        );
        virtual ~FGs2BasicReOpener() override = default;
        
        FDetectVersionUpDelegate& OnDetectVersionUp()
        {
            return this->DetectVersionUpDelegate;
        }

        virtual void SetAuthenticator(
            const IAuthenticatorPtr Authenticator,
            const FString UserId,
            const FString Password,
            Auth::Model::FEzAccessTokenPtr AccessToken
        ) override;

        virtual Gs2::Core::Model::FGs2ErrorPtr ReOpen(
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
            const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession
        ) override;
    };
}
