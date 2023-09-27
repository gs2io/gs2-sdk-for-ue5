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

#include "Idle/Domain/Model/Gs2IdleEzCategoryModelDomain.h"

namespace Gs2::UE5::Idle::Domain::Model
{

    TOptional<FString> FEzCategoryModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCategoryModelDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    FEzCategoryModelDomain::FEzCategoryModelDomain(
        Gs2::Idle::Domain::Model::FCategoryModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzCategoryModelDomain::FGetCategoryModelTask::FGetCategoryModelTask(
        TSharedPtr<FEzCategoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCategoryModelDomain::FGetCategoryModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Idle::Model::FEzCategoryModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetCategoryModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Idle::Request::FGetCategoryModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Idle::Model::FEzCategoryModel::FromModel(
                    Task->GetTask().Result()
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

    TSharedPtr<FAsyncTask<FEzCategoryModelDomain::FGetCategoryModelTask>> FEzCategoryModelDomain::GetCategoryModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetCategoryModelTask>>(
            this->AsShared()
        );
    }

    FEzCategoryModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCategoryModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCategoryModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Idle::Model::FEzCategoryModelPtr> Result
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
                *Result = Gs2::UE5::Idle::Model::FEzCategoryModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCategoryModelDomain::FModelTask>> FEzCategoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzCategoryModelDomain::Subscribe(TFunction<void(Gs2::UE5::Idle::Model::FEzCategoryModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Idle::Model::FCategoryModelPtr Item)
            {
                Callback(Gs2::UE5::Idle::Model::FEzCategoryModel::FromModel(Item));
            }
        );
    }

    void FEzCategoryModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
