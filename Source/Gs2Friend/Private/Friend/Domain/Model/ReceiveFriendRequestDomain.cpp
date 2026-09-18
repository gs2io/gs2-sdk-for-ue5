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

#include "Friend/Domain/Model/ReceiveFriendRequest.h"
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
#include "Friend/Model/Cache/ReceiveFriendRequest.h"
#include "Friend/Model/Cache/FriendRequest.h"
#include "Friend/Model/Cache/SendFriendRequest.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FReceiveFriendRequestDomain::FReceiveFriendRequestDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> FromUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        FromUserId(FromUserId),
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "ReceiveFriendRequest"
        ))
    {
    }

    FReceiveFriendRequestDomain::FReceiveFriendRequestDomain(
        const FReceiveFriendRequestDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        FromUserId(From.FromUserId),
        ParentKey(From.ParentKey)
    {

    }

    FReceiveFriendRequestDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        const Request::FGetReceiveRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveFriendRequestDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendRequest>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->GetReceiveRequestByUserId(
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
        Gs2::Friend::Model::Cache::FFriendRequestCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetTargetUserId(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FGetTask>> FReceiveFriendRequestDomain::Get(
        Request::FGetReceiveRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReceiveFriendRequestDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        const Request::FAcceptRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveFriendRequestDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->AcceptRequestByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

              if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetFromUserId(),
            TOptional<int32>()
        );
        Gs2::Friend::Model::Cache::FSendFriendRequestCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetFromUserId(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>()
        );
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            Self->FromUserId
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FAcceptTask>> FReceiveFriendRequestDomain::Accept(
        Request::FAcceptRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FReceiveFriendRequestDomain::FRejectTask::FRejectTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        const Request::FRejectRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveFriendRequestDomain::FRejectTask::FRejectTask(
        const FRejectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->RejectRequestByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

              if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetFromUserId(),
            TOptional<int32>()
        );
        Gs2::Friend::Model::Cache::FSendFriendRequestCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetFromUserId(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>()
        );
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            Self->FromUserId
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FRejectTask>> FReceiveFriendRequestDomain::Reject(
        Request::FRejectRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(this->AsShared(), Request);
    }

    FString FReceiveFriendRequestDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> FromUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (FromUserId.IsSet() ? *FromUserId : "null") + ":" +
            ChildType;
    }

    FString FReceiveFriendRequestDomain::CreateCacheKey(
        TOptional<FString> FromUserId
    )
    {
        return FString("") +
            (FromUserId.IsSet() ? *FromUserId : "null");
    }

    FReceiveFriendRequestDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiveFriendRequestDomain> Self
    ): Self(Self)
    {

    }

    FReceiveFriendRequestDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FReceiveFriendRequest>> Result
    )
    {
        const auto CacheParentKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheKey(

            Self->FromUserId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Friend::Model::FReceiveFriendRequestPtr Value;
                const auto CacheHit = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->FromUserId,
                    TOptional<int32>(),
                    &Value
                );
                if (!CacheHit)
                {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Friend::Request::FGetReceiveRequestByUserIdRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Put(
                            Self->Gs2->Cache,

                            Self->NamespaceName,
                            Self->UserId,
                            Self->FromUserId,
                            TOptional<int32>(),
                            nullptr
                        );
                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "receiveFriendRequest")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        const auto RawValue = Future->GetTask().Result();
                        if (RawValue.IsValid())
                        {
                            Value = MakeShared<Gs2::Friend::Model::FReceiveFriendRequest>()
                                ->WithUserId(RawValue->GetUserId())
                                ->WithTargetUserId(RawValue->GetTargetUserId());
                        }
                    }
                    Future->EnsureCompletion();
                    Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Put(
                        Self->Gs2->Cache,

                        Self->NamespaceName,
                        Self->UserId,
                        Self->FromUserId,
                        TOptional<int32>(),
                        Value
                    );
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FModelTask>> FReceiveFriendRequestDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveFriendRequestDomain::FModelTask>>(this->AsShared());
    }

    void FReceiveFriendRequestDomain::Invalidate()
    {
        Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            FromUserId,
            TOptional<int32>()
        );
    }

    FReceiveFriendRequestDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        TFunction<void(Gs2::Friend::Model::FReceiveFriendRequestPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FReceiveFriendRequestDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FSubscribeWithInitialCallTask>> FReceiveFriendRequestDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Friend::Model::FReceiveFriendRequestPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FReceiveFriendRequestDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FReceiveFriendRequestPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheKey(

            FromUserId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Friend::Domain::FGs2FriendDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryFromUserId = FromUserId;
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FReceiveFriendRequest>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryFromUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FReceiveFriendRequestDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryFromUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FReceiveFriendRequestDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheKey(

            FromUserId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
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
