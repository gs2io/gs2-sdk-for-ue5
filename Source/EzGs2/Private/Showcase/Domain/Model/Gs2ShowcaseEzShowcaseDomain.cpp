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

#include "Showcase/Domain/Model/Gs2ShowcaseEzShowcaseDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzShowcaseDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzShowcaseDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzShowcaseDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    FEzShowcaseDomain::FEzShowcaseDomain(
        Gs2::Showcase::Domain::Model::FShowcaseDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Showcase::Domain::Model::FEzDisplayItemDomainPtr FEzShowcaseDomain::DisplayItem(
        const FString DisplayItemId
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzDisplayItemDomain>(
            Domain->DisplayItem(
                DisplayItemId
            ),
            ProfileValue
        );
    }

    FEzShowcaseDomain::FModelTask::FModelTask(
        TSharedPtr<FEzShowcaseDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzShowcaseDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzShowcasePtr> Result
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
                *Result = Gs2::UE5::Showcase::Model::FEzShowcase::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzShowcaseDomain::FModelTask>> FEzShowcaseDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzShowcaseDomain::Subscribe(TFunction<void(Gs2::UE5::Showcase::Model::FEzShowcasePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Showcase::Model::FShowcasePtr Item)
            {
                Callback(Gs2::UE5::Showcase::Model::FEzShowcase::FromModel(Item));
            }
        );
    }

    void FEzShowcaseDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
