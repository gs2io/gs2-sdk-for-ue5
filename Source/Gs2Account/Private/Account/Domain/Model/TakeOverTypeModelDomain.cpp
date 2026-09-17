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

#include "Account/Domain/Model/TakeOverTypeModel.h"
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
#include "Account/Model/Cache/TakeOverTypeModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FTakeOverTypeModelDomain::FTakeOverTypeModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "TakeOverTypeModel"
        ))
    {
    }

    FTakeOverTypeModelDomain::FTakeOverTypeModelDomain(
        const FTakeOverTypeModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverTypeModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverTypeModelDomain>& Self,
        const Request::FGetTakeOverTypeModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverTypeModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithType(Self->Type);
        const auto Future = Self->Client->GetTakeOverTypeModel(
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
              }
        Gs2::Account::Model::Cache::FTakeOverTypeModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetType().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverTypeModelDomain::FGetTask>> FTakeOverTypeModelDomain::Get(
        Request::FGetTakeOverTypeModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FTakeOverTypeModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int32> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Type.IsSet() ? FString::FromInt(*Type) : "null") + ":" +
            ChildType;
    }

    FString FTakeOverTypeModelDomain::CreateCacheKey(
        TOptional<int32> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? FString::FromInt(*Type) : "null");
    }

    FTakeOverTypeModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverTypeModelDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverTypeModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheKey(

            Self->Type
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Account::Model::FTakeOverTypeModelPtr Value;
                const auto CacheHit = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Type,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Type,
                    TOptional<int32>(),
                    [Self](Gs2::Account::Model::FTakeOverTypeModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Account::Request::FGetTakeOverTypeModelRequest>()
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

    TSharedPtr<FAsyncTask<FTakeOverTypeModelDomain::FModelTask>> FTakeOverTypeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverTypeModelDomain::FModelTask>>(this->AsShared());
    }

    void FTakeOverTypeModelDomain::Invalidate()
    {
        Gs2::Account::Model::Cache::FTakeOverTypeModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            Type,
            TOptional<int32>()
        );
    }

    FTakeOverTypeModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FTakeOverTypeModelDomain>& Self,
        TFunction<void(Gs2::Account::Model::FTakeOverTypeModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FTakeOverTypeModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FTakeOverTypeModelDomain::FSubscribeWithInitialCallTask>> FTakeOverTypeModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Account::Model::FTakeOverTypeModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FTakeOverTypeModelDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FTakeOverTypeModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheKey(

            Type
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<int32> QueryType = Type;
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryType]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FTakeOverTypeModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryType
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FTakeOverTypeModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheKey(

            Type
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
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
