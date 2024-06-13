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

#include "Ranking2/Domain/Model/Gs2Ranking2EzNamespaceDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzNamespaceDomain::UploadToken() const
    {
        return Domain->UploadToken;
    }

    TOptional<FString> FEzNamespaceDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
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
        Gs2::Ranking2::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingModelsIteratorPtr FEzNamespaceDomain::GlobalRankingModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeGlobalRankingModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeGlobalRankingModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeGlobalRankingModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeGlobalRankingModels(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingModelDomainPtr FEzNamespaceDomain::GlobalRankingModel(
        const FString RankingName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingModelDomain>(
            Domain->GlobalRankingModel(
                RankingName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingModelsIteratorPtr FEzNamespaceDomain::SubscribeRankingModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeSubscribeRankingModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscribeRankingModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeSubscribeRankingModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscribeRankingModels(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingModelDomainPtr FEzNamespaceDomain::SubscribeRankingModel(
        const FString RankingName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingModelDomain>(
            Domain->SubscribeRankingModel(
                RankingName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingModelsIteratorPtr FEzNamespaceDomain::ClusterRankingModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeClusterRankingModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeClusterRankingModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeClusterRankingModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeClusterRankingModels(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingModelDomainPtr FEzNamespaceDomain::ClusterRankingModel(
        const FString RankingName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingModelDomain>(
            Domain->ClusterRankingModel(
                RankingName
            ),
            ConnectionValue
        );
    }
}
