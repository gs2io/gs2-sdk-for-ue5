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

#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
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
#include "Friend/Model/Cache/FriendUser.h"
#include "Friend/Model/Cache/Friend.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FFriendUserAccessTokenDomain::FFriendUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<bool> WithProfile,
        const TOptional<FString> TargetUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        WithProfile(WithProfile),
        TargetUserId(TargetUserId),
        ParentKey(Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            WithProfile.IsSet() ? *WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
            "FriendUser"
        ))
    {
    }

    FFriendUserAccessTokenDomain::FFriendUserAccessTokenDomain(
        const FFriendUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        WithProfile(From.WithProfile),
        TargetUserId(From.TargetUserId),
        ParentKey(From.ParentKey)
    {

    }

    FFriendUserAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FFriendUserAccessTokenDomain>& Self,
        const Request::FGetFriendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFriendUserAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTargetUserId(Self->TargetUserId)
            ->WithWithProfile(Self->WithProfile);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetFriend(
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
        Gs2::Friend::Model::Cache::FFriendUserCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            Request->GetWithProfile().Get(bool{}),
            Request->GetTargetUserId(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FGetTask>> FFriendUserAccessTokenDomain::Get(
        Request::FGetFriendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFriendUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFriendUserAccessTokenDomain>& Self,
        const Request::FDeleteFriendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFriendUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTargetUserId(Self->TargetUserId);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeleteFriend(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

              if (!((CacheOwnerSnapshotUserId)).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
        // フレンド解除は双方向の関係であり、また一覧キャッシュは WithProfile(true/false/未指定) ごとに
        // 別々に保持されるため、自分側・相手側それぞれ全パターンのキャッシュを削除する
        for (const auto& WithProfile : {TOptional<bool>(false), TOptional<bool>(true), TOptional<bool>()})
        {
            Gs2::Friend::Model::Cache::FFriendUserCache::Delete(
                Self->Gs2->Cache,

                Request->GetNamespaceName(),
                (CacheOwnerSnapshotUserId),
                WithProfile,
                Request->GetTargetUserId(),
                CacheOwnerSnapshotTimeOffset
            );
            Gs2::Friend::Model::Cache::FFriendUserCache::Delete(
                Self->Gs2->Cache,

                Request->GetNamespaceName(),
                Request->GetTargetUserId(),
                WithProfile,
                (CacheOwnerSnapshotUserId),
                CacheOwnerSnapshotTimeOffset
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FDeleteTask>> FFriendUserAccessTokenDomain::Delete(
        Request::FDeleteFriendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFriendUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> WithProfile,
        TOptional<FString> TargetUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (WithProfile.IsSet() ? *WithProfile : "null") + ":" +
            (TargetUserId.IsSet() ? *TargetUserId : "null") + ":" +
            ChildType;
    }

    FString FFriendUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TargetUserId
    )
    {
        return FString("") +
            (TargetUserId.IsSet() ? *TargetUserId : "null");
    }

    FFriendUserAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FFriendUserAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FFriendUserAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result
    )
    {
        const auto CacheParentKey = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->WithProfile,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheKey(

            Self->TargetUserId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Friend::Model::FFriendUser::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Friend::Model::FFriendUserPtr Value;
                const auto CacheHit = Gs2::Friend::Model::Cache::FFriendUserCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->WithProfile,
                    Self->TargetUserId,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Friend::Model::Cache::FFriendUserCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->WithProfile,
                    Self->TargetUserId,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Friend::Model::FFriendUserPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Friend::Request::FGetFriendRequest>()
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

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FModelTask>> FFriendUserAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFriendUserAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FFriendUserAccessTokenDomain::Invalidate()
    {
        Gs2::Friend::Model::Cache::FFriendUserCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            WithProfile,
            TargetUserId,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FFriendUserAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FFriendUserAccessTokenDomain>& Self,
        TFunction<void(Gs2::Friend::Model::FFriendUserPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FFriendUserAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFriendUserAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FFriendUserAccessTokenDomain::FSubscribeWithInitialCallTask>> FFriendUserAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Friend::Model::FFriendUserPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FFriendUserAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FFriendUserPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            WithProfile,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheKey(

            TargetUserId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<bool> QueryWithProfile = WithProfile;
        const TOptional<FString> QueryTargetUserId = TargetUserId;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FFriendUser>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryWithProfile, QueryTargetUserId, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FFriendUserAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryWithProfile,
                    QueryTargetUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FFriendUserAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            WithProfile,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheKey(

            TargetUserId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
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
