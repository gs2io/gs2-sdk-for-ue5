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

#include "Lottery/Model/Cache/Probability.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FLotteryDomain::FLotteryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> LotteryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        LotteryName(LotteryName),
        ParentKey(Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Lottery"
        ))
    {
    }

    FLotteryDomain::FLotteryDomain(
        const FLotteryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        LotteryName(From.LotteryName),
        ParentKey(From.ParentKey)
    {

    }

    FLotteryDomain::FDrawTask::FDrawTask(
        const TSharedPtr<FLotteryDomain>& Self,
        const Request::FDrawByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryDomain::FDrawTask::FDrawTask(
        const FDrawTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FDrawTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLotteryName(Self->LotteryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DrawByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            ResultModel->GetTransactionId().IsSet() ? *ResultModel->GetTransactionId() : FString(),
            ResultModel->GetStampSheet().IsSet() ? *ResultModel->GetStampSheet() : FString(),
            ResultModel->GetStampSheetEncryptionKeyId().IsSet() ? *ResultModel->GetStampSheetEncryptionKeyId() : FString(),
            ResultModel->GetAtomicCommit().IsSet() ? *ResultModel->GetAtomicCommit() : false,
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryDomain::FDrawTask>> FLotteryDomain::Draw(
        Request::FDrawByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDrawTask>>(this->AsShared(), Request);
    }

    FLotteryDomain::FPredictionTask::FPredictionTask(
        const TSharedPtr<FLotteryDomain>& Self,
        const Request::FPredictionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryDomain::FPredictionTask::FPredictionTask(
        const FPredictionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FPredictionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Lottery::Model::FDrawnPrize>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLotteryName(Self->LotteryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PredictionByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        *Result = ResultModel->GetItems();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryDomain::FPredictionTask>> FLotteryDomain::Prediction(
        Request::FPredictionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPredictionTask>>(this->AsShared(), Request);
    }

    FLotteryDomain::FDrawWithRandomSeedTask::FDrawWithRandomSeedTask(
        const TSharedPtr<FLotteryDomain>& Self,
        const Request::FDrawWithRandomSeedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryDomain::FDrawWithRandomSeedTask::FDrawWithRandomSeedTask(
        const FDrawWithRandomSeedTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FDrawWithRandomSeedTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLotteryName(Self->LotteryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DrawWithRandomSeedByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            ResultModel->GetTransactionId().IsSet() ? *ResultModel->GetTransactionId() : FString(),
            ResultModel->GetStampSheet().IsSet() ? *ResultModel->GetStampSheet() : FString(),
            ResultModel->GetStampSheetEncryptionKeyId().IsSet() ? *ResultModel->GetStampSheetEncryptionKeyId() : FString(),
            ResultModel->GetAtomicCommit().IsSet() ? *ResultModel->GetAtomicCommit() : false,
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryDomain::FDrawWithRandomSeedTask>> FLotteryDomain::DrawWithRandomSeed(
        Request::FDrawWithRandomSeedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDrawWithRandomSeedTask>>(this->AsShared(), Request);
    }

    Gs2::Lottery::Domain::Iterator::FDescribeProbabilitiesByUserIdIteratorPtr FLotteryDomain::Probabilities(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribeProbabilitiesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            LotteryName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FLotteryDomain::SubscribeProbabilities(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                LotteryName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FLotteryDomain::UnsubscribeProbabilities(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                LotteryName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FLotteryDomain::FCollectProbabilitiesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Lottery::Model::FProbabilityPtr>>, public TSharedFromThis<FCollectProbabilitiesTask>
    {
        const TSharedPtr<FLotteryDomain> Self;
        const TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectProbabilitiesTask(const TSharedPtr<FLotteryDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectProbabilitiesTask(const FCollectProbabilitiesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Lottery::Model::FProbabilityPtr>>> Result) override
        {
            TArray<Gs2::Lottery::Model::FProbabilityPtr> Items;
            auto Iterator = Self->Probabilities(QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FLotteryDomain::SubscribeProbabilities(
        TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryLotteryName = LotteryName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        LotteryName,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryLotteryName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FLotteryDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryLotteryName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectProbabilitiesTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FLotteryDomain::InvalidateProbabilities(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        LotteryName,
        TOptional<int32>()
    )
        );
    }

    FLotteryDomain::FSubscribeProbabilitiesWithInitialCallTask::FSubscribeProbabilitiesWithInitialCallTask(const TSharedPtr<FLotteryDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FLotteryDomain::FSubscribeProbabilitiesWithInitialCallTask::FSubscribeProbabilitiesWithInitialCallTask(const FSubscribeProbabilitiesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FSubscribeProbabilitiesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectProbabilitiesTask>>(Self, TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeProbabilities(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FLotteryDomain::FSubscribeProbabilitiesWithInitialCallTask>> FLotteryDomain::SubscribeProbabilitiesWithInitialCall(TFunction<void(TArray<Gs2::Lottery::Model::FProbabilityPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeProbabilitiesWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FProbabilityDomain> FLotteryDomain::Probability(
        const FString PrizeId
    )
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FProbabilityDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            LotteryName,
            TOptional<FString>(PrizeId)
        );
    }

    FString FLotteryDomain::CreateCacheParentKey(
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

    FString FLotteryDomain::CreateCacheKey(
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

