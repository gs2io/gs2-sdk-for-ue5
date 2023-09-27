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

#include "News/Domain/Model/Gs2NewsEzSetCookieRequestEntryGameSessionDomain.h"

namespace Gs2::UE5::News::Domain::Model
{

    TOptional<FString> FEzSetCookieRequestEntryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSetCookieRequestEntryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSetCookieRequestEntryGameSessionDomain::Key() const
    {
        return Domain->Key;
    }

    TOptional<FString> FEzSetCookieRequestEntryGameSessionDomain::Value() const
    {
        return Domain->Value;
    }

    FEzSetCookieRequestEntryGameSessionDomain::FEzSetCookieRequestEntryGameSessionDomain(
        Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSetCookieRequestEntryGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSetCookieRequestEntryGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSetCookieRequestEntryGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::News::Model::FEzSetCookieRequestEntryPtr> Result
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
                *Result = Gs2::UE5::News::Model::FEzSetCookieRequestEntry::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSetCookieRequestEntryGameSessionDomain::FModelTask>> FEzSetCookieRequestEntryGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSetCookieRequestEntryGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::News::Model::FEzSetCookieRequestEntryPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::News::Model::FSetCookieRequestEntryPtr Item)
            {
                Callback(Gs2::UE5::News::Model::FEzSetCookieRequestEntry::FromModel(Item));
            }
        );
    }

    void FEzSetCookieRequestEntryGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
