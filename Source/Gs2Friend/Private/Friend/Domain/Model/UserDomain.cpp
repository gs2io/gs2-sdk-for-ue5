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
#include "Friend/Domain/Model/FriendRequest.h"
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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Friend::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FSendRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendRequestByUserId(
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
        Gs2::Friend::Model::Cache::FSendFriendRequestCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetTargetUserId(),
            TOptional<int32>(),
            MakeShared<Gs2::Friend::Model::FSendFriendRequest>()
            ->WithUserId(ResultModel->GetItem()->GetUserId())
            ->WithTargetUserId(ResultModel->GetItem()->GetTargetUserId())
            ->WithPublicProfile(ResultModel->GetItem()->GetPublicProfile())
        );
            }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendRequestTask>> FUserDomain::SendRequest(
        Request::FSendRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FProfileDomain> FUserDomain::Profile(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FProfileDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileDomain> FUserDomain::PublicProfile(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FPublicProfileDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeBlackListByUserIdIteratorPtr FUserDomain::BlackListUsers(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeBlackListByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FBlackListDomain> FUserDomain::BlackList(
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FBlackListDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowDomain> FUserDomain::Follow(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeFriendsByUserIdIteratorPtr FUserDomain::Friends(
        const TOptional<bool> WithProfile,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFriendsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            WithProfile,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeFriends(
    TFunction<void()> Callback
        , const TOptional<bool> WithProfile
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                WithProfile,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeFriends(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<bool> WithProfile, const TOptional<FString> TimeOffsetToken
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                WithProfile,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectFriendsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FFriendUserPtr>>, public TSharedFromThis<FCollectFriendsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> OnCollected;
    const TOptional<bool> QueryWithProfile;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectFriendsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> OnCollected,const TOptional<bool> WithProfile,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryWithProfile(WithProfile), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectFriendsTask(const FCollectFriendsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryWithProfile(From.QueryWithProfile), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FFriendUserPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FFriendUserPtr> Items;
            auto Iterator = Self->Friends(QueryWithProfile, QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeFriends(
        TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> Callback,const TOptional<bool> WithProfile,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryWithProfile = WithProfile;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        WithProfile,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryWithProfile, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFriendsTask>>(Domain, Callback, QueryWithProfile, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateFriends(const TOptional<bool> WithProfile,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FFriendUser::TypeName,
            Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        WithProfile,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeFriendsWithInitialCallTask::FSubscribeFriendsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> Callback,const TOptional<bool> WithProfile,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryWithProfile(WithProfile), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeFriendsWithInitialCallTask::FSubscribeFriendsWithInitialCallTask(const FSubscribeFriendsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryWithProfile(From.QueryWithProfile), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeFriendsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFriendsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)>(), QueryWithProfile, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeFriends(Callback, QueryWithProfile, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeFriendsWithInitialCallTask>> FUserDomain::SubscribeFriendsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FFriendUserPtr>)> Callback,const TOptional<bool> WithProfile,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeFriendsWithInitialCallTask>>(this->AsShared(), Callback, WithProfile, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFriendDomain> FUserDomain::Friend(
        const bool WithProfile
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFriendDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            WithProfile
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeSendRequestsByUserIdIteratorPtr FUserDomain::SendRequests(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeSendRequestsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeSendRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectSendRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FSendFriendRequestPtr>>, public TSharedFromThis<FCollectSendRequestsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectSendRequestsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectSendRequestsTask(const FCollectSendRequestsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FSendFriendRequestPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FSendFriendRequestPtr> Items;
            auto Iterator = Self->SendRequests(QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(
        TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateSendRequests(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FSendFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const FSubscribeSendRequestsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeSendRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSendRequests(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeSendRequestsWithInitialCallTask>> FUserDomain::SubscribeSendRequestsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FSendFriendRequestPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSendRequestsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestDomain> FUserDomain::SendFriendRequest(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsByUserIdIteratorPtr FUserDomain::ReceiveRequests(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceiveRequests(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeReceiveRequests(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectReceiveRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>>, public TSharedFromThis<FCollectReceiveRequestsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectReceiveRequestsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectReceiveRequestsTask(const FCollectReceiveRequestsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr> Items;
            auto Iterator = Self->ReceiveRequests(QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeReceiveRequests(
        TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiveRequestsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateReceiveRequests(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            Gs2::Friend::Model::Cache::FFriendRequestCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeReceiveRequestsWithInitialCallTask::FSubscribeReceiveRequestsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeReceiveRequestsWithInitialCallTask::FSubscribeReceiveRequestsWithInitialCallTask(const FSubscribeReceiveRequestsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeReceiveRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectReceiveRequestsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeReceiveRequests(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeReceiveRequestsWithInitialCallTask>> FUserDomain::SubscribeReceiveRequestsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeReceiveRequestsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain> FUserDomain::ReceiveFriendRequest(
        const FString FromUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            FromUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(FromUserId)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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
