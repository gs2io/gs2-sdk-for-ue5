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

#include "Formation/Domain/Model/Gs2FormationEzPropertyFormDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzPropertyFormDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzPropertyFormDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzPropertyFormDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzPropertyFormDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzPropertyFormDomain::PropertyFormModelName() const
    {
        return Domain->PropertyFormModelName;
    }

    TOptional<FString> FEzPropertyFormDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzPropertyFormDomain::FEzPropertyFormDomain(
        Gs2::Formation::Domain::Model::FPropertyFormDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzPropertyFormDomain::FModelTask::FModelTask(
        TSharedPtr<FEzPropertyFormDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPropertyFormDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzPropertyFormPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzPropertyFormDomain::FModelTask>> FEzPropertyFormDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzPropertyFormDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzPropertyFormPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FPropertyFormPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(Item));
            }
        );
    }

    void FEzPropertyFormDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
