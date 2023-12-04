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

#include "Quest/Domain/Model/Gs2QuestEzCompletedQuestListGameSessionDomain.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    TOptional<FString> FEzCompletedQuestListGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCompletedQuestListGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzCompletedQuestListGameSessionDomain::QuestGroupName() const
    {
        return Domain->QuestGroupName;
    }

    FEzCompletedQuestListGameSessionDomain::FEzCompletedQuestListGameSessionDomain(
        Gs2::Quest::Domain::Model::FCompletedQuestListAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzCompletedQuestListGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCompletedQuestListGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCompletedQuestListGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr> Result
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
                *Result = Gs2::UE5::Quest::Model::FEzCompletedQuestList::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCompletedQuestListGameSessionDomain::FModelTask>> FEzCompletedQuestListGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzCompletedQuestListGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Quest::Model::FCompletedQuestListPtr Item)
            {
                Callback(Gs2::UE5::Quest::Model::FEzCompletedQuestList::FromModel(Item));
            }
        );
    }

    void FEzCompletedQuestListGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
