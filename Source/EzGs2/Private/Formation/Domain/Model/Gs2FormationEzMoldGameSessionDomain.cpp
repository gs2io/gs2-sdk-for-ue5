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

#include "Formation/Domain/Model/Gs2FormationEzMoldGameSessionDomain.h"

namespace Gs2::UE5::Formation::Domain::Model
{

    TOptional<FString> FEzMoldGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzMoldGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzMoldGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzMoldGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMoldGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzMoldGameSessionDomain::MoldModelName() const
    {
        return Domain->MoldModelName;
    }

    FEzMoldGameSessionDomain::FEzMoldGameSessionDomain(
        Gs2::Formation::Domain::Model::FMoldAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormsIteratorPtr FEzMoldGameSessionDomain::Forms(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzMoldGameSessionDomain::SubscribeForms(TFunction<void()> Callback)
    {
        return Domain->SubscribeForms(
            Callback
        );
    }

    void FEzMoldGameSessionDomain::UnsubscribeForms(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeForms(
            CallbackId
        );
    }

    Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomainPtr FEzMoldGameSessionDomain::Form(
        const int32 Index
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Model::FEzFormGameSessionDomain>(
            Domain->Form(
                Index
            ),
            GameSession,
            ConnectionValue
        );
    }

    FEzMoldGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMoldGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMoldGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Formation::Model::FEzMoldPtr> Result
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
                *Result = Gs2::UE5::Formation::Model::FEzMold::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMoldGameSessionDomain::FModelTask>> FEzMoldGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMoldGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Formation::Model::FEzMoldPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Formation::Model::FMoldPtr Item)
            {
                Callback(Gs2::UE5::Formation::Model::FEzMold::FromModel(Item));
            }
        );
    }

    void FEzMoldGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
