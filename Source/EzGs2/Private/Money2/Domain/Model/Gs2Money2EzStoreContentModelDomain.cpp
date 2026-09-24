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

#include "Money2/Domain/Model/Gs2Money2EzStoreContentModelDomain.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    TOptional<FString> FEzStoreContentModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStoreContentModelDomain::ContentName() const
    {
        return Domain->ContentName;
    }

    FEzStoreContentModelDomain::FEzStoreContentModelDomain(
        Gs2::Money2::Domain::Model::FStoreContentModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzStoreContentModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStoreContentModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStoreContentModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Money2::Model::FEzStoreContentModelPtr> Result
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
                *Result = Gs2::UE5::Money2::Model::FEzStoreContentModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStoreContentModelDomain::FModelTask>> FEzStoreContentModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStoreContentModelDomain::Subscribe(TFunction<void(Gs2::UE5::Money2::Model::FEzStoreContentModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [Callback](Gs2::Money2::Model::FStoreContentModelPtr Item)
            {
                Callback(Gs2::UE5::Money2::Model::FEzStoreContentModel::FromModel(Item));
            }
        );
    }

    void FEzStoreContentModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
