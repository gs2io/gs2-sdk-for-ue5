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

#include "Distributor/Domain/Model/Gs2DistributorEzStampSheetResultDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzStampSheetResultDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStampSheetResultDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzStampSheetResultDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    FEzStampSheetResultDomain::FEzStampSheetResultDomain(
        Gs2::Distributor::Domain::Model::FStampSheetResultDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzStampSheetResultDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStampSheetResultDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStampSheetResultDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Distributor::Model::FEzStampSheetResultPtr> Result
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
                *Result = Gs2::UE5::Distributor::Model::FEzStampSheetResult::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStampSheetResultDomain::FModelTask>> FEzStampSheetResultDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStampSheetResultDomain::Subscribe(TFunction<void(Gs2::UE5::Distributor::Model::FEzStampSheetResultPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Distributor::Model::FStampSheetResultPtr Item)
            {
                Callback(Gs2::UE5::Distributor::Model::FEzStampSheetResult::FromModel(Item));
            }
        );
    }

    void FEzStampSheetResultDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
