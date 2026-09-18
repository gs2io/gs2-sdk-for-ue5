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

#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Domain/Model/Follow.h"
#include "Friend/Domain/Model/FollowAccessToken.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/FriendAccessToken.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/SendFriendRequest.h"
#include "Friend/Domain/Model/SendFriendRequestAccessToken.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/ReceiveFriendRequestAccessToken.h"
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Domain/Model/PublicProfileAccessToken.h"
#include "Friend/Domain/Model/FriendRequestAccessToken.h"
#include "Friend/Model/Cache/BlackList.h"
#include "Friend/Domain/Model/BlackListEntry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FBlackListAccessTokenDomain::FBlackListAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "BlackList"
        ))
    {
    }

    FBlackListAccessTokenDomain::FBlackListAccessTokenDomain(
        const FBlackListAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FBlackListAccessTokenDomain::FRegisterTask::FRegisterTask(
        const TSharedPtr<FBlackListAccessTokenDomain>& Self,
        const Request::FRegisterBlackListRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBlackListAccessTokenDomain::FRegisterTask::FRegisterTask(
        const FRegisterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBlackListAccessTokenDomain::FRegisterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->RegisterBlackList(
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

        if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Friend::Model::Cache::FBlackListCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
        // ブラックリスト登録/解除で一覧の内容が変わるため、BlackListUsers() の一覧キャッシュを無効化する
        Self->Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FBlackListEntry::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                Request->GetNamespaceName(),
                (CacheOwnerSnapshotUserId),
                Gs2::Friend::Model::FBlackListEntry::TypeName
            )
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBlackListAccessTokenDomain::FRegisterTask>> FBlackListAccessTokenDomain::Register(
        Request::FRegisterBlackListRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRegisterTask>>(this->AsShared(), Request);
    }

    FBlackListAccessTokenDomain::FUnregisterTask::FUnregisterTask(
        const TSharedPtr<FBlackListAccessTokenDomain>& Self,
        const Request::FUnregisterBlackListRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBlackListAccessTokenDomain::FUnregisterTask::FUnregisterTask(
        const FUnregisterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBlackListAccessTokenDomain::FUnregisterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->UnregisterBlackList(
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

        if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Friend::Model::Cache::FBlackListCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
        // ブラックリスト登録/解除で一覧の内容が変わるため、BlackListUsers() の一覧キャッシュを無効化する
        Self->Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FBlackListEntry::TypeName,
            Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                Request->GetNamespaceName(),
                (CacheOwnerSnapshotUserId),
                Gs2::Friend::Model::FBlackListEntry::TypeName
            )
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBlackListAccessTokenDomain::FUnregisterTask>> FBlackListAccessTokenDomain::Unregister(
        Request::FUnregisterBlackListRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnregisterTask>>(this->AsShared(), Request);
    }

    FString FBlackListAccessTokenDomain::CreateCacheParentKey(
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

    FString FBlackListAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FBlackListAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FBlackListAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FBlackListAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBlackListAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FBlackList>> Result
    )
    {
        const auto CacheParentKey = Gs2::Friend::Model::Cache::FBlackListCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Friend::Model::Cache::FBlackListCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Friend::Model::FBlackList::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Friend::Model::FBlackListPtr Value;
                const auto CacheHit = Gs2::Friend::Model::Cache::FBlackListCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FBlackListAccessTokenDomain::FModelTask>> FBlackListAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBlackListAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FBlackListAccessTokenDomain::Invalidate()
    {
        Gs2::Friend::Model::Cache::FBlackListCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FBlackListAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBlackListAccessTokenDomain>& Self,
        TFunction<void(Gs2::Friend::Model::FBlackListPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBlackListAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBlackListAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FBlackListAccessTokenDomain::FSubscribeWithInitialCallTask>> FBlackListAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Friend::Model::FBlackListPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBlackListAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FBlackListPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FBlackListCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FBlackListCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FBlackList::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FBlackList>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FBlackListAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBlackListAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FBlackListCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FBlackListCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FBlackList::TypeName,
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
