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

#include "Util/Authentication/Gs2AccountAuthenticator.h"

#include "Account/Gs2AccountRestClient.h"
#include "Auth/Gs2AuthRestClient.h"
#include "Gateway/Gs2GatewayWebSocketClient.h"
#include "Version/Gs2VersionRestClient.h"

namespace Gs2::UE5::Util
{
    FGs2AccountAuthenticator::FGs2AccountAuthenticator(
        const FAccountSettingPtr& AccountSetting,
        const FGatewaySettingPtr& GatewaySetting,
        const FVersionSettingPtr& VersionSetting
    ):
        AccountSetting(AccountSetting),
        GatewaySetting(GatewaySetting == nullptr ? MakeShared<FGatewaySetting>() : GatewaySetting),
        VersionSetting(VersionSetting),
        NeedReAuthenticationValue(false)
    {
    }

    void FGs2AccountAuthenticator::OnDisconnect()
    {
        NeedReAuthenticationValue = true;
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2AccountAuthenticator::Authentication(
        const Gs2::UE5::Util::FGs2ConnectionPtr Connection,
        const FString UserId,
        const FString Password,
        const TSharedPtr<Gs2::Auth::Model::FAccessTokenPtr> Result
    )
    {
        if (Connection->IsDisconnected())
        {
            auto Future = Connection->Connect();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
        }
        
        const auto AccountClient = MakeShared<Gs2::Account::FGs2AccountRestClient>(Connection->RestSession());
        const auto AuthClient = MakeShared<Gs2::Auth::FGs2AuthRestClient>(Connection->RestSession());
        Account::Result::FAuthenticationResultPtr AuthenticationResult;
        {
            const auto Future = AccountClient->Authentication(
                MakeShared<Gs2::Account::Request::FAuthenticationRequest>()
                    ->WithNamespaceName(AccountSetting->AccountNamespaceName)
                    ->WithKeyId(AccountSetting->KeyId)
                    ->WithUserId(UserId)
                    ->WithPassword(Password)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            AuthenticationResult = Future->GetTask().Result().ToSharedRef();
            Future->EnsureCompletion();
        }
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken;
        {
            const auto Future = AuthClient->LoginBySignature(
                MakeShared<Gs2::Auth::Request::FLoginBySignatureRequest>()
                    ->WithBody(AuthenticationResult->GetBody())
                    ->WithSignature(AuthenticationResult->GetSignature())
                    ->WithKeyId(AccountSetting->KeyId)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            AccessToken = MakeShared<Gs2::UE5::Auth::Model::FEzAccessToken>()
                ->WithToken(Future->GetTask().Result()->GetToken())
                ->WithExpire(Future->GetTask().Result()->GetExpire())
                ->WithUserId(Future->GetTask().Result()->GetUserId());
            Future->EnsureCompletion();
        }
        if (GatewaySetting.IsValid() && AccessToken.IsValid())
        {
            const auto GatewayClient = MakeShared<Gs2::Gateway::FGs2GatewayWebSocketClient>(Connection->WebSocketSession());
            auto Future = GatewayClient->SetUserId(
                MakeShared<Gs2::Gateway::Request::FSetUserIdRequest>()
                    ->WithNamespaceName(GatewaySetting->GatewayNamespaceName)
                    ->WithAccessToken(AccessToken->GetToken())
                    ->WithAllowConcurrentAccess(GatewaySetting->AllowConcurrentAccess)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error().IsValid() && !Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
                {
                    Future->EnsureCompletion();
                    return Future->GetTask().Error();
                }
            }
            Future->EnsureCompletion();

            NeedReAuthenticationValue = false;
            if (!Future->GetTask().IsError())
            {
                if (OnDisconnectHandle.IsValid())
                {
                    Connection->WebSocketSession()->OnDisconnect().Remove(OnDisconnectHandle);
                }
                OnDisconnectHandle = Connection->WebSocketSession()->OnDisconnect().AddLambda([this]
                {
                    OnDisconnect();
                });
            }
        }
        if (VersionSetting.IsValid() && AccessToken.IsValid() && !VersionSetting->VersionNamespaceName.IsEmpty())
        {
            const auto VersionClient = MakeShared<Gs2::Version::FGs2VersionRestClient>(Connection->RestSession());
            auto Future = VersionClient->CheckVersion(
                MakeShared<Gs2::Version::Request::FCheckVersionRequest>()
                    ->WithNamespaceName(VersionSetting->VersionNamespaceName)
                    ->WithAccessToken(AccessToken->GetToken())
                    ->WithTargetVersions([this]
                    {
                        auto Items = MakeShared<TArray<Gs2::Version::Model::FTargetVersionPtr>>();
                        for (auto Item : VersionSetting->TargetVersions)
                        {
                            Items->Add(Item->ToModel());
                        }
                        return Items;
                    }())
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            if (!Future->GetTask().Result()->GetProjectToken().IsSet())
            {
                Connection->RestSession()->Credential()->UpdateProjectToken(*Future->GetTask().Result()->GetProjectToken());
                Connection->WebSocketSession()->Credential()->UpdateProjectToken(*Future->GetTask().Result()->GetProjectToken());
            }
            if (Future->GetTask().Result()->GetErrors()->Num() > 0)
            {
                OnDetectVersionUp.Broadcast();

                return MakeShared<Gs2::Core::Model::FUnauthorizedError>(
                    []
                    {
                        auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Details->Add(
                            MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
                                "version",
                                "version.version.check.error.failed",
                                ""
                            )
                        );
                        return Details;
                    }()
                );
            }
            Future->EnsureCompletion();
        }
        
        if (!Result->IsValid())
        {
            *Result = MakeShared<Gs2::Auth::Model::FAccessToken>();
        }
        (*Result)
            ->WithToken(AccessToken->GetToken())
            ->WithExpire(AccessToken->GetExpire())
            ->WithUserId(AccessToken->GetUserId());
        
        return nullptr;
    }
        
    bool FGs2AccountAuthenticator::NeedReAuthentication()
    {
        return NeedReAuthenticationValue;
    }
}
