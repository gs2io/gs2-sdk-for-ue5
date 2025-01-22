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

#include "Exchange/Domain/Model/Gs2ExchangeEzAwaitGameSessionDomain.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    TOptional<FString> FEzAwaitGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzAwaitGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzAwaitGameSessionDomain::AwaitName() const
    {
        return Domain->AwaitName;
    }

    FEzAwaitGameSessionDomain::FEzAwaitGameSessionDomain(
        Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzAwaitGameSessionDomain::FAcquireTask::FAcquireTask(
        TSharedPtr<FEzAwaitGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAwaitGameSessionDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Acquire(
                    MakeShared<Gs2::Exchange::Request::FAcquireRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzAwaitGameSessionDomain::FAcquireTask>> FEzAwaitGameSessionDomain::Acquire(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(
            this->AsShared()
        );
    }

    FEzAwaitGameSessionDomain::FDeleteAwaitTask::FDeleteAwaitTask(
        TSharedPtr<FEzAwaitGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAwaitGameSessionDomain::FDeleteAwaitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Exchange::Request::FDeleteAwaitRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzAwaitGameSessionDomain::FDeleteAwaitTask>> FEzAwaitGameSessionDomain::DeleteAwait(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteAwaitTask>>(
            this->AsShared()
        );
    }

    FEzAwaitGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzAwaitGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAwaitGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwaitPtr> Result
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
                *Result = Gs2::UE5::Exchange::Model::FEzAwait::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzAwaitGameSessionDomain::FModelTask>> FEzAwaitGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzAwaitGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Exchange::Model::FEzAwaitPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Exchange::Model::FAwaitPtr Item)
            {
                Callback(Gs2::UE5::Exchange::Model::FEzAwait::FromModel(Item));
            }
        );
    }

    void FEzAwaitGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
