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

#include "Lottery/Domain/Model/Gs2LotteryEzBoxItemsGameSessionDomain.h"

namespace Gs2::UE5::Lottery::Domain::Model
{

    TOptional<FString> FEzBoxItemsGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBoxItemsGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzBoxItemsGameSessionDomain::PrizeTableName() const
    {
        return Domain->PrizeTableName;
    }

    FEzBoxItemsGameSessionDomain::FEzBoxItemsGameSessionDomain(
        Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzBoxItemsGameSessionDomain::FGetBoxTask::FGetBoxTask(
        TSharedPtr<FEzBoxItemsGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBoxItemsGameSessionDomain::FGetBoxTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItems>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetBoxTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Lottery::Request::FGetBoxRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Lottery::Model::FEzBoxItems::FromModel(
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

    TSharedPtr<FAsyncTask<FEzBoxItemsGameSessionDomain::FGetBoxTask>> FEzBoxItemsGameSessionDomain::GetBox(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetBoxTask>>(
            this->AsShared()
        );
    }

    FEzBoxItemsGameSessionDomain::FResetBoxTask::FResetBoxTask(
        TSharedPtr<FEzBoxItemsGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBoxItemsGameSessionDomain::FResetBoxTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FResetBoxTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->ResetBox(
                    MakeShared<Gs2::Lottery::Request::FResetBoxRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Lottery::Domain::Model::FEzBoxItemsGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzBoxItemsGameSessionDomain::FResetBoxTask>> FEzBoxItemsGameSessionDomain::ResetBox(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FResetBoxTask>>(
            this->AsShared()
        );
    }

    FEzBoxItemsGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBoxItemsGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBoxItemsGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItemsPtr> Result
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
                *Result = Gs2::UE5::Lottery::Model::FEzBoxItems::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzBoxItemsGameSessionDomain::FModelTask>> FEzBoxItemsGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBoxItemsGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Lottery::Model::FEzBoxItemsPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Lottery::Model::FBoxItemsPtr Item)
            {
                Callback(Gs2::UE5::Lottery::Model::FEzBoxItems::FromModel(Item));
            }
        );
    }

    void FEzBoxItemsGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
