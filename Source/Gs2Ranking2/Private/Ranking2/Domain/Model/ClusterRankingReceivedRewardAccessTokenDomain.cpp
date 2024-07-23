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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Ranking2/Domain/Model/ClusterRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedReward.h"
#include "Ranking2/Domain/Model/Namespace.h"
#include "Ranking2/Domain/Model/GlobalRankingModel.h"
#include "Ranking2/Domain/Model/GlobalRankingModelMaster.h"
#include "Ranking2/Domain/Model/GlobalRankingScore.h"
#include "Ranking2/Domain/Model/GlobalRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingReceivedReward.h"
#include "Ranking2/Domain/Model/GlobalRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingSeason.h"
#include "Ranking2/Domain/Model/GlobalRankingData.h"
#include "Ranking2/Domain/Model/GlobalRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingModel.h"
#include "Ranking2/Domain/Model/ClusterRankingModelMaster.h"
#include "Ranking2/Domain/Model/ClusterRankingScore.h"
#include "Ranking2/Domain/Model/ClusterRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedReward.h"
#include "Ranking2/Domain/Model/ClusterRankingReceivedRewardAccessToken.h"
#include "Ranking2/Domain/Model/ClusterRankingSeason.h"
#include "Ranking2/Domain/Model/ClusterRankingData.h"
#include "Ranking2/Domain/Model/ClusterRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingModel.h"
#include "Ranking2/Domain/Model/SubscribeRankingModelMaster.h"
#include "Ranking2/Domain/Model/SubscribeRankingSeason.h"
#include "Ranking2/Domain/Model/SubscribeRankingSeasonAccessToken.h"
#include "Ranking2/Domain/Model/Subscribe.h"
#include "Ranking2/Domain/Model/SubscribeAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingScore.h"
#include "Ranking2/Domain/Model/SubscribeRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/SubscribeRankingData.h"
#include "Ranking2/Domain/Model/SubscribeRankingDataAccessToken.h"
#include "Ranking2/Domain/Model/CurrentRankingMaster.h"
#include "Ranking2/Domain/Model/SubscribeUser.h"
#include "Ranking2/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking2/Domain/Model/User.h"
#include "Ranking2/Domain/Model/UserAccessToken.h"
#include "Ranking2/Domain/SpeculativeExecutor/Transaction/ReceiveClusterRankingReceivedRewardByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FClusterRankingReceivedRewardAccessTokenDomain::FClusterRankingReceivedRewardAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RankingName(RankingName),
        ClusterName(ClusterName),
        Season(Season),
        ParentKey(Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "ClusterRankingReceivedReward"
        ))
    {
    }

    FClusterRankingReceivedRewardAccessTokenDomain::FClusterRankingReceivedRewardAccessTokenDomain(
        const FClusterRankingReceivedRewardAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RankingName(From.RankingName),
        ClusterName(From.ClusterName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    FClusterRankingReceivedRewardAccessTokenDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FClusterRankingReceivedRewardAccessTokenDomain>& Self,
        const Request::FCreateClusterRankingReceivedRewardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingReceivedRewardAccessTokenDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingReceivedRewardAccessTokenDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->CreateClusterRankingReceivedReward(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "ClusterRankingReceivedReward"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetClusterName(),
                    ResultModel->GetItem()->GetSeason().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSeason()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingReceivedRewardAccessTokenDomain::FCreateTask>> FClusterRankingReceivedRewardAccessTokenDomain::Create(
        Request::FCreateClusterRankingReceivedRewardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FClusterRankingReceivedRewardAccessTokenDomain::FReceiveTask::FReceiveTask(
        const TSharedPtr<FClusterRankingReceivedRewardAccessTokenDomain>& Self,
        const Request::FReceiveClusterRankingReceivedRewardRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FClusterRankingReceivedRewardAccessTokenDomain::FReceiveTask::FReceiveTask(
        const FReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingReceivedRewardAccessTokenDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithSeason(Self->Season);

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FReceiveClusterRankingReceivedRewardByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FReceiveClusterRankingReceivedRewardByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->ReceiveClusterRankingReceivedReward(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "ClusterRankingModel"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingReceivedRewardAccessTokenDomain::FReceiveTask>> FClusterRankingReceivedRewardAccessTokenDomain::Receive(
        Request::FReceiveClusterRankingReceivedRewardRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FClusterRankingReceivedRewardAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FClusterRankingReceivedRewardAccessTokenDomain>& Self,
        const Request::FGetClusterRankingReceivedRewardRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FClusterRankingReceivedRewardAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingReceivedRewardAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingReceivedReward>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithClusterName(Self->ClusterName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetClusterRankingReceivedReward(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "ClusterRankingReceivedReward"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetClusterName(),
                    ResultModel->GetItem()->GetSeason().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSeason()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingReceivedRewardAccessTokenDomain::FGetTask>> FClusterRankingReceivedRewardAccessTokenDomain::Get(
        Request::FGetClusterRankingReceivedRewardRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FClusterRankingReceivedRewardAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RankingName,
        TOptional<FString> ClusterName,
        TOptional<FString> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" +
            (Season.IsSet() ? *Season : "null") + ":" +
            ChildType;
    }

    FString FClusterRankingReceivedRewardAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RankingName,
        TOptional<FString> ClusterName,
        TOptional<FString> Season
    )
    {
        return FString("") +
            (RankingName.IsSet() ? *RankingName : "null") + ":" + 
            (ClusterName.IsSet() ? *ClusterName : "null") + ":" + 
            (Season.IsSet() ? *Season : "null");
    }

    FClusterRankingReceivedRewardAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FClusterRankingReceivedRewardAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FClusterRankingReceivedRewardAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FClusterRankingReceivedRewardAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingReceivedReward>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking2::Model::FClusterRankingReceivedReward> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FClusterRankingReceivedReward>(
            Self->ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                Self->RankingName,
                Self->ClusterName,
                Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking2::Request::FGetClusterRankingReceivedRewardRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                    Self->RankingName,
                    Self->ClusterName,
                    Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "clusterRankingReceivedReward")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FClusterRankingReceivedReward>(
                Self->ParentKey,
                Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                    Self->RankingName,
                    Self->ClusterName,
                    Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FClusterRankingReceivedRewardAccessTokenDomain::FModelTask>> FClusterRankingReceivedRewardAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FClusterRankingReceivedRewardAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FClusterRankingReceivedRewardAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                RankingName,
                ClusterName,
                Season.IsSet() ? FString::FromInt(*Season) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FClusterRankingReceivedReward>(obj));
            }
        );
    }

    void FClusterRankingReceivedRewardAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FClusterRankingReceivedReward::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardDomain::CreateCacheKey(
                RankingName,
                ClusterName,
                Season.IsSet() ? FString::FromInt(*Season) : TOptional<FString>()
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

