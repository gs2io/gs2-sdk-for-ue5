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

#include "Grade/Domain/Model/Gs2GradeEzGradeModelDomain.h"

namespace Gs2::UE5::Grade::Domain::Model
{

    TOptional<FString> FEzGradeModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGradeModelDomain::GradeName() const
    {
        return Domain->GradeName;
    }

    FEzGradeModelDomain::FEzGradeModelDomain(
        Gs2::Grade::Domain::Model::FGradeModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzGradeModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGradeModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGradeModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeModelPtr> Result
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
                *Result = Gs2::UE5::Grade::Model::FEzGradeModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGradeModelDomain::FModelTask>> FEzGradeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGradeModelDomain::Subscribe(TFunction<void(Gs2::UE5::Grade::Model::FEzGradeModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Grade::Model::FGradeModelPtr Item)
            {
                Callback(Gs2::UE5::Grade::Model::FEzGradeModel::FromModel(Item));
            }
        );
    }

    void FEzGradeModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
