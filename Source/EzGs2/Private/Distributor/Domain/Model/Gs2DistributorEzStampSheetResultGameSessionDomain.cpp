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

#include "Distributor/Domain/Model/Gs2DistributorEzStampSheetResultGameSessionDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzStampSheetResultGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStampSheetResultGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzStampSheetResultGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    FEzStampSheetResultGameSessionDomain::FEzStampSheetResultGameSessionDomain(
        Gs2::Distributor::Domain::Model::FStampSheetResultAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzStampSheetResultGameSessionDomain::FGetStampSheetResultTask::FGetStampSheetResultTask(
        TSharedPtr<FEzStampSheetResultGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStampSheetResultGameSessionDomain::FGetStampSheetResultTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Distributor::Model::FEzStampSheetResult>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetStampSheetResultTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Distributor::Request::FGetStampSheetResultRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Distributor::Model::FEzStampSheetResult::FromModel(
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

    TSharedPtr<FAsyncTask<FEzStampSheetResultGameSessionDomain::FGetStampSheetResultTask>> FEzStampSheetResultGameSessionDomain::GetStampSheetResult(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetStampSheetResultTask>>(
            this->AsShared()
        );
    }

    FEzStampSheetResultGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStampSheetResultGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStampSheetResultGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Distributor::Model::FEzStampSheetResultPtr> Result
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
                *Result = Gs2::UE5::Distributor::Model::FEzStampSheetResult::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStampSheetResultGameSessionDomain::FModelTask>> FEzStampSheetResultGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStampSheetResultGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Distributor::Model::FEzStampSheetResultPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Distributor::Model::FStampSheetResultPtr Item)
            {
                Callback(Gs2::UE5::Distributor::Model::FEzStampSheetResult::FromModel(Item));
            }
        );
    }

    void FEzStampSheetResultGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
