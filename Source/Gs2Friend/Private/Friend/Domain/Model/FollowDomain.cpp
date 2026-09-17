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

#include "Friend/Domain/Model/Follow.h"
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
#include "Friend/Model/Cache/Follow.h"
#include "Friend/Model/Cache/FollowUser.h"
#include "Friend/Model/Cache/PublicProfile.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FFollowDomain::FFollowDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<bool> WithProfile
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        WithProfile(WithProfile),
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Follow"
        ))
    {
    }

    FFollowDomain::FFollowDomain(
        const FFollowDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        WithProfile(From.WithProfile),
        ParentKey(From.ParentKey)
    {

    }

    FFollowDomain::FFollowTask::FFollowTask(
        const TSharedPtr<FFollowDomain>& Self,
        const Request::FFollowByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFollowDomain::FFollowTask::FFollowTask(
        const FFollowTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowDomain::FFollowTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->FollowByUserId(
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

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Friend::Model::Cache::FFollowUserCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Self->UserId,
            true,
            Request->GetTargetUserId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
        Gs2::Friend::Model::Cache::FFollowUserCache::Put(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            Self->UserId,
            false,
            Request->GetTargetUserId(),
            TOptional<int32>(),
            MakeShared<Gs2::Friend::Model::FFollowUser>()->WithUserId(Request->GetTargetUserId())
        );
        Gs2::Friend::Model::Cache::FFollowUserCache::Put(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            Self->UserId,
            TOptional<bool>(),
            Request->GetTargetUserId(),
            TOptional<int32>(),
            MakeShared<Gs2::Friend::Model::FFollowUser>()->WithUserId(Request->GetTargetUserId())
        );
        Gs2::Friend::Model::Cache::FPublicProfileCache::Put(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            TOptional<int32>(),
            MakeShared<Gs2::Friend::Model::FPublicProfile>()
                ->WithUserId(ResultModel->GetItem()->GetUserId())
                ->WithPublicProfile(ResultModel->GetItem()->GetPublicProfile())
        );
            }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FFollowUserDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->UserId,
            Self->WithProfile,
            Request->GetTargetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFollowDomain::FFollowTask>> FFollowDomain::Follow(
        Request::FFollowByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFollowTask>>(this->AsShared(), Request);
    }

    Gs2::Friend::Domain::Iterator::FDescribeFollowsByUserIdIteratorPtr FFollowDomain::Follows(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeFollowsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            WithProfile,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FFollowDomain::SubscribeFollows(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FFollowUser::TypeName,
            Gs2::Friend::Model::Cache::FFollowUserCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                WithProfile,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FFollowDomain::UnsubscribeFollows(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FFollowUser::TypeName,
            Gs2::Friend::Model::Cache::FFollowUserCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                WithProfile,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FFollowDomain::FCollectFollowsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FFollowUserPtr>>, public TSharedFromThis<FCollectFollowsTask>
    {
        const TSharedPtr<FFollowDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectFollowsTask(const TSharedPtr<FFollowDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectFollowsTask(const FCollectFollowsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FFollowUserPtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FFollowUserPtr> Items;
            auto Iterator = Self->Follows(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Friend::Model::FFollowUserPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FFollowDomain::SubscribeFollows(
        TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryWithProfile = WithProfile;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Friend::Model::Cache::FFollowUserCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        WithProfile,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Friend::Model::FFollowUser::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Friend::Model::FFollowUserPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Friend::Model::FFollowUser>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryWithProfile, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FFollowDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryWithProfile);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFollowsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FFollowDomain::InvalidateFollows(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FFollowUser::TypeName,
            Gs2::Friend::Model::Cache::FFollowUserCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        WithProfile,
        TOptional<int32>()
    )
        );
    }

    FFollowDomain::FSubscribeFollowsWithInitialCallTask::FSubscribeFollowsWithInitialCallTask(const TSharedPtr<FFollowDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FFollowDomain::FSubscribeFollowsWithInitialCallTask::FSubscribeFollowsWithInitialCallTask(const FSubscribeFollowsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FFollowDomain::FSubscribeFollowsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFollowsTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeFollows(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FFollowDomain::FSubscribeFollowsWithInitialCallTask>> FFollowDomain::SubscribeFollowsWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FFollowUserPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeFollowsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FFollowUserDomain> FFollowDomain::FollowUser(
        const FString TargetUserId
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FFollowUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            WithProfile,
            TargetUserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(TargetUserId)
        );
    }

    FString FFollowDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> WithProfile,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (WithProfile.IsSet() ? *WithProfile : "null") + ":" +
            ChildType;
    }

    FString FFollowDomain::CreateCacheKey(
        TOptional<FString> WithProfile
    )
    {
        return FString("") +
            (WithProfile.IsSet() ? *WithProfile : "null");
    }

    FFollowDomain::FModelTask::FModelTask(
        const TSharedPtr<FFollowDomain> Self
    ): Self(Self)
    {

    }

    FFollowDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFollow>> Result
    )
    {
        const auto CacheParentKey = Gs2::Friend::Model::Cache::FFollowCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Friend::Model::Cache::FFollowCache::CreateCacheKey(

            Self->WithProfile
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Friend::Model::FFollow::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Friend::Model::FFollowPtr Value;
                const auto CacheHit = Gs2::Friend::Model::Cache::FFollowCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->WithProfile,
                    TOptional<int32>(),
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

    TSharedPtr<FAsyncTask<FFollowDomain::FModelTask>> FFollowDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFollowDomain::FModelTask>>(this->AsShared());
    }

    void FFollowDomain::Invalidate()
    {
        Gs2::Friend::Model::Cache::FFollowCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            WithProfile,
            TOptional<int32>()
        );
    }

    FFollowDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FFollowDomain>& Self,
        TFunction<void(Gs2::Friend::Model::FFollowPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FFollowDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFollowDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FFollowDomain::FSubscribeWithInitialCallTask>> FFollowDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Friend::Model::FFollowPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FFollowDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FFollowPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FFollowCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FFollowCache::CreateCacheKey(

            WithProfile
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<bool> QueryWithProfile = WithProfile;
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FFollow::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FFollow>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryWithProfile]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FFollowDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryWithProfile
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FFollowDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FFollowCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FFollowCache::CreateCacheKey(

            WithProfile
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FFollow::TypeName,
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
