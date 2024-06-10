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

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeUserDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzSubscribeUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSubscribeUserDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<FString> FEzSubscribeUserDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzSubscribeUserDomain::FEzSubscribeUserDomain(
        Gs2::Ranking2::Domain::Model::FSubscribeUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzSubscribeUserDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSubscribeUserDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeUserDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzSubscribeUserPtr> Result
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
                *Result = Gs2::UE5::Ranking2::Model::FEzSubscribeUser::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSubscribeUserDomain::FModelTask>> FEzSubscribeUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeUserDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzSubscribeUserPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FSubscribeUserPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzSubscribeUser::FromModel(Item));
            }
        );
    }

    void FEzSubscribeUserDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
