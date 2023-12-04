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
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::MegaField::Domain::Iterator::FEzDescribeLayerModelsIteratorPtr FEzAreaModelDomain::LayerModels(
    ) const
    {
        return MakeShared<Gs2::UE5::MegaField::Domain::Iterator::FEzDescribeLayerModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzAreaModelDomain::SubscribeLayerModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeLayerModels(
            Callback
        );
    }

    void FEzAreaModelDomain::UnsubscribeLayerModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeLayerModels(
            CallbackId
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
            ConnectionValue
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
        const auto Future = Self->ConnectionValue->Run(
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

    Gs2::Core::Domain::CallbackID FEzAreaModelDomain::Subscribe(TFunction<void(Gs2::UE5::MegaField::Model::FEzAreaModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::MegaField::Model::FAreaModelPtr Item)
            {
                Callback(Gs2::UE5::MegaField::Model::FEzAreaModel::FromModel(Item));
            }
        );
    }

    void FEzAreaModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
