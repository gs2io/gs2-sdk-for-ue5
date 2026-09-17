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

#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"
#include "SerialKey/Model/Cache/SerialKey.h"
#include "SerialKey/Model/Cache/CampaignModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FSerialKeyAccessTokenDomain::FSerialKeyAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> SerialKeyCode
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        SerialKeyCode(SerialKeyCode),
        ParentKey(Gs2::SerialKey::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "SerialKey"
        ))
    {
    }

    FSerialKeyAccessTokenDomain::FSerialKeyAccessTokenDomain(
        const FSerialKeyAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        SerialKeyCode(From.SerialKeyCode),
        ParentKey(From.ParentKey)
    {

    }

    FSerialKeyAccessTokenDomain::FUseTask::FUseTask(
        const TSharedPtr<FSerialKeyAccessTokenDomain>& Self,
        const Request::FUseRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSerialKeyAccessTokenDomain::FUseTask::FUseTask(
        const FUseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyAccessTokenDomain::FUseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->Use(
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
        Gs2::SerialKey::Model::Cache::FSerialKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetCode(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetCampaignModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::SerialKey::Model::Cache::FCampaignModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetCampaignModelName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetCampaignModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSerialKeyAccessTokenDomain::FUseTask>> FSerialKeyAccessTokenDomain::Use(
        Request::FUseRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUseTask>>(this->AsShared(), Request);
    }

    FString FSerialKeyAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> SerialKeyCode,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (SerialKeyCode.IsSet() ? *SerialKeyCode : "null") + ":" +
            ChildType;
    }

    FString FSerialKeyAccessTokenDomain::CreateCacheKey(
        TOptional<FString> SerialKeyCode
    )
    {
        return FString("") +
            (SerialKeyCode.IsSet() ? *SerialKeyCode : "null");
    }

    FSerialKeyAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSerialKeyAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSerialKeyAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result
    )
    {
        const auto CacheParentKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheKey(

            Self->SerialKeyCode
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SerialKey::Model::FSerialKeyPtr Value;
                const auto CacheHit = Gs2::SerialKey::Model::Cache::FSerialKeyCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->SerialKeyCode,
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

    TSharedPtr<FAsyncTask<FSerialKeyAccessTokenDomain::FModelTask>> FSerialKeyAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSerialKeyAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FSerialKeyAccessTokenDomain::Invalidate()
    {
        Gs2::SerialKey::Model::Cache::FSerialKeyCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            SerialKeyCode,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FSerialKeyAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSerialKeyAccessTokenDomain>& Self,
        TFunction<void(Gs2::SerialKey::Model::FSerialKeyPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSerialKeyAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSerialKeyAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSerialKeyAccessTokenDomain::FSubscribeWithInitialCallTask>> FSerialKeyAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::SerialKey::Model::FSerialKeyPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSerialKeyAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::SerialKey::Model::FSerialKeyPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheKey(

            SerialKeyCode
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SerialKey::Domain::FGs2SerialKeyDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QuerySerialKeyCode = SerialKeyCode;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SerialKey::Model::FSerialKey>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QuerySerialKeyCode, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FSerialKeyAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QuerySerialKeyCode
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSerialKeyAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheKey(

            SerialKeyCode
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
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
