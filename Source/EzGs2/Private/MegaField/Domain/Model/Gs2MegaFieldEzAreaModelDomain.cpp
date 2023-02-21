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

#include "MegaField/Domain/Model/Gs2MegaFieldEzAreaModelDomain.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    TOptional<FString> FEzAreaModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzAreaModelDomain::AreaModelName() const
    {
        return Domain->AreaModelName;
    }

    FEzAreaModelDomain::FEzAreaModelDomain(
        Gs2::MegaField::Domain::Model::FAreaModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzAreaModelDomain::FGetAreaModelTask::FGetAreaModelTask(
        TSharedPtr<FEzAreaModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAreaModelDomain::FGetAreaModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::MegaField::Model::FEzAreaModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetAreaModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::MegaField::Request::FGetAreaModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::MegaField::Model::FEzAreaModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzAreaModelDomain::FGetAreaModelTask>> FEzAreaModelDomain::GetAreaModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetAreaModelTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::MegaField::Domain::Iterator::FEzDescribeLayerModelsIteratorPtr FEzAreaModelDomain::LayerModels(
    ) const
    {
        return MakeShared<Gs2::UE5::MegaField::Domain::Iterator::FEzDescribeLayerModelsIterator>(
            Domain->LayerModels(
            )
        );
    }

    Gs2::UE5::MegaField::Domain::Model::FEzLayerModelDomainPtr FEzAreaModelDomain::LayerModel(
        const FString LayerModelName
    ) const
    {
        return MakeShared<Gs2::UE5::MegaField::Domain::Model::FEzLayerModelDomain>(
            Domain->LayerModel(
                LayerModelName
            ),
            ProfileValue
        );
    }

    FEzAreaModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzAreaModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAreaModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzAreaModelPtr> Result
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
                *Result = Gs2::UE5::MegaField::Model::FEzAreaModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzAreaModelDomain::FModelTask>> FEzAreaModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
