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

#include "Gateway/Domain/Model/Gs2GatewayEzFirebaseTokenGameSessionDomain.h"

namespace Gs2::UE5::Gateway::Domain::Model
{

    TOptional<FString> FEzFirebaseTokenGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFirebaseTokenGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzFirebaseTokenGameSessionDomain::FEzFirebaseTokenGameSessionDomain(
        Gs2::Gateway::Domain::Model::FFirebaseTokenAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzFirebaseTokenGameSessionDomain::FSetFirebaseTokenTask::FSetFirebaseTokenTask(
        TSharedPtr<FEzFirebaseTokenGameSessionDomain> Self,
        FString Token,
        TOptional<FString> Locale
    ): Self(Self), Token(Token), Locale(Locale)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFirebaseTokenGameSessionDomain::FSetFirebaseTokenTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Gateway::Domain::Model::FEzFirebaseTokenGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Set(
                    MakeShared<Gs2::Gateway::Request::FSetFirebaseTokenRequest>()
                        ->WithToken(Token)
                        ->WithLocale(Locale)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Gateway::Domain::Model::FEzFirebaseTokenGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzFirebaseTokenGameSessionDomain::FSetFirebaseTokenTask>> FEzFirebaseTokenGameSessionDomain::SetFirebaseToken(
        FString Token,
        TOptional<FString> Locale
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSetFirebaseTokenTask>>(
            this->AsShared(),
            Token,
            Locale
        );
    }

    FEzFirebaseTokenGameSessionDomain::FDeleteFirebaseTokenTask::FDeleteFirebaseTokenTask(
        TSharedPtr<FEzFirebaseTokenGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFirebaseTokenGameSessionDomain::FDeleteFirebaseTokenTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Gateway::Domain::Model::FEzFirebaseTokenGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Gateway::Request::FDeleteFirebaseTokenRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Gateway::Domain::Model::FEzFirebaseTokenGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzFirebaseTokenGameSessionDomain::FDeleteFirebaseTokenTask>> FEzFirebaseTokenGameSessionDomain::DeleteFirebaseToken(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFirebaseTokenTask>>(
            this->AsShared()
        );
    }

    FEzFirebaseTokenGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFirebaseTokenGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFirebaseTokenGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Gateway::Model::FEzFirebaseTokenPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Gateway::Model::FEzFirebaseToken::FromModel(Task->GetTask().Result());
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzFirebaseTokenGameSessionDomain::FModelTask>> FEzFirebaseTokenGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzFirebaseTokenGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Gateway::Model::FEzFirebaseTokenPtr)> Callback)
    {
        return Domain->Subscribe(
            [Callback](Gs2::Gateway::Model::FFirebaseTokenPtr Item)
            {
                Callback(Gs2::UE5::Gateway::Model::FEzFirebaseToken::FromModel(Item));
            }
        );
    }

    void FEzFirebaseTokenGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
