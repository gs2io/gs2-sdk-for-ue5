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

    TOptional<FString> FEzMoldGameSessionDomain::MoldName() const
    {
        return Domain->MoldName;
    }

    FEzMoldGameSessionDomain::FEzMoldGameSessionDomain(
        Gs2::Formation::Domain::Model::FMoldAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzMoldGameSessionDomain::FGetMoldTask::FGetMoldTask(
        TSharedPtr<FEzMoldGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMoldGameSessionDomain::FGetMoldTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzMold>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetMoldTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Formation::Request::FGetMoldRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Formation::Model::FEzMold::FromModel(
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

    TSharedPtr<FAsyncTask<FEzMoldGameSessionDomain::FGetMoldTask>> FEzMoldGameSessionDomain::GetMold(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetMoldTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormsIteratorPtr FEzMoldGameSessionDomain::Forms(
    ) const
    {
        return MakeShared<Gs2::UE5::Formation::Domain::Iterator::FEzDescribeFormsIterator>(
            Domain->Forms(
            )
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
            ProfileValue
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
        const auto Future = Self->ProfileValue->Run<FModelTask>(
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
}
