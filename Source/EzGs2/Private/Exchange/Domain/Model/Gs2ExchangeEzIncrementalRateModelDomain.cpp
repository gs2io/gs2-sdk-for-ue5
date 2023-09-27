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

#include "Exchange/Domain/Model/Gs2ExchangeEzIncrementalRateModelDomain.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    TOptional<FString> FEzIncrementalRateModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzIncrementalRateModelDomain::RateName() const
    {
        return Domain->RateName;
    }

    FEzIncrementalRateModelDomain::FEzIncrementalRateModelDomain(
        Gs2::Exchange::Domain::Model::FIncrementalRateModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzIncrementalRateModelDomain::FGetIncrementalRateModelTask::FGetIncrementalRateModelTask(
        TSharedPtr<FEzIncrementalRateModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzIncrementalRateModelDomain::FGetIncrementalRateModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzIncrementalRateModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetIncrementalRateModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Exchange::Request::FGetIncrementalRateModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Exchange::Model::FEzIncrementalRateModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzIncrementalRateModelDomain::FGetIncrementalRateModelTask>> FEzIncrementalRateModelDomain::GetIncrementalRateModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetIncrementalRateModelTask>>(
            this->AsShared()
        );
    }

    FEzIncrementalRateModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzIncrementalRateModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzIncrementalRateModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Exchange::Model::FEzIncrementalRateModelPtr> Result
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
                *Result = Gs2::UE5::Exchange::Model::FEzIncrementalRateModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzIncrementalRateModelDomain::FModelTask>> FEzIncrementalRateModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzIncrementalRateModelDomain::Subscribe(TFunction<void(Gs2::UE5::Exchange::Model::FEzIncrementalRateModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Exchange::Model::FIncrementalRateModelPtr Item)
            {
                Callback(Gs2::UE5::Exchange::Model::FEzIncrementalRateModel::FromModel(Item));
            }
        );
    }

    void FEzIncrementalRateModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
