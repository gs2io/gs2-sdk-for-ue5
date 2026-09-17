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

#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Domain/Model/LotteryModelMaster.h"
#include "Lottery/Domain/Model/PrizeTableMaster.h"
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/ProbabilityAccessToken.h"
#include "Lottery/Domain/Model/CurrentLotteryMaster.h"
#include "Lottery/Domain/Model/PrizeLimit.h"
#include "Lottery/Domain/Model/BoxItems.h"
#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Domain/Model/User.h"
#include "Lottery/Domain/Model/UserAccessToken.h"
#include "Lottery/Domain/SpeculativeExecutor/Transaction/DrawByUserIdSpeculativeExecutor.h"
#include "Lottery/Domain/SpeculativeExecutor/Transaction/DrawWithRandomSeedByUserIdSpeculativeExecutor.h"

#include "Lottery/Model/Cache/Probability.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FLotteryAccessTokenDomain::FLotteryAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> LotteryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        LotteryName(LotteryName),
        ParentKey(Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Lottery"
        ))
    {
    }

    FLotteryAccessTokenDomain::FLotteryAccessTokenDomain(
        const FLotteryAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        LotteryName(From.LotteryName),
        ParentKey(From.ParentKey)
    {

    }

    FLotteryAccessTokenDomain::FPredictionTask::FPredictionTask(
        const TSharedPtr<FLotteryAccessTokenDomain>& Self,
        const Request::FPredictionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryAccessTokenDomain::FPredictionTask::FPredictionTask(
        const FPredictionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryAccessTokenDomain::FPredictionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Lottery::Model::FDrawnPrize>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithLotteryName(Self->LotteryName);
        const auto Future = Self->Client->Prediction(
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
            
        }
        *Result = ResultModel->GetItems();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryAccessTokenDomain::FPredictionTask>> FLotteryAccessTokenDomain::Prediction(
        Request::FPredictionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPredictionTask>>(this->AsShared(), Request);
    }

    Gs2::Lottery::Domain::Iterator::FDescribeProbabilitiesIteratorPtr FLotteryAccessTokenDomain::Probabilities(
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribeProbabilitiesIterator>(
            Gs2,
            Client,
            NamespaceName,
            LotteryName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FLotteryAccessTokenDomain::SubscribeProbabilities(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                LotteryName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FLotteryAccessTokenDomain::UnsubscribeProbabilities(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                LotteryName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FLotteryAccessTokenDomain::FCollectProbabilitiesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Lottery::Model::FProbabilityPtr>>, public TSharedFromThis<FCollectProbabilitiesTask>
    {
        const TSharedPtr<FLotteryAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> OnCollected;

    public:
        explicit FCollectProbabilitiesTask(const TSharedPtr<FLotteryAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectProbabilitiesTask(const FCollectProbabilitiesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Lottery::Model::FProbabilityPtr>>> Result) override
        {
            TArray<Gs2::Lottery::Model::FProbabilityPtr> Items;
            auto Iterator = Self->Probabilities()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Lottery::Model::FProbabilityPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FLotteryAccessTokenDomain::SubscribeProbabilities(
        TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryLotteryName = LotteryName;
        const auto Parent = Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        LotteryName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Lottery::Model::FProbability::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Lottery::Model::FProbabilityPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Lottery::Model::FProbability>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryLotteryName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FLotteryAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot, QueryLotteryName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectProbabilitiesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FLotteryAccessTokenDomain::InvalidateProbabilities()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        LotteryName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FLotteryAccessTokenDomain::FSubscribeProbabilitiesWithInitialCallTask::FSubscribeProbabilitiesWithInitialCallTask(const TSharedPtr<FLotteryAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FLotteryAccessTokenDomain::FSubscribeProbabilitiesWithInitialCallTask::FSubscribeProbabilitiesWithInitialCallTask(const FSubscribeProbabilitiesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FLotteryAccessTokenDomain::FSubscribeProbabilitiesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectProbabilitiesTask>>(Self, TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeProbabilities(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FLotteryAccessTokenDomain::FSubscribeProbabilitiesWithInitialCallTask>> FLotteryAccessTokenDomain::SubscribeProbabilitiesWithInitialCall(TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeProbabilitiesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    FString FLotteryAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> LotteryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (LotteryName.IsSet() ? *LotteryName : "null") + ":" +
            ChildType;
    }

    FString FLotteryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> LotteryName
    )
    {
        return FString("") +
            (LotteryName.IsSet() ? *LotteryName : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

