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

#include "Util/Authentication/Gs2GuildGuildAuthenticator.h"

#include "Account/Gs2AccountRestClient.h"
#include "Auth/Gs2AuthRestClient.h"
#include "Gateway/Gs2GatewayWebSocketClient.h"
#include "Guild/Gs2GuildRestClient.h"

namespace Gs2::UE5::Util
{
    FGs2GuildGuildAuthenticator::FGs2GuildGuildAuthenticator(
        const FGuildSettingPtr& GuildSetting,
        const FGatewaySettingPtr& GatewaySetting
    ):
        GuildSetting(GuildSetting),
        GatewaySetting(GatewaySetting == nullptr ? MakeShared<FGatewaySetting>() : GatewaySetting),
        NeedReAuthenticationValue(false)
    {
    }

    void FGs2GuildGuildAuthenticator::OnDisconnect()
    {
        NeedReAuthenticationValue = true;
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildGuildAuthenticator::Authentication(
        const Gs2::UE5::Util::FGs2ConnectionPtr Connection,
        const Gs2::UE5::Util::IGameSessionPtr UserGameSession,
        const FString GuildName,
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
        
        const auto GuildClient = MakeShared<Gs2::Guild::FGs2GuildRestClient>(Connection->RestSession());

        Guild::Result::FAssumeResultPtr _result;
        {
            const auto Future = GuildClient->Assume(
                MakeShared<Gs2::Guild::Request::FAssumeRequest>()
                    ->WithAccessToken(UserGameSession->AccessToken()->GetToken())
                    ->WithNamespaceName(GuildSetting->GuildNamespaceName)
                    ->WithGuildModelName(GuildSetting->GuildModelName)
                    ->WithGuildName(GuildName)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            _result = Future->GetTask().Result().ToSharedRef();
            Future->EnsureCompletion();
        }
        Gs2::Auth::Model::FAccessTokenPtr AccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>()
            ->WithToken(_result->GetToken())
            ->WithUserId(_result->GetUserId())
            ->WithFederationFromUserId(UserGameSession->AccessToken()->GetUserId())
            ->WithExpire(_result->GetExpire());
            //->WithTimeOffset(UserGameSession->AccessToken()->GetTimeOffset());
        
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
        
    bool FGs2GuildGuildAuthenticator::NeedReAuthentication()
    {
        return NeedReAuthenticationValue;
    }
}
