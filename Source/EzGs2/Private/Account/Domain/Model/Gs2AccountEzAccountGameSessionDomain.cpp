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

#include "Account/Domain/Model/Gs2AccountEzAccountGameSessionDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Account::Model::FEzBanStatus>>> FEzAccountGameSessionDomain::BanStatuses() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Account::Model::FEzBanStatus>>>();
            for (auto Value : *Domain->BanStatuses) {
                Result->Add(
                    Gs2::UE5::Account::Model::FEzBanStatus::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzAccountGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzAccountGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzAccountGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzAccountGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzAccountGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzAccountGameSessionDomain::FEzAccountGameSessionDomain(
        Gs2::Account::Domain::Model::FAccountAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Account::Domain::Iterator::FEzDescribeTakeOversIteratorPtr FEzAccountGameSessionDomain::TakeOvers(
    ) const
    {
        return MakeShared<Gs2::UE5::Account::Domain::Iterator::FEzDescribeTakeOversIterator>(
            Domain->TakeOvers(
            )
        );
    }

    Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomainPtr FEzAccountGameSessionDomain::TakeOver(
        const int32 Type
    ) const
    {
        return MakeShared<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>(
            Domain->TakeOver(
                Type
            ),
            ProfileValue
        );
    }

    FEzAccountGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzAccountGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAccountGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Account::Model::FEzAccountPtr> Result
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
                *Result = Gs2::UE5::Account::Model::FEzAccount::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzAccountGameSessionDomain::FModelTask>> FEzAccountGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
