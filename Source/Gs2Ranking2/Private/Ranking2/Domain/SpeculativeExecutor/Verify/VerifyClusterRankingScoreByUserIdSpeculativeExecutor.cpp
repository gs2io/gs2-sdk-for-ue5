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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Ranking2/Domain/SpeculativeExecutor/Verify/VerifyClusterRankingScoreByUserIdSpeculativeExecutor.h"
#include "Ranking2/Model/Cache/ClusterRankingScore.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"
namespace Gs2::Ranking2::Domain::SpeculativeExecutor
{
namespace
{
    bool Ranking2VerifyClusterPredicate(const Gs2::Ranking2::Model::FClusterRankingScorePtr& Item, const FString& ExpectedId, const FString& UserId,
        const FString& RankingName, const FString& ClusterName, const int64 ExpectedSeason, const TOptional<int64>& RequestSeason,
        const FString& VerifyType, const int64 RequestValue)
    {
        if (!Item.IsValid() || !Item->GetClusterRankingScoreId().IsSet() || Item->GetClusterRankingScoreId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetRankingName().IsSet() || Item->GetRankingName().Get(FString()) != RankingName ||
            !Item->GetClusterName().IsSet() || Item->GetClusterName().Get(FString()) != ClusterName ||
            !Item->GetSeason().IsSet() || Item->GetSeason().Get(0) != ExpectedSeason || !Item->GetScore().IsSet() ||
            (RequestSeason.IsSet() && Item->GetSeason().Get(0) != RequestSeason.Get(0))) return false;
        const int64 Current = Item->GetScore().Get(0);
        if (VerifyType == TEXT("less")) return Current < RequestValue;
        if (VerifyType == TEXT("lessEqual")) return Current <= RequestValue;
        if (VerifyType == TEXT("greater")) return Current > RequestValue;
        if (VerifyType == TEXT("greaterEqual")) return Current >= RequestValue;
        if (VerifyType == TEXT("equal")) return Current == RequestValue;
        if (VerifyType == TEXT("notEqual")) return Current != RequestValue;
        return false;
    }

    FString Ranking2ClusterFailureReason(const FString& VerifyType)
    {
        if (VerifyType == TEXT("less")) return TEXT("greaterEqual");
        if (VerifyType == TEXT("lessEqual")) return TEXT("greater");
        if (VerifyType == TEXT("greater")) return TEXT("lessEqual");
        if (VerifyType == TEXT("greaterEqual")) return TEXT("less");
        if (VerifyType == TEXT("equal")) return TEXT("notEqual");
        if (VerifyType == TEXT("notEqual")) return TEXT("equal");
        return TEXT("invalid");
    }
}
    FString FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Ranking2:VerifyClusterRankingScoreByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr&,
        Gs2::Ranking2::Model::FClusterRankingScorePtr
    )
    {
        return nullptr;
    }

    FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr& Request
    ):
        Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
    {

    }

    FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
        Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || Domain->RestSession->OwnerId().IsEmpty() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() || !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}")) PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) || !PreparedRequest->GetScore().IsSet() || !PreparedRequest->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("less") && VerifyType != TEXT("lessEqual") && VerifyType != TEXT("greater") && VerifyType != TEXT("greaterEqual") && VerifyType != TEXT("equal") && VerifyType != TEXT("notEqual")) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString()), RankingName = PreparedRequest->GetRankingName().Get(FString()), ClusterName = PreparedRequest->GetClusterName().Get(FString()), UserId = PreparedRequest->GetUserId().Get(FString()); const TOptional<int64> RequestSeason = PreparedRequest->GetSeason(); const int64 RequestValue = PreparedRequest->GetScore().Get(0); const auto TimeOffset = PreparedToken->GetTimeOffset();
        Gs2::Ranking2::Model::FClusterRankingScorePtr Cached;
        if (!Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::TryGet(Domain->Cache, NamespaceName, RankingName, ClusterName, RequestSeason, UserId, TimeOffset, &Cached) || !Cached.IsValid() || !Cached->GetSeason().IsSet()) return nullptr;
        const int64 ExpectedSeason = Cached->GetSeason().Get(0);
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:ranking2:%s:user:%s:cluster:%s:%s:%lld:score"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *RankingName, *ClusterName, Cached->GetSeason().Get(0));
        if (!Ranking2VerifyClusterPredicate(Cached, ExpectedId, UserId, RankingName, ClusterName, ExpectedSeason, RequestSeason, VerifyType, RequestValue))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
                TEXT("score"),
                FString::Printf(TEXT("ranking2.clusterRankingScore.score.error.%s"), *Ranking2ClusterFailureReason(VerifyType)),
                TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, RankingName, ClusterName, RequestSeason, UserId, TimeOffset, ExpectedId, ExpectedSeason, VerifyType, RequestValue]()
        {
            Gs2::Ranking2::Model::FClusterRankingScorePtr Current;
            if (!Gs2::Ranking2::Model::Cache::FClusterRankingScoreCache::TryGet(Cache, NamespaceName, RankingName, ClusterName, RequestSeason, UserId, TimeOffset, &Current) || !Current.IsValid()) return false;
            return Ranking2VerifyClusterPredicate(Current, ExpectedId, UserId, RankingName, ClusterName, ExpectedSeason, RequestSeason, VerifyType, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::FCommitTask>> FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::FCommitTask>> FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Ranking2::Domain::FGs2Ranking2DomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = Inverse->GetVerifyType().Get(FString());
        if (VerifyType == TEXT("less")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greaterEqual")));
        else if (VerifyType == TEXT("lessEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greater")));
        else if (VerifyType == TEXT("greater")) Inverse->WithVerifyType(TOptional<FString>(TEXT("lessEqual")));
        else if (VerifyType == TEXT("greaterEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("less")));
        else if (VerifyType == TEXT("equal")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notEqual")));
        else if (VerifyType == TEXT("notEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("equal")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::Rate(
        const Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false)) return Request;
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetScore().Get(1), Rate, Value)) return Request;
        Request->WithScore(Value);
        return Request;
    }

    Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr FVerifyClusterRankingScoreByUserIdSpeculativeExecutor::Rate(
        const Gs2::Ranking2::Request::FVerifyClusterRankingScoreByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false)) return Request;
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetScore().Get(1), Rate, Value)) return Request;
        Request->WithScore(Value);
        return Request;
    }
}
