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

#include "MegaField/Domain/Model/Gs2MegaFieldEzLayerModelDomain.h"

namespace Gs2::UE5::MegaField::Domain::Model
{

    TOptional<FString> FEzLayerModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzLayerModelDomain::AreaModelName() const
    {
        return Domain->AreaModelName;
    }

    TOptional<FString> FEzLayerModelDomain::LayerModelName() const
    {
        return Domain->LayerModelName;
    }

    FEzLayerModelDomain::FEzLayerModelDomain(
        Gs2::MegaField::Domain::Model::FLayerModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzLayerModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzLayerModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzLayerModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModelPtr> Result
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
                *Result = Gs2::UE5::MegaField::Model::FEzLayerModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzLayerModelDomain::FModelTask>> FEzLayerModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzLayerModelDomain::Subscribe(TFunction<void(Gs2::UE5::MegaField::Model::FEzLayerModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::MegaField::Model::FLayerModelPtr Item)
            {
                Callback(Gs2::UE5::MegaField::Model::FEzLayerModel::FromModel(Item));
            }
        );
    }

    void FEzLayerModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
