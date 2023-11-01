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

#include "Idle/Domain/Model/Gs2IdleEzStatusGameSessionDomain.h"

namespace Gs2::UE5::Idle::Domain::Model
{

    TOptional<FString> FEzStatusGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzStatusGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzStatusGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStatusGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzStatusGameSessionDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    FEzStatusGameSessionDomain::FEzStatusGameSessionDomain(
        Gs2::Idle::Domain::Model::FStatusAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzStatusGameSessionDomain::FPredictionTask::FPredictionTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FPredictionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FPredictionTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Prediction(
                    MakeShared<Gs2::Idle::Request::FPredictionRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>>();
                for (auto Value : *Task->GetTask().Result()) {
                    (**Result).Add(Gs2::UE5::Idle::Model::FEzAcquireAction::FromModel(Value));
                }
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FPredictionTask>> FEzStatusGameSessionDomain::Prediction(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPredictionTask>>(
            this->AsShared()
        );
    }

    FEzStatusGameSessionDomain::FReceiveTask::FReceiveTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FReceiveTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Receive(
                    MakeShared<Gs2::Idle::Request::FReceiveRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Idle::Domain::Model::FEzStatusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FReceiveTask>> FEzStatusGameSessionDomain::Receive(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(
            this->AsShared()
        );
    }

    FEzStatusGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Idle::Model::FEzStatusPtr> Result
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
                *Result = Gs2::UE5::Idle::Model::FEzStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FModelTask>> FEzStatusGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStatusGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Idle::Model::FEzStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Idle::Model::FStatusPtr Item)
            {
                Callback(Gs2::UE5::Idle::Model::FEzStatus::FromModel(Item));
            }
        );
    }

    void FEzStatusGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
