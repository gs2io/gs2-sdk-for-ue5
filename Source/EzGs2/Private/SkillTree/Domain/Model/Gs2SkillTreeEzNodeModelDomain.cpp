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

#include "SkillTree/Domain/Model/Gs2SkillTreeEzNodeModelDomain.h"

namespace Gs2::UE5::SkillTree::Domain::Model
{

    TOptional<FString> FEzNodeModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzNodeModelDomain::NodeModelName() const
    {
        return Domain->NodeModelName;
    }

    FEzNodeModelDomain::FEzNodeModelDomain(
        Gs2::SkillTree::Domain::Model::FNodeModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzNodeModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzNodeModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNodeModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::SkillTree::Model::FEzNodeModelPtr> Result
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
                *Result = Gs2::UE5::SkillTree::Model::FEzNodeModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzNodeModelDomain::FModelTask>> FEzNodeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzNodeModelDomain::Subscribe(TFunction<void(Gs2::UE5::SkillTree::Model::FEzNodeModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::SkillTree::Model::FNodeModelPtr Item)
            {
                Callback(Gs2::UE5::SkillTree::Model::FEzNodeModel::FromModel(Item));
            }
        );
    }

    void FEzNodeModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
