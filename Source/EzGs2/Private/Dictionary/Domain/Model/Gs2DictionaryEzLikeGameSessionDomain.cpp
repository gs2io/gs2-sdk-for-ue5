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

#include "Dictionary/Domain/Model/Gs2DictionaryEzLikeGameSessionDomain.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    TOptional<FString> FEzLikeGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzLikeGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzLikeGameSessionDomain::EntryModelName() const
    {
        return Domain->EntryModelName;
    }

    FEzLikeGameSessionDomain::FEzLikeGameSessionDomain(
        Gs2::Dictionary::Domain::Model::FLikeAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzLikeGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzLikeGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzLikeGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Dictionary::Model::FEzLikePtr> Result
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
                *Result = Gs2::UE5::Dictionary::Model::FEzLike::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzLikeGameSessionDomain::FModelTask>> FEzLikeGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzLikeGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Dictionary::Model::FEzLikePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Dictionary::Model::FLikePtr Item)
            {
                Callback(Gs2::UE5::Dictionary::Model::FEzLike::FromModel(Item));
            }
        );
    }

    void FEzLikeGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
