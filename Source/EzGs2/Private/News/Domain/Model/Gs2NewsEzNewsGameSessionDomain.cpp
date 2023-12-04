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

#include "News/Domain/Model/Gs2NewsEzNewsGameSessionDomain.h"

namespace Gs2::UE5::News::Domain::Model
{

    TOptional<FString> FEzNewsGameSessionDomain::BrowserUrl() const
    {
        return Domain->BrowserUrl;
    }

    TOptional<FString> FEzNewsGameSessionDomain::ZipUrl() const
    {
        return Domain->ZipUrl;
    }

    TOptional<FString> FEzNewsGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzNewsGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzNewsGameSessionDomain::FEzNewsGameSessionDomain(
        Gs2::News::Domain::Model::FNewsAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzNewsGameSessionDomain::FGetContentsUrlTask::FGetContentsUrlTask(
        TSharedPtr<FEzNewsGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNewsGameSessionDomain::FGetContentsUrlTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::News::Domain::Model::FEzSetCookieRequestEntryGameSessionDomain>>>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->WantGrant(
                    MakeShared<Gs2::News::Request::FWantGrantRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::News::Domain::Model::FEzSetCookieRequestEntryGameSessionDomain>>>();
                for (auto Value : *Task->GetTask().Result()) {
                    (**Result).Add(MakeShared<Gs2::UE5::News::Domain::Model::FEzSetCookieRequestEntryGameSessionDomain>(
                        Value,
                        Self->GameSession,
                        Self->ConnectionValue
                    ));
                }
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

    TSharedPtr<FAsyncTask<FEzNewsGameSessionDomain::FGetContentsUrlTask>> FEzNewsGameSessionDomain::GetContentsUrl(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetContentsUrlTask>>(
            this->AsShared()
        );
    }

    FEzNewsGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzNewsGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNewsGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::News::Model::FEzNewsPtr> Result
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
                *Result = Gs2::UE5::News::Model::FEzNews::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzNewsGameSessionDomain::FModelTask>> FEzNewsGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzNewsGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::News::Model::FEzNewsPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::News::Model::FNewsPtr Item)
            {
                Callback(Gs2::UE5::News::Model::FEzNews::FromModel(Item));
            }
        );
    }

    void FEzNewsGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
