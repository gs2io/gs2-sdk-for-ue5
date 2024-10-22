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

#include "Ranking2/Domain/Model/GlobalRankingScoreAccessToken.h"
#include "Ranking2/Domain/Model/GlobalRankingScore.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Ranking2::Domain::Model
{

    FGlobalRankingScoreAccessTokenDomain::FGlobalRankingScoreAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RankingName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking2::FGs2Ranking2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RankingName(RankingName),
        Season(Season),
        ParentKey(Gs2::Ranking2::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "GlobalRankingScore"
        ))
    {
    }

    FGlobalRankingScoreAccessTokenDomain::FGlobalRankingScoreAccessTokenDomain(
        const FGlobalRankingScoreAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RankingName(From.RankingName),
        Season(From.Season),
        ParentKey(From.ParentKey)
    {

    }

    FGlobalRankingScoreAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FGlobalRankingScoreAccessTokenDomain>& Self,
        const Request::FGetGlobalRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalRankingScoreAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingScoreAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FGlobalRankingScore>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRankingName(Self->RankingName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->GetGlobalRankingScore(
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
                    "GlobalRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetSeason().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSeason()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
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

    TSharedPtr<FAsyncTask<FGlobalRankingScoreAccessTokenDomain::FGetTask>> FGlobalRankingScoreAccessTokenDomain::Get(
        Request::FGetGlobalRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGlobalRankingScoreAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FGlobalRankingScoreAccessTokenDomain>& Self,
        const Request::FVerifyGlobalRankingScoreRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalRankingScoreAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingScoreAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Domain::Model::FGlobalRankingScoreAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRankingName(Self->RankingName)
            ->WithSeason(Self->Season);
        const auto Future = Self->Client->VerifyGlobalRankingScore(
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
                    "GlobalRankingScore"
                );
                const auto Key = Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRankingName(),
                    ResultModel->GetItem()->GetSeason().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetSeason()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
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

    TSharedPtr<FAsyncTask<FGlobalRankingScoreAccessTokenDomain::FVerifyTask>> FGlobalRankingScoreAccessTokenDomain::Verify(
        Request::FVerifyGlobalRankingScoreRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FGlobalRankingScoreAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RankingName,
        TOptional<FString> Season,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RankingName.IsSet() ? *RankingName : "null") + ":" +
            (Season.IsSet() ? *Season : "null") + ":" +
            ChildType;
    }

    FString FGlobalRankingScoreAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RankingName,
        TOptional<FString> Season
    )
    {
        return FString("") +
            (RankingName.IsSet() ? *RankingName : "null") + ":" + 
            (Season.IsSet() ? *Season : "null");
    }

    FGlobalRankingScoreAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FGlobalRankingScoreAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FGlobalRankingScoreAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalRankingScoreAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FGlobalRankingScore>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking2::Model::FGlobalRankingScore> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FGlobalRankingScore>(
            Self->ParentKey,
            Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                Self->RankingName,
                Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking2::Request::FGetGlobalRankingScoreRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                    Self->RankingName,
                    Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "globalRankingScore")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Ranking2::Model::FGlobalRankingScore>(
                Self->ParentKey,
                Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                    Self->RankingName,
                    Self->Season.IsSet() ? FString::FromInt(*Self->Season) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalRankingScoreAccessTokenDomain::FModelTask>> FGlobalRankingScoreAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGlobalRankingScoreAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FGlobalRankingScoreAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Ranking2::Model::FGlobalRankingScorePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                RankingName,
                Season.IsSet() ? FString::FromInt(*Season) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking2::Model::FGlobalRankingScore>(obj));
            }
        );
    }

    void FGlobalRankingScoreAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Ranking2::Model::FGlobalRankingScore::TypeName,
            ParentKey,
            Gs2::Ranking2::Domain::Model::FGlobalRankingScoreDomain::CreateCacheKey(
                RankingName,
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

