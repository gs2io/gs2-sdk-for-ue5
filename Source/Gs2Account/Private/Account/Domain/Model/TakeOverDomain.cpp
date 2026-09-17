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

#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/TakeOverTypeModel.h"
#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/CurrentModelMaster.h"
#include "Account/Model/Cache/TakeOver.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FTakeOverDomain::FTakeOverDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "TakeOver"
        ))
    {
    }

    FTakeOverDomain::FTakeOverDomain(
        const FTakeOverDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        const Request::FCreateTakeOverByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->CreateTakeOverByUserId(
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
        Gs2::Account::Model::Cache::FTakeOverCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetType().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverDomain::FCreateTask>> FTakeOverDomain::Create(
        Request::FCreateTakeOverByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FTakeOverDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        const Request::FGetTakeOverByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->GetTakeOverByUserId(
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
        Gs2::Account::Model::Cache::FTakeOverCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetType().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverDomain::FGetTask>> FTakeOverDomain::Get(
        Request::FGetTakeOverByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTakeOverDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        const Request::FUpdateTakeOverByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->UpdateTakeOverByUserId(
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
        Gs2::Account::Model::Cache::FTakeOverCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetType().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverDomain::FUpdateTask>> FTakeOverDomain::Update(
        Request::FUpdateTakeOverByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FString FTakeOverDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Type.IsSet() ? FString::FromInt(*Type) : "null") + ":" +
            ChildType;
    }

    FString FTakeOverDomain::CreateCacheKey(
        TOptional<int32> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? FString::FromInt(*Type) : "null");
    }

    FTakeOverDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        const auto CacheParentKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheKey(

            Self->Type
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FTakeOver::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Account::Model::FTakeOverPtr Value;
                const auto CacheHit = Gs2::Account::Model::Cache::FTakeOverCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->Type,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Account::Model::Cache::FTakeOverCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->Type,
                    TOptional<int32>(),
                    [Self](Gs2::Account::Model::FTakeOverPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Account::Request::FGetTakeOverByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FTakeOverDomain::FModelTask>> FTakeOverDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverDomain::FModelTask>>(this->AsShared());
    }

    void FTakeOverDomain::Invalidate()
    {
        Gs2::Account::Model::Cache::FTakeOverCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            Type,
            TOptional<int32>()
        );
    }

    FTakeOverDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FTakeOverDomain>& Self,
        TFunction<void(Gs2::Account::Model::FTakeOverPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FTakeOverDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FTakeOverDomain::FSubscribeWithInitialCallTask>> FTakeOverDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Account::Model::FTakeOverPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FTakeOverDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FTakeOverPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheKey(

            Type
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<int32> QueryType = Type;
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FTakeOver>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryType]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FTakeOverDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryType
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FTakeOverDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheKey(

            Type
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
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
