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

    TOptional<int64> FEzAwaitGameSessionDomain::UnlockAt() const
    {
        return Domain->UnlockAt;
    }

    TOptional<FString> FEzAwaitGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzAwaitGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

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
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzAwaitGameSessionDomain::FGetAwaitTask::FGetAwaitTask(
        TSharedPtr<FEzAwaitGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAwaitGameSessionDomain::FGetAwaitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwait>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetAwaitTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Exchange::Request::FGetAwaitRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Exchange::Model::FEzAwait::FromModel(
                    Task->GetTask().Result()
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

    TSharedPtr<FAsyncTask<FEzAwaitGameSessionDomain::FGetAwaitTask>> FEzAwaitGameSessionDomain::GetAwait(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetAwaitTask>>(
            this->AsShared()
        );
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
        const auto Future = Self->ProfileValue->Run<FAcquireTask>(
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
                    Self->ProfileValue
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

    FEzAwaitGameSessionDomain::FSkipTask::FSkipTask(
        TSharedPtr<FEzAwaitGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAwaitGameSessionDomain::FSkipTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FSkipTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Skip(
                    MakeShared<Gs2::Exchange::Request::FSkipRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzAwaitGameSessionDomain::FSkipTask>> FEzAwaitGameSessionDomain::Skip(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSkipTask>>(
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
        const auto Future = Self->ProfileValue->Run<FDeleteAwaitTask>(
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
                    Self->ProfileValue
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
        const auto Future = Self->ProfileValue->Run<FModelTask>(
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
}
