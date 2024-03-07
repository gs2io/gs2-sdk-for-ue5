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

#include "Mission/Domain/Model/Gs2MissionEzCounterDomain.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzComplete>>> FEzCounterDomain::ChangedCompletes() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzComplete>>>();
            for (auto Value : *Domain->ChangedCompletes) {
                Result->Add(
                    Gs2::UE5::Mission::Model::FEzComplete::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzCounterDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCounterDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzCounterDomain::CounterName() const
    {
        return Domain->CounterName;
    }

    FEzCounterDomain::FEzCounterDomain(
        Gs2::Mission::Domain::Model::FCounterDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzCounterDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCounterDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCounterDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterPtr> Result
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
                *Result = Gs2::UE5::Mission::Model::FEzCounter::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCounterDomain::FModelTask>> FEzCounterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzCounterDomain::Subscribe(TFunction<void(Gs2::UE5::Mission::Model::FEzCounterPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Mission::Model::FCounterPtr Item)
            {
                Callback(Gs2::UE5::Mission::Model::FEzCounter::FromModel(Item));
            }
        );
    }

    void FEzCounterDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
