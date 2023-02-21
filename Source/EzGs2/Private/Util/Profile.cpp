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

#include "Util/Profile.h"

#include "Core/Gs2Domain.h"
#include "Core/Model/BasicGs2Credential.h"
#include "Core/Net/Rest/Task/RestCloseTask.h"
#include "Core/Net/Rest/Task/RestOpenTask.h"
#include "Core/Net/Rest/Task/RestReOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketCloseTask.h"
#include "Core/Net/WebSocket/Task/WebSocketOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketReOpenTask.h"

namespace Gs2::UE5::Util
{
    FProfile::FProfile(
        const FString ClientId,
        const FString ClientSecret,
        const Gs2::Core::Model::ERegion Region,
        const IReOpenerPtr ReOpener,
        const TOptional<FString> DistributorNamespaceName
    ):
        ClientId(ClientId),
        ClientSecret(ClientSecret),
        Region(Region),
        ReOpener(ReOpener),
        Gs2RestSession(nullptr),
        Gs2WebSocketSession(nullptr),
        DistributorNamespaceName(DistributorNamespaceName)
    {
    }

    FProfile::FInitializeTask::FInitializeTask(
        const TSharedPtr<FProfile> Self
    ): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProfile::FInitializeTask::Action(
        const TSharedPtr<TSharedPtr<Core::Domain::FGs2Domain>> Result
    )
    {
        auto Credential = MakeShared<Gs2::Core::Model::FBasicGs2Credential>(
            Self->ClientId,
            Self->ClientSecret
            );
        Self->Gs2RestSession = MakeShared<Gs2::Core::Net::Rest::FGs2RestSession>(
            Credential,
            Self->Region
            );
        Self->Gs2WebSocketSession = MakeShared<Gs2::Core::Net::WebSocket::FGs2WebSocketSession>(
            Credential,
            Self->Region
        );
        
        if (const auto Error = Self->ReOpener->ReOpen(
            Self->Gs2RestSession,
            Self->Gs2WebSocketSession
        ); Error.IsValid())
        {
            return Error;
        }
        
        *Result = MakeShared<Core::Domain::FGs2Domain>(
            Self
        );
        
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProfile::FInitializeTask>> FProfile::Initialize()
    {
        return Gs2::Core::Util::New<FAsyncTask<FInitializeTask>>(this->AsShared());
    }

    FProfile::FReConnectTask::FReConnectTask(
        const TSharedPtr<FProfile> Self
    ): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProfile::FReConnectTask::Action(TSharedPtr<TSharedPtr<void>> Result)
    {
        if (const auto Error = Self->ReOpener->ReOpen(
            Self->Gs2RestSession,
            Self->Gs2WebSocketSession
        ); Error.IsValid())
        {
            return Error;
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProfile::FReConnectTask>> FProfile::ReConnect()
    {
        return Gs2::Core::Util::New<FAsyncTask<FReConnectTask>>(this->AsShared());
    }

    FProfile::FLoginTask::FLoginTask(
        const TSharedPtr<FProfile> Self,
        const FString UserId,
        const FString Password
    ):
        Self(Self),
        UserId(UserId),
        Password(Password)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProfile::FLoginTask::Action(
        const TSharedPtr<TSharedPtr<Auth::Model::FEzAccessToken>> Result
    )
    {
        const auto AccessToken = MakeShared<Auth::Model::FEzAccessToken>();
        Self->ReOpener->SetAuthenticator(
            Self->AuthenticatorValue,
            UserId,
            Password,
            AccessToken
        );
        const auto Error = Self->ReOpener->ReOpen(
            Self->Gs2RestSession,
            Self->Gs2WebSocketSession
        );
        if (Error.IsValid())
        {
            return Error;
        }
        *Result = AccessToken;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProfile::FLoginTask>> FProfile::Login(
        const IAuthenticatorPtr Authenticator,
        const FString UserId,
        const FString Password
    )
    {
        AuthenticatorValue = Authenticator;
        UserIdValue = UserId;
        PasswordValue = Password;
        return Gs2::Core::Util::New<FAsyncTask<FProfile::FLoginTask>>(this->AsShared(), UserId, Password);
    }

    FProfile::FFinalizeTask::FFinalizeTask(
        const TSharedPtr<FProfile> Self
    ): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProfile::FFinalizeTask::Action(
        const TSharedPtr<TSharedPtr<void>> Result
    )
    {
        if (Self->Gs2RestSession != nullptr) {
            const auto Future = Self->Gs2RestSession->Close();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();

            Self->Gs2RestSession = nullptr;
        }
        if (Self->Gs2WebSocketSession != nullptr) {
            const auto Future = Self->Gs2WebSocketSession->Close();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();

            Self->Gs2WebSocketSession = nullptr;
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProfile::FFinalizeTask>> FProfile::Finalize()
    {
        return Gs2::Core::Util::New<FAsyncTask<FFinalizeTask>>(this->AsShared());
    }

}
