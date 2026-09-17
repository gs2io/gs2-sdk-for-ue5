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

#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/Namespace.h"
#include "Ranking/Domain/Model/CategoryModel.h"
#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Subscribe.h"
#include "Ranking/Domain/Model/SubscribeAccessToken.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/CurrentRankingMaster.h"
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"
#include "Ranking/Model/Cache/Subscribe.h"
#include "Ranking/Model/Cache/SubscribeUser.h"
#include "Ranking/Model/Cache/Ranking.h"
#include "Ranking/Model/Cache/Score.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FRankingCategoryDomain::FRankingCategoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Ranking::Domain::FGs2RankingDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CategoryName,
        const TOptional<FString> AdditionalScopeName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CategoryName(CategoryName),
        AdditionalScopeName(AdditionalScopeName),
        ParentKey(Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "RankingCategory"
        ))
    {
    }

    FRankingCategoryDomain::FRankingCategoryDomain(
        const FRankingCategoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CategoryName(From.CategoryName),
        AdditionalScopeName(From.AdditionalScopeName),
        ParentKey(From.ParentKey)
    {

    }

    FRankingCategoryDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FRankingCategoryDomain>& Self,
        const Request::FSubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingCategoryDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SubscribeByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Ranking::Model::Cache::FSubscribeUserCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetCategoryName(),
            TOptional<FString>(),
            ResultModel->GetItem()->GetTargetUserId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetCategoryName(),
            Self->AdditionalScopeName,
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FSubscribeTask>> FRankingCategoryDomain::Subscribe(
        Request::FSubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    FRankingCategoryDomain::FPutScoreTask::FPutScoreTask(
        const TSharedPtr<FRankingCategoryDomain>& Self,
        const Request::FPutScoreByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRankingCategoryDomain::FPutScoreTask::FPutScoreTask(
        const FPutScoreTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FPutScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FScoreDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PutScoreByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Ranking::Model::Cache::FScoreCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetScorerUserId(),
            Request->GetCategoryName(),
            ResultModel->GetItem()->GetUniqueId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Ranking::Domain::Model::FScoreDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetCategoryName(),
            ResultModel->GetItem()->GetScorerUserId(),
            ResultModel->GetItem()->GetUniqueId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FPutScoreTask>> FRankingCategoryDomain::PutScore(
        Request::FPutScoreByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutScoreTask>>(this->AsShared(), Request);
    }

    Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIteratorPtr FRankingCategoryDomain::SubscribesByCategoryName(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeSubscribesByCategoryName(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                TOptional<FString>(),
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRankingCategoryDomain::UnsubscribeSubscribesByCategoryName(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                TOptional<FString>(),
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRankingCategoryDomain::FCollectSubscribesByCategoryNameTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>, public TSharedFromThis<FCollectSubscribesByCategoryNameTask>
    {
        const TSharedPtr<FRankingCategoryDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking::Model::FSubscribeUserPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectSubscribesByCategoryNameTask(const TSharedPtr<FRankingCategoryDomain>& Self, TFunction<void(TArray<Gs2::Ranking::Model::FSubscribeUserPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectSubscribesByCategoryNameTask(const FCollectSubscribesByCategoryNameTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>> Result) override
        {
            TArray<Gs2::Ranking::Model::FSubscribeUserPtr> Items;
            auto Iterator = Self->SubscribesByCategoryName(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeSubscribesByCategoryName(
        TFunction<void(TArray<Gs2::Ranking::Model::FSubscribeUserPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking::Domain::FGs2RankingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryCategoryName = CategoryName;
        const auto QueryAdditionalScopeName = AdditionalScopeName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        CategoryName,
        TOptional<FString>(),
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking::Model::FSubscribeUserPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking::Model::FSubscribeUser>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FRankingCategoryDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesByCategoryNameTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRankingCategoryDomain::InvalidateSubscribesByCategoryName(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking::Model::FSubscribeUser::TypeName,
            Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        CategoryName,
        TOptional<FString>(),
        TOptional<int32>()
    )
        );
    }

    FRankingCategoryDomain::FSubscribeSubscribesByCategoryNameWithInitialCallTask::FSubscribeSubscribesByCategoryNameWithInitialCallTask(const TSharedPtr<FRankingCategoryDomain>& Self, TFunction<void(TArray<Gs2::Ranking::Model::FSubscribeUserPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FRankingCategoryDomain::FSubscribeSubscribesByCategoryNameWithInitialCallTask::FSubscribeSubscribesByCategoryNameWithInitialCallTask(const FSubscribeSubscribesByCategoryNameWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FSubscribeSubscribesByCategoryNameWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesByCategoryNameTask>>(Self, TFunction<void(TArray<Gs2::Ranking::Model::FSubscribeUserPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscribesByCategoryName(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FSubscribeSubscribesByCategoryNameWithInitialCallTask>> FRankingCategoryDomain::SubscribeSubscribesByCategoryNameWithInitialCall(TFunction<void(TArray<Gs2::Ranking::Model::FSubscribeUserPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscribesByCategoryNameWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FSubscribeUserDomain> FRankingCategoryDomain::SubscribeUser(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FSubscribeUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIteratorPtr FRankingCategoryDomain::Rankings(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeRankingsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            CategoryName,
            UserId,
            AdditionalScopeName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeRankings(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                AdditionalScopeName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRankingCategoryDomain::UnsubscribeRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                CategoryName,
                AdditionalScopeName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRankingCategoryDomain::FCollectRankingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking::Model::FRankingPtr>>, public TSharedFromThis<FCollectRankingsTask>
    {
        const TSharedPtr<FRankingCategoryDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectRankingsTask(const TSharedPtr<FRankingCategoryDomain>& Self, TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectRankingsTask(const FCollectRankingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking::Model::FRankingPtr>>> Result) override
        {
            TArray<Gs2::Ranking::Model::FRankingPtr> Items;
            auto Iterator = Self->Rankings(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking::Model::FRankingPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeRankings(
        TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking::Domain::FGs2RankingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryCategoryName = CategoryName;
        const auto QueryAdditionalScopeName = AdditionalScopeName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        CategoryName,
        AdditionalScopeName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking::Model::FRanking::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking::Model::FRankingPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking::Model::FRanking>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FRankingCategoryDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRankingsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRankingCategoryDomain::InvalidateRankings(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        CategoryName,
        AdditionalScopeName,
        TOptional<int32>()
    )
        );
    }

    FRankingCategoryDomain::FSubscribeRankingsWithInitialCallTask::FSubscribeRankingsWithInitialCallTask(const TSharedPtr<FRankingCategoryDomain>& Self, TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FRankingCategoryDomain::FSubscribeRankingsWithInitialCallTask::FSubscribeRankingsWithInitialCallTask(const FSubscribeRankingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FSubscribeRankingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRankingsTask>>(Self, TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRankings(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FSubscribeRankingsWithInitialCallTask>> FRankingCategoryDomain::SubscribeRankingsWithInitialCall(TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRankingsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIteratorPtr FRankingCategoryDomain::NearRankings(
        const int64 Score
    ) const
    {
        return MakeShared<Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator>(
            Gs2,
            Client,
            NamespaceName,
            CategoryName,
            Score,
            AdditionalScopeName
        );
    }

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeNearRankings(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>(),
                CategoryName,
                AdditionalScopeName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRankingCategoryDomain::UnsubscribeNearRankings(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>(),
                CategoryName,
                AdditionalScopeName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRankingCategoryDomain::FCollectNearRankingsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking::Model::FRankingPtr>>, public TSharedFromThis<FCollectNearRankingsTask>
    {
        const TSharedPtr<FRankingCategoryDomain> Self;
        const TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> OnCollected;
    const int64 QueryScore;
    public:
        explicit FCollectNearRankingsTask(const TSharedPtr<FRankingCategoryDomain>& Self, TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> OnCollected,const int64 Score) : Self(Self), OnCollected(OnCollected), QueryScore(Score) {}
        FCollectNearRankingsTask(const FCollectNearRankingsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryScore(From.QueryScore) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Ranking::Model::FRankingPtr>>> Result) override
        {
            TArray<Gs2::Ranking::Model::FRankingPtr> Items;
            auto Iterator = Self->NearRankings(QueryScore)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Ranking::Model::FRankingPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FRankingCategoryDomain::SubscribeNearRankings(
        TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> Callback,const int64 Score
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Ranking::Domain::FGs2RankingDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryCategoryName = CategoryName;
        const auto QueryAdditionalScopeName = AdditionalScopeName;
        const auto QueryScore = Score;
        const auto Parent = Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<FString>(),
        CategoryName,
        AdditionalScopeName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Ranking::Model::FRanking::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Ranking::Model::FRankingPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Ranking::Model::FRanking>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName, QueryScore]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FRankingCategoryDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryCategoryName, QueryAdditionalScopeName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNearRankingsTask>>(Domain, Callback, QueryScore);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRankingCategoryDomain::InvalidateNearRankings(const int64 Score)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Ranking::Model::FRanking::TypeName,
            Gs2::Ranking::Model::Cache::FRankingCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<FString>(),
        CategoryName,
        AdditionalScopeName,
        TOptional<int32>()
    )
        );
    }

    FRankingCategoryDomain::FSubscribeNearRankingsWithInitialCallTask::FSubscribeNearRankingsWithInitialCallTask(const TSharedPtr<FRankingCategoryDomain>& Self, TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> Callback,const int64 Score) : Self(Self), Callback(Callback), QueryScore(Score) {}
    FRankingCategoryDomain::FSubscribeNearRankingsWithInitialCallTask::FSubscribeNearRankingsWithInitialCallTask(const FSubscribeNearRankingsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryScore(From.QueryScore) {}
    Gs2::Core::Model::FGs2ErrorPtr FRankingCategoryDomain::FSubscribeNearRankingsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNearRankingsTask>>(Self, TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)>(), QueryScore);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNearRankings(Callback, QueryScore);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRankingCategoryDomain::FSubscribeNearRankingsWithInitialCallTask>> FRankingCategoryDomain::SubscribeNearRankingsWithInitialCall(TFunction<void(TArray<Gs2::Ranking::Model::FRankingPtr>)> Callback,const int64 Score)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNearRankingsWithInitialCallTask>>(this->AsShared(), Callback, Score);
    }

    TSharedPtr<Gs2::Ranking::Domain::Model::FRankingDomain> FRankingCategoryDomain::Ranking(
        const TOptional<FString> ScorerUserId,
        const TOptional<int64> Index
    )
    {
        return MakeShared<Gs2::Ranking::Domain::Model::FRankingDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            CategoryName,
            AdditionalScopeName,
            ScorerUserId,
            Index
        );
    }

    FString FRankingCategoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null") + ":" +
            ChildType;
    }

    FString FRankingCategoryDomain::CreateCacheKey(
        TOptional<FString> CategoryName,
        TOptional<FString> AdditionalScopeName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            (AdditionalScopeName.IsSet() ? *AdditionalScopeName : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
