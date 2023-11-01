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

#include "Limit/Domain/Model/Gs2LimitEzCounterGameSessionDomain.h"

namespace Gs2::UE5::Limit::Domain::Model
{

    TOptional<FString> FEzCounterGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCounterGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzCounterGameSessionDomain::LimitName() const
    {
        return Domain->LimitName;
    }

    TOptional<FString> FEzCounterGameSessionDomain::CounterName() const
    {
        return Domain->CounterName;
    }

    FEzCounterGameSessionDomain::FEzCounterGameSessionDomain(
        Gs2::Limit::Domain::Model::FCounterAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzCounterGameSessionDomain::FCountUpTask::FCountUpTask(
        TSharedPtr<FEzCounterGameSessionDomain> Self,
        TOptional<int32> CountUpValue,
        TOptional<int32> MaxValue
    ): Self(Self), CountUpValue(CountUpValue), MaxValue(MaxValue)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCounterGameSessionDomain::FCountUpTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FCountUpTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CountUp(
                    MakeShared<Gs2::Limit::Request::FCountUpRequest>()
                        ->WithCountUpValue(CountUpValue)
                        ->WithMaxValue(MaxValue)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzCounterGameSessionDomain::FCountUpTask>> FEzCounterGameSessionDomain::CountUp(
        TOptional<int32> CountUpValue,
        TOptional<int32> MaxValue
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCountUpTask>>(
            this->AsShared(),
            CountUpValue,
            MaxValue
        );
    }

    FEzCounterGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCounterGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCounterGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Limit::Model::FEzCounterPtr> Result
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
                *Result = Gs2::UE5::Limit::Model::FEzCounter::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCounterGameSessionDomain::FModelTask>> FEzCounterGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzCounterGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Limit::Model::FEzCounterPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Limit::Model::FCounterPtr Item)
            {
                Callback(Gs2::UE5::Limit::Model::FEzCounter::FromModel(Item));
            }
        );
    }

    void FEzCounterGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
