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

#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomDisplayItemDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzRandomDisplayItemDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzRandomDisplayItemDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzRandomDisplayItemDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRandomDisplayItemDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzRandomDisplayItemDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    TOptional<FString> FEzRandomDisplayItemDomain::DisplayItemName() const
    {
        return Domain->DisplayItemName;
    }

    FEzRandomDisplayItemDomain::FEzRandomDisplayItemDomain(
        Gs2::Showcase::Domain::Model::FRandomDisplayItemDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzRandomDisplayItemDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRandomDisplayItemDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRandomDisplayItemDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr> Result
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
                *Result = Gs2::UE5::Showcase::Model::FEzRandomDisplayItem::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRandomDisplayItemDomain::FModelTask>> FEzRandomDisplayItemDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRandomDisplayItemDomain::Subscribe(TFunction<void(Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Showcase::Model::FRandomDisplayItemPtr Item)
            {
                Callback(Gs2::UE5::Showcase::Model::FEzRandomDisplayItem::FromModel(Item));
            }
        );
    }

    void FEzRandomDisplayItemDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
