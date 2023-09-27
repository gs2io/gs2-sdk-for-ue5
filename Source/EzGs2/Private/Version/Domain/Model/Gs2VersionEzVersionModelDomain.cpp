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

#include "Version/Domain/Model/Gs2VersionEzVersionModelDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzVersionModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzVersionModelDomain::VersionName() const
    {
        return Domain->VersionName;
    }

    FEzVersionModelDomain::FEzVersionModelDomain(
        Gs2::Version::Domain::Model::FVersionModelDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzVersionModelDomain::FGetVersionModelTask::FGetVersionModelTask(
        TSharedPtr<FEzVersionModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzVersionModelDomain::FGetVersionModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetVersionModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Version::Request::FGetVersionModelRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Version::Model::FEzVersionModel::FromModel(
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

    TSharedPtr<FAsyncTask<FEzVersionModelDomain::FGetVersionModelTask>> FEzVersionModelDomain::GetVersionModel(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetVersionModelTask>>(
            this->AsShared()
        );
    }

    FEzVersionModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzVersionModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzVersionModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModelPtr> Result
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
                *Result = Gs2::UE5::Version::Model::FEzVersionModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzVersionModelDomain::FModelTask>> FEzVersionModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzVersionModelDomain::Subscribe(TFunction<void(Gs2::UE5::Version::Model::FEzVersionModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Version::Model::FVersionModelPtr Item)
            {
                Callback(Gs2::UE5::Version::Model::FEzVersionModel::FromModel(Item));
            }
        );
    }

    void FEzVersionModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
