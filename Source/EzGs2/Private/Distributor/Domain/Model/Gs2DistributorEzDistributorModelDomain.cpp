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

#include "Distributor/Domain/Model/Gs2DistributorEzDistributorModelDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzDistributorModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzDistributorModelDomain::DistributorName() const
    {
        return Domain->DistributorName;
    }

    FEzDistributorModelDomain::FEzDistributorModelDomain(
        Gs2::Distributor::Domain::Model::FDistributorModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzDistributorModelDomain::FGetDistributorModelTask::FGetDistributorModelTask(
        TSharedPtr<FEzDistributorModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDistributorModelDomain::FGetDistributorModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Distributor::Model::FEzDistributorModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetDistributorModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Distributor::Request::FGetDistributorModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Distributor::Model::FEzDistributorModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzDistributorModelDomain::FGetDistributorModelTask>> FEzDistributorModelDomain::GetDistributorModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetDistributorModelTask>>(
            this->AsShared()
        );
    }

    FEzDistributorModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzDistributorModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDistributorModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Distributor::Model::FEzDistributorModelPtr> Result
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
                *Result = Gs2::UE5::Distributor::Model::FEzDistributorModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzDistributorModelDomain::FModelTask>> FEzDistributorModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzDistributorModelDomain::Subscribe(TFunction<void(Gs2::UE5::Distributor::Model::FEzDistributorModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Distributor::Model::FDistributorModelPtr Item)
            {
                Callback(Gs2::UE5::Distributor::Model::FEzDistributorModel::FromModel(Item));
            }
        );
    }

    void FEzDistributorModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
