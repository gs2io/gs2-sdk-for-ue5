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

#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/User.h"
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
#include "Friend/Model/Cache/Profile.h"
#include "Friend/Model/Cache/SendFriendRequest.h"
#include "Friend/Model/Cache/FriendRequest.h"
#include "Friend/Model/Cache/PublicProfile.h"
#include "Friend/Model/Cache/BlackList.h"
#include "Friend/Model/Cache/FollowUser.h"
#include "Friend/Model/Cache/Follow.h"
#include "Friend/Model/Cache/Friend.h"
#include "Friend/Model/Cache/FriendUser.h"
#include "Friend/Model/Cache/ReceiveFriendRequest.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
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
        ParentKey(Gs2::Friend::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FSendRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->SendRequest(
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
        Gs2::Friend::Model::Cache::FSendFriendRequestCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetTargetUserId(),
            CacheOwnerSnapshotTimeOffset,
            MakeShared<Gs2::Friend::Model::FSendFriendRequest>()
            ->WithUserId(ResultModel->GetItem()->GetUserId())
            ->WithTargetUserId(ResultModel->GetItem()->GetTargetUserId())
            ->WithPublicProfile(ResultModel->GetItem()->GetPublicProfile())
        );
            }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSendRequestTask>> FUserAccessTokenDomain::SendRequest(
        Request::FSendRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FProfileAccessTokenDomain> FUserAccessTokenDomain::Profile(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FProfileAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain> FUserAccessTokenDomain::PublicProfile(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeBlackListIteratorPtr FUserAccessTokenDomain::BlackListUsers(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain> FUserAccessTokenDomain::BlackList(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowAccessTokenDomain> FUserAccessTokenDomain::Follow(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFriendsIteratorPtr FUserAccessTokenDomain::Friends(
        const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFriendsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeFriends(
    TFunction<void()> Callback
        , const TOptional<bool> WithProfile
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                WithProfile,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeFriends(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<bool> WithProfile
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                WithProfile,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectFriendsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FFriendUserPtr>>, public TSharedFromThis<FCollectFriendsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> OnCollected;
    const TOptional<bool> QueryWithProfile;
    public:
        explicit FCollectFriendsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> OnCollected,const TOptional<bool> WithProfile) : Self(Self), OnCollected(OnCollected), QueryWithProfile(WithProfile) {}
        FCollectFriendsTask(const FCollectFriendsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryWithProfile(From.QueryWithProfile) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FFriendUserPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FFriendUserPtr> Items;
            auto Iterator = Self->Friends(QueryWithProfile)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Friend::Model::FFriendUserPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeFriends(
        TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> Callback,const TOptional<bool> WithProfile
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryWithProfile = WithProfile;
        const auto Parent = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        WithProfile,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Friend::Model::FFriendUserPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Friend::Model::FFriendUser>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryWithProfile, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFriendsTask>>(Domain, Callback, QueryWithProfile);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateFriends(const TOptional<bool> WithProfile)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        WithProfile,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeFriendsWithInitialCallTask::FSubscribeFriendsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> Callback,const TOptional<bool> WithProfile) : Self(Self), Callback(Callback), QueryWithProfile(WithProfile) {}
    FUserAccessTokenDomain::FSubscribeFriendsWithInitialCallTask::FSubscribeFriendsWithInitialCallTask(const FSubscribeFriendsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryWithProfile(From.QueryWithProfile) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeFriendsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFriendsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)>(), QueryWithProfile);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeFriends(Callback, QueryWithProfile);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeFriendsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeFriendsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> Callback,const TOptional<bool> WithProfile)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeFriendsWithInitialCallTask>>(this->AsShared(), Callback, WithProfile);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain> FUserAccessTokenDomain::Friend(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIteratorPtr FUserAccessTokenDomain::SendRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeSendRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectSendRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FSendFriendRequestPtr>>, public TSharedFromThis<FCollectSendRequestsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> OnCollected;

    public:
        explicit FCollectSendRequestsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectSendRequestsTask(const FCollectSendRequestsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FSendFriendRequestPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FSendFriendRequestPtr> Items;
            auto Iterator = Self->SendRequests()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Friend::Model::FSendFriendRequestPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(
        TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Friend::Model::FSendFriendRequestPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Friend::Model::FSendFriendRequest>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateSendRequests()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const FSubscribeSendRequestsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSendRequests(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeSendRequestsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSendRequestsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain> FUserAccessTokenDomain::SendFriendRequest(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr FUserAccessTokenDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeReceiveRequests(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeReceiveRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectReceiveRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>>, public TSharedFromThis<FCollectReceiveRequestsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> OnCollected;

    public:
        explicit FCollectReceiveRequestsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectReceiveRequestsTask(const FCollectReceiveRequestsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr> Items;
            auto Iterator = Self->ReceiveRequests()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeReceiveRequests(
        TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Friend::Model::FReceiveFriendRequest>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiveRequestsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateReceiveRequests()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask::FSubscribeReceiveRequestsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FUserAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask::FSubscribeReceiveRequestsWithInitialCallTask(const FSubscribeReceiveRequestsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiveRequestsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeReceiveRequests(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeReceiveRequestsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeReceiveRequestsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeReceiveRequestsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain> FUserAccessTokenDomain::ReceiveFriendRequest(
        const FString FromUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            FromUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(FromUserId)
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
