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

#include "Quest/Domain/Model/Gs2QuestEzQuestModelDomain.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    TOptional<FString> FEzQuestModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzQuestModelDomain::QuestGroupName() const
    {
        return Domain->QuestGroupName;
    }

    TOptional<FString> FEzQuestModelDomain::QuestName() const
    {
        return Domain->QuestName;
    }

    FEzQuestModelDomain::FEzQuestModelDomain(
        Gs2::Quest::Domain::Model::FQuestModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzQuestModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzQuestModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzQuestModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModelPtr> Result
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
                *Result = Gs2::UE5::Quest::Model::FEzQuestModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzQuestModelDomain::FModelTask>> FEzQuestModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzQuestModelDomain::Subscribe(TFunction<void(Gs2::UE5::Quest::Model::FEzQuestModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Quest::Model::FQuestModelPtr Item)
            {
                Callback(Gs2::UE5::Quest::Model::FEzQuestModel::FromModel(Item));
            }
        );
    }

    void FEzQuestModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
