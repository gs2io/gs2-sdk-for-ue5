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

#include "Formation/Domain/Model/Gs2FormationEzFormDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzFormDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzFormDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzFormDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzFormDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzFormDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFormDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzFormDomain::MoldModelName() const
    {
        return Domain->MoldModelName;
    }

    TOptional<int32> FEzFormDomain::Index() const
    {
        return Domain->Index;
    }

    FEzFormDomain::FEzFormDomain(
        Gs2::Formation::Domain::Model::FFormDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzFormDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFormDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFormDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzFormPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzForm::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzFormDomain::FModelTask>> FEzFormDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzFormDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzFormPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FFormPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzForm::FromModel(Item));
            }
        );
    }

    void FEzFormDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
