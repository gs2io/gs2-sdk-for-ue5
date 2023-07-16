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

#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomShowcaseGameSessionDomain.h"

namespace Gs2::UE5::Showcase::Domain::Model
{

    TOptional<FString> FEzRandomShowcaseGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRandomShowcaseGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRandomShowcaseGameSessionDomain::ShowcaseName() const
    {
        return Domain->ShowcaseName;
    }

    FEzRandomShowcaseGameSessionDomain::FEzRandomShowcaseGameSessionDomain(
        Gs2::Showcase::Domain::Model::FRandomShowcaseAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRandomShowcaseGameSessionDomain::FGetRandomShowcaseDisplayItemTask::FGetRandomShowcaseDisplayItemTask(
        TSharedPtr<FEzRandomShowcaseGameSessionDomain> Self,
        TOptional<FString> DisplayItemName
    ): Self(Self), DisplayItemName(DisplayItemName)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRandomShowcaseGameSessionDomain::FGetRandomShowcaseDisplayItemTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetRandomShowcaseDisplayItemTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetSalesItem(
                    MakeShared<Gs2::Showcase::Request::FGetRandomShowcaseSalesItemRequest>()
                        ->WithDisplayItemName(DisplayItemName)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzRandomShowcaseGameSessionDomain::FGetRandomShowcaseDisplayItemTask>> FEzRandomShowcaseGameSessionDomain::GetRandomShowcaseDisplayItem(
        TOptional<FString> DisplayItemName
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetRandomShowcaseDisplayItemTask>>(
            this->AsShared(),
            DisplayItemName
        );
    }

    Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomainPtr FEzRandomShowcaseGameSessionDomain::RandomDisplayItem(
        const FString DisplayItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomain>(
            Domain->RandomDisplayItem(
                DisplayItemName
            ),
            ProfileValue
        );
    }
}
