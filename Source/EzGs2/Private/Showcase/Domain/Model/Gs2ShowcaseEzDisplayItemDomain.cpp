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

#include "Showcase/Domain/Model/Gs2ShowcaseEzDisplayItemDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzDisplayItemDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzDisplayItemDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzDisplayItemDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzDisplayItemDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzDisplayItemDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    TOptional<FString> FEzDisplayItemDomain::DisplayItemId() const
    {
        return Domain->DisplayItemId;
    }

    FEzDisplayItemDomain::FEzDisplayItemDomain(
        Gs2::Showcase::Domain::Model::FDisplayItemDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzDisplayItemDomain::FModelTask::FModelTask(
        TSharedPtr<FEzDisplayItemDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDisplayItemDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItemPtr> Result
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
                *Result = Gs2::UE5::Showcase::Model::FEzDisplayItem::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzDisplayItemDomain::FModelTask>> FEzDisplayItemDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzDisplayItemDomain::Subscribe(TFunction<void(Gs2::UE5::Showcase::Model::FEzDisplayItemPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Showcase::Model::FDisplayItemPtr Item)
            {
                Callback(Gs2::UE5::Showcase::Model::FEzDisplayItem::FromModel(Item));
            }
        );
    }

    void FEzDisplayItemDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
