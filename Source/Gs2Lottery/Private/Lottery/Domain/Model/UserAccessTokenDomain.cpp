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

#include "Lottery/Domain/Model/UserAccessToken.h"
#include "Lottery/Domain/Model/User.h"
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
#include "Lottery/Model/Cache/DrawnPrize.h"
#include "Lottery/Model/Cache/BoxItems.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryAccessTokenDomain> FUserAccessTokenDomain::Lottery(
        const FString LotteryName
    )
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FLotteryAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            LotteryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LotteryName)
        );
    }

    Gs2::Lottery::Domain::Iterator::FDescribeBoxesIteratorPtr FUserAccessTokenDomain::Boxes(
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeBoxes(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeBoxes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectBoxesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Lottery::Model::FBoxItemsPtr>>, public TSharedFromThis<FCollectBoxesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Lottery::Model::FBoxItemsPtr>)> OnCollected;

    public:
        explicit FCollectBoxesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FBoxItemsPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectBoxesTask(const FCollectBoxesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Lottery::Model::FBoxItemsPtr>>> Result) override
        {
            TArray<Gs2::Lottery::Model::FBoxItemsPtr> Items;
            auto Iterator = Self->Boxes()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Lottery::Model::FBoxItemsPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeBoxes(
        TFunction<void(TArray<Gs2::Lottery::Model::FBoxItemsPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Lottery::Model::FBoxItemsPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Lottery::Model::FBoxItems>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBoxesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateBoxes()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeBoxesWithInitialCallTask::FSubscribeBoxesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Lottery::Model::FBoxItemsPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeBoxesWithInitialCallTask::FSubscribeBoxesWithInitialCallTask(const FSubscribeBoxesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeBoxesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBoxesTask>>(Self, TFunction<void(TArray<Gs2::Lottery::Model::FBoxItemsPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeBoxes(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeBoxesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeBoxesWithInitialCall(TFunction<void(TArray<Gs2::Lottery::Model::FBoxItemsPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeBoxesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomain> FUserAccessTokenDomain::BoxItems(
        const FString PrizeTableName
    )
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            PrizeTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(PrizeTableName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
