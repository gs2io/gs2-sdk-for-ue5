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

#include "SeasonRating/Domain/Model/Gs2SeasonRatingEzSeasonModelDomain.h"

namespace Gs2::UE5::SeasonRating::Domain::Model
{

    TOptional<FString> FEzSeasonModelDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSeasonModelDomain::SeasonName() const
    {
        return Domain->SeasonName;
    }

    FEzSeasonModelDomain::FEzSeasonModelDomain(
        Gs2::SeasonRating::Domain::Model::FSeasonModelDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzSeasonModelDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSeasonModelDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSeasonModelDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr> Result
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
                *Result = Gs2::UE5::SeasonRating::Model::FEzSeasonModel::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSeasonModelDomain::FModelTask>> FEzSeasonModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSeasonModelDomain::Subscribe(TFunction<void(Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::SeasonRating::Model::FSeasonModelPtr Item)
            {
                Callback(Gs2::UE5::SeasonRating::Model::FEzSeasonModel::FromModel(Item));
            }
        );
    }

    void FEzSeasonModelDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
