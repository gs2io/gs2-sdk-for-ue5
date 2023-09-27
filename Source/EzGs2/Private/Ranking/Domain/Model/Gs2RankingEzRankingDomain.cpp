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
 *
 * deny overwrite
 */

#include "Ranking/Domain/Model/Gs2RankingEzRankingDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzRankingDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRankingDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzRankingDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    FEzRankingDomain::FEzRankingDomain(
        Gs2::Ranking::Domain::Model::FRankingDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRankingDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRankingDomain> Self,
        FString ScorerUserId
    ): Self(Self), ScorerUserId(ScorerUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRankingDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking::Model::FEzRankingPtr> Result
    )
    {
        const auto Future = Self->Domain->Model(ScorerUserId);
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        *Result = Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Future->GetTask().Result());
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzRankingDomain::FModelTask>> FEzRankingDomain::Model(
        FString ScorerUserId
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared(), ScorerUserId);
    }
    
    Gs2::Core::Domain::CallbackID FEzRankingDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking::Model::FEzRankingPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking::Model::FRankingPtr Item)
            {
                Callback(Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Item));
            }
        );
    }

    void FEzRankingDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
