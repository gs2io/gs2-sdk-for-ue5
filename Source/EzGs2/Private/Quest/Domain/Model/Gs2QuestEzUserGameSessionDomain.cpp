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

#include "Quest/Domain/Model/Gs2QuestEzUserGameSessionDomain.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzUserGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

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
        Gs2::Quest::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzUserGameSessionDomain::FStartTask::FStartTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString QuestGroupName,
        FString QuestName,
        TOptional<bool> Force,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config
    ): Self(Self), QuestGroupName(QuestGroupName), QuestName(QuestName), Force(Force), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FStartTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FStartTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Start(
                    MakeShared<Gs2::Quest::Request::FStartRequest>()
                        ->WithQuestGroupName(QuestGroupName)
                        ->WithQuestName(QuestName)
                        ->WithForce(Force)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FConfig>>>();
                            if (!Config.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Config) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Quest::Domain::Model::FEzUserGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FStartTask>> FEzUserGameSessionDomain::Start(
        FString QuestGroupName,
        FString QuestName,
        TOptional<bool> Force,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FStartTask>>(
            this->AsShared(),
            QuestGroupName,
            QuestName,
            Force,
            Config
        );
    }

    Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomainPtr FEzUserGameSessionDomain::Progress(
    ) const
    {
        return MakeShared<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>(
            Domain->Progress(
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Quest::Domain::Iterator::FEzDescribeCompletedQuestListsIteratorPtr FEzUserGameSessionDomain::CompletedQuestLists(
    ) const
    {
        return MakeShared<Gs2::UE5::Quest::Domain::Iterator::FEzDescribeCompletedQuestListsIterator>(
            Domain->CompletedQuestLists(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeCompletedQuestLists(TFunction<void()> Callback)
    {
        return Domain->SubscribeCompletedQuestLists(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeCompletedQuestLists(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeCompletedQuestLists(
            CallbackId
        );
    }

    Gs2::UE5::Quest::Domain::Model::FEzCompletedQuestListGameSessionDomainPtr FEzUserGameSessionDomain::CompletedQuestList(
        const FString QuestGroupName
    ) const
    {
        return MakeShared<Gs2::UE5::Quest::Domain::Model::FEzCompletedQuestListGameSessionDomain>(
            Domain->CompletedQuestList(
                QuestGroupName
            ),
            ProfileValue
        );
    }
}
