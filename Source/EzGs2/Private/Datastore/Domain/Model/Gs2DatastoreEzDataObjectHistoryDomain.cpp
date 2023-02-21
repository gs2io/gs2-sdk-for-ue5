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

#include "Datastore/Domain/Model/Gs2DatastoreEzDataObjectHistoryDomain.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    TOptional<FString> FEzDataObjectHistoryDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzDataObjectHistoryDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzDataObjectHistoryDomain::DataObjectName() const
    {
        return Domain->DataObjectName;
    }

    TOptional<FString> FEzDataObjectHistoryDomain::Generation() const
    {
        return Domain->Generation;
    }

    FEzDataObjectHistoryDomain::FEzDataObjectHistoryDomain(
        Gs2::Datastore::Domain::Model::FDataObjectHistoryDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzDataObjectHistoryDomain::FModelTask::FModelTask(
        TSharedPtr<FEzDataObjectHistoryDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectHistoryDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr> Result
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
                *Result = Gs2::UE5::Datastore::Model::FEzDataObjectHistory::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzDataObjectHistoryDomain::FModelTask>> FEzDataObjectHistoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
