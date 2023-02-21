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

#include "Dictionary/Domain/Model/Gs2DictionaryEzEntryDomain.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    TOptional<FString> FEzEntryDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzEntryDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzEntryDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzEntryDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzEntryDomain::EntryModelName() const
    {
        return Domain->EntryModelName;
    }

    FEzEntryDomain::FEzEntryDomain(
        Gs2::Dictionary::Domain::Model::FEntryDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzEntryDomain::FModelTask::FModelTask(
        TSharedPtr<FEzEntryDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzEntryDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryPtr> Result
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
                *Result = Gs2::UE5::Dictionary::Model::FEzEntry::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzEntryDomain::FModelTask>> FEzEntryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
