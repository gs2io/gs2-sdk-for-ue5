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

#include "Inbox/Domain/Model/Gs2InboxEzUserGameSessionDomain.h"

namespace Gs2::UE5::Inbox::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Inbox::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzUserGameSessionDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        TSharedPtr<FEzUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FReceiveGlobalMessageTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>>>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FReceiveGlobalMessageTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->ReceiveGlobalMessage(
                    MakeShared<Gs2::Inbox::Request::FReceiveGlobalMessageRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>>>();
                for (auto Value : *Task->GetTask().Result()) {
                    (**Result).Add(MakeShared<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>(
                        Value,
                        Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FReceiveGlobalMessageTask>> FEzUserGameSessionDomain::ReceiveGlobalMessage(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveGlobalMessageTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Inbox::Domain::Iterator::FEzDescribeMessagesIteratorPtr FEzUserGameSessionDomain::Messages(
          const TOptional<bool> IsRead
    ) const
    {
        return MakeShared<Gs2::UE5::Inbox::Domain::Iterator::FEzDescribeMessagesIterator>(
            Domain->Messages(
                IsRead
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeMessages(TFunction<void()> Callback)
    {
        return Domain->SubscribeMessages(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeMessages(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeMessages(
            CallbackId
        );
    }

    Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomainPtr FEzUserGameSessionDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomain>(
            Domain->Message(
                MessageName
            ),
            ProfileValue
        );
    }
}
