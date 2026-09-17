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

#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Domain/Model/BoxItems.h"
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
#include "Lottery/Model/Cache/BoxItems.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FBoxItemsAccessTokenDomain::FBoxItemsAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> PrizeTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        PrizeTableName(PrizeTableName),
        ParentKey(Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "BoxItems"
        ))
    {
    }

    FBoxItemsAccessTokenDomain::FBoxItemsAccessTokenDomain(
        const FBoxItemsAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        PrizeTableName(From.PrizeTableName),
        ParentKey(From.ParentKey)
    {

    }

    FBoxItemsAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FBoxItemsAccessTokenDomain>& Self,
        const Request::FGetBoxRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBoxItemsAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FBoxItems>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetBox(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Lottery::Model::Cache::FBoxItemsCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetPrizeTableName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBoxItemsAccessTokenDomain::FGetTask>> FBoxItemsAccessTokenDomain::Get(
        Request::FGetBoxRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FBoxItemsAccessTokenDomain::FResetBoxTask::FResetBoxTask(
        const TSharedPtr<FBoxItemsAccessTokenDomain>& Self,
        const Request::FResetBoxRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBoxItemsAccessTokenDomain::FResetBoxTask::FResetBoxTask(
        const FResetBoxTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsAccessTokenDomain::FResetBoxTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FBoxItemsAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->ResetBox(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Lottery::Model::Cache::FBoxItemsCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetPrizeTableName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBoxItemsAccessTokenDomain::FResetBoxTask>> FBoxItemsAccessTokenDomain::ResetBox(
        Request::FResetBoxRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetBoxTask>>(this->AsShared(), Request);
    }

    FString FBoxItemsAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> PrizeTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            ChildType;
    }

    FString FBoxItemsAccessTokenDomain::CreateCacheKey(
        TOptional<FString> PrizeTableName
    )
    {
        return FString("") +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null");
    }

    FBoxItemsAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FBoxItemsAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FBoxItemsAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FBoxItems>> Result
    )
    {
        const auto CacheParentKey = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheKey(

            Self->PrizeTableName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Lottery::Model::FBoxItemsPtr Value;
                const auto CacheHit = Gs2::Lottery::Model::Cache::FBoxItemsCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->PrizeTableName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Lottery::Model::Cache::FBoxItemsCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->PrizeTableName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Lottery::Model::FBoxItemsPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Lottery::Request::FGetBoxRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FBoxItemsAccessTokenDomain::FModelTask>> FBoxItemsAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBoxItemsAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FBoxItemsAccessTokenDomain::Invalidate()
    {
        Gs2::Lottery::Model::Cache::FBoxItemsCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            PrizeTableName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FBoxItemsAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBoxItemsAccessTokenDomain>& Self,
        TFunction<void(Gs2::Lottery::Model::FBoxItemsPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBoxItemsAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBoxItemsAccessTokenDomain::FSubscribeWithInitialCallTask>> FBoxItemsAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Lottery::Model::FBoxItemsPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBoxItemsAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FBoxItemsPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheKey(

            PrizeTableName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Lottery::Domain::FGs2LotteryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryPrizeTableName = PrizeTableName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FBoxItems>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryPrizeTableName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FBoxItemsAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryPrizeTableName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBoxItemsAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Lottery::Model::Cache::FBoxItemsCache::CreateCacheKey(

            PrizeTableName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
