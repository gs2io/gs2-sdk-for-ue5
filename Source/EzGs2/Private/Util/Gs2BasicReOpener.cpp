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

#include "Util/Gs2BasicReOpener.h"

#include "Core/Net/Rest/Task/RestReOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketReOpenTask.h"
#include "Gateway/Gs2GatewayRestClient.h"
#include "Gateway/Gs2GatewayWebSocketClient.h"
#include "Version/Gs2VersionRestClient.h"

namespace Gs2::UE5::Util
{
    FGs2BasicReOpener::FGs2BasicReOpener(
        const FGatewaySettingPtr GatewaySetting,
        const FVersionSettingPtr VersionSetting
    ):
        GatewaySetting(GatewaySetting),
        VersionSetting(VersionSetting)
    {
    }

    FGs2BasicReOpener::FGs2BasicReOpener(
        const FGs2BasicReOpener& From
    ):
        GatewaySetting(From.GatewaySetting),
        VersionSetting(From.VersionSetting),
        AuthenticatorValue(From.AuthenticatorValue),
        UserIdValue(From.UserIdValue),
        PasswordValue(From.PasswordValue),
        AccessTokenValue(From.AccessTokenValue),
        DetectVersionUpDelegate(From.DetectVersionUpDelegate)
    {
    }

    void FGs2BasicReOpener::SetAuthenticator(
        const IAuthenticatorPtr Authenticator,
        const FString UserId,
        const FString Password,
        Auth::Model::FEzAccessTokenPtr AccessToken
    )
    {
        this->AuthenticatorValue = Authenticator;
        this->UserIdValue = UserId;
        this->PasswordValue = Password;
        this->AccessTokenValue = AccessToken;
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2BasicReOpener::ReOpen(
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
        const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession
    )
    {
        {
            const auto Future = RestSession->ReOpen();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
        }
        {
            const auto Future = WebSocketSession->ReOpen();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
        }
        if (AuthenticatorValue != nullptr && UserIdValue.IsSet() && PasswordValue.IsSet())
        {
            const auto AuthenticationResult = MakeShared<Auth::Model::FEzAccessTokenPtr>();
            if (const auto Error = AuthenticatorValue->Authentication(
                RestSession,
                *UserIdValue,
                *PasswordValue,
                AuthenticationResult
            ); Error.IsValid())
            {
                return Error;
            }
            AccessTokenValue
                ->WithToken((*AuthenticationResult)->GetToken())
                ->WithUserId((*AuthenticationResult)->GetUserId())
                ->WithExpire((*AuthenticationResult)->GetExpire());
        }
        if (GatewaySetting != nullptr && AccessTokenValue != nullptr)
        {
            {
                const auto GatewayClient = Gateway::FGs2GatewayWebSocketClient(WebSocketSession);
                const auto Future = GatewayClient.SetUserId(
                    MakeShared<Gateway::Request::FSetUserIdRequest>()
                        ->WithNamespaceName(GatewaySetting->GatewayNamespaceName)
                        ->WithAccessToken(AccessTokenValue->GetToken())
                        ->WithAllowConcurrentAccess(GatewaySetting->AllowConcurrentAccess)
                );
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    return Future->GetTask().Error();
                }
            }
        }
        if (VersionSetting != nullptr && AccessTokenValue != nullptr)
        {
            {
                const auto VersionClient = Gs2::Version::FGs2VersionRestClient(RestSession);
                const auto Future = VersionClient.CheckVersion(
                    MakeShared<Gs2::Version::Request::FCheckVersionRequest>()
                        ->WithNamespaceName(VersionSetting->VersionNamespaceName)
                        ->WithTargetVersions([&]
                        {
                            const auto Values = MakeShared<TArray<Gs2::Version::Model::FTargetVersionPtr>>();
                            for (auto Value : VersionSetting->TargetVersions)
                            {
                                Values->Add(Value->ToModel());
                            }
                            return Values;
                        }())
                        ->WithAccessToken(AccessTokenValue->GetToken())
                );
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    return Future->GetTask().Error();
                }
                const auto ProjectToken = Future->GetTask().Result()->GetProjectToken();
                if (ProjectToken.IsSet())
                {
                    RestSession->Credential()->UpdateProjectToken(*ProjectToken);
                    WebSocketSession->Credential()->UpdateProjectToken(*ProjectToken);
                }
                if (Future->GetTask().Result()->GetErrors() != nullptr && Future->GetTask().Result()->GetErrors()->Num() > 0)
                {
                    DetectVersionUpDelegate.Execute(
                        Future->GetTask().Result()->GetErrors()
                    );
                    
                    auto Detail = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Detail->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
                        "version",
                        "version.version.check.error.failed",
                        ""
                    ));
                    return MakeShared<Gs2::Core::Model::FUnauthorizedError>(
                        Detail
                    );
                }
            }
        }
        return nullptr;
    }
}
