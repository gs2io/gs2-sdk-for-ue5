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

#include "Mission/Domain/Model/Gs2MissionEzNamespaceDomain.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzNamespaceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzNamespaceDomain::FEzNamespaceDomain(
        Gs2::Mission::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    Gs2::UE5::Mission::Domain::Iterator::FEzDescribeMissionGroupModelsIteratorPtr FEzNamespaceDomain::MissionGroupModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Iterator::FEzDescribeMissionGroupModelsIterator>(
            Domain->MissionGroupModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeMissionGroupModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeMissionGroupModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeMissionGroupModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeMissionGroupModels(
            CallbackId
        );
    }

    Gs2::UE5::Mission::Domain::Model::FEzMissionGroupModelDomainPtr FEzNamespaceDomain::MissionGroupModel(
        const FString MissionGroupName
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Model::FEzMissionGroupModelDomain>(
            Domain->MissionGroupModel(
                MissionGroupName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Mission::Domain::Iterator::FEzDescribeCounterModelsIteratorPtr FEzNamespaceDomain::CounterModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Iterator::FEzDescribeCounterModelsIterator>(
            Domain->CounterModels(
            )
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeCounterModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeCounterModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeCounterModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeCounterModels(
            CallbackId
        );
    }

    Gs2::UE5::Mission::Domain::Model::FEzCounterModelDomainPtr FEzNamespaceDomain::CounterModel(
        const FString CounterName
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Model::FEzCounterModelDomain>(
            Domain->CounterModel(
                CounterName
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Mission::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Mission::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::UE5::Mission::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                AccessToken->ToModel()
            ),
            ProfileValue
        );
    }
}
