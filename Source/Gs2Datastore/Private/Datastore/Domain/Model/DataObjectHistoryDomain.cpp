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

#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/Namespace.h"
#include "Datastore/Domain/Model/DataObject.h"
#include "Datastore/Domain/Model/DataObjectAccessToken.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/DataObjectHistoryAccessToken.h"
#include "Datastore/Domain/Model/User.h"
#include "Datastore/Domain/Model/UserAccessToken.h"
#include "Datastore/Model/Cache/DataObjectHistory.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Datastore::Domain::Model
{

    FDataObjectHistoryDomain::FDataObjectHistoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Datastore::Domain::FGs2DatastoreDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> DataObjectName,
        const TOptional<FString> Generation
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        DataObjectName(DataObjectName),
        Generation(Generation),
        ParentKey(Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            DataObjectName,
            "DataObjectHistory"
        ))
    {
    }

    FDataObjectHistoryDomain::FDataObjectHistoryDomain(
        const FDataObjectHistoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        DataObjectName(From.DataObjectName),
        Generation(From.Generation),
        ParentKey(From.ParentKey)
    {

    }

    FDataObjectHistoryDomain::FGetTask::FGetTask(
        const TSharedPtr<FDataObjectHistoryDomain>& Self,
        const Request::FGetDataObjectHistoryByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectHistoryDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectHistoryDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithGeneration(Self->Generation);
        const auto Future = Self->Client->GetDataObjectHistoryByUserId(
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
              }if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetDataObjectName(),
            ResultModel->GetItem()->GetGeneration(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectHistoryDomain::FGetTask>> FDataObjectHistoryDomain::Get(
        Request::FGetDataObjectHistoryByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDataObjectHistoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> DataObjectName,
        TOptional<FString> Generation,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (DataObjectName.IsSet() ? *DataObjectName : "null") + ":" +
            (Generation.IsSet() ? *Generation : "null") + ":" +
            ChildType;
    }

    FString FDataObjectHistoryDomain::CreateCacheKey(
        TOptional<FString> Generation
    )
    {
        return FString("") +
            (Generation.IsSet() ? *Generation : "null");
    }

    FDataObjectHistoryDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataObjectHistoryDomain> Self
    ): Self(Self)
    {

    }

    FDataObjectHistoryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectHistoryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result
    )
    {
        const auto CacheParentKey = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            Self->DataObjectName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheKey(

            Self->Generation
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Datastore::Model::FDataObjectHistoryPtr Value;
                const auto CacheHit = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->DataObjectName,
                    Self->Generation,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->DataObjectName,
                    Self->Generation,
                    TOptional<int32>(),
                    [Self](Gs2::Datastore::Model::FDataObjectHistoryPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Datastore::Request::FGetDataObjectHistoryByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FDataObjectHistoryDomain::FModelTask>> FDataObjectHistoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataObjectHistoryDomain::FModelTask>>(this->AsShared());
    }

    void FDataObjectHistoryDomain::Invalidate()
    {
        Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            DataObjectName,
            Generation,
            TOptional<int32>()
        );
    }

    FDataObjectHistoryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDataObjectHistoryDomain>& Self,
        TFunction<void(Gs2::Datastore::Model::FDataObjectHistoryPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FDataObjectHistoryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectHistoryDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FDataObjectHistoryDomain::FSubscribeWithInitialCallTask>> FDataObjectHistoryDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Datastore::Model::FDataObjectHistoryPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FDataObjectHistoryDomain::Subscribe(
        TFunction<void(Gs2::Datastore::Model::FDataObjectHistoryPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            DataObjectName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheKey(

            Generation
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Datastore::Domain::FGs2DatastoreDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryDataObjectName = DataObjectName;
        const TOptional<FString> QueryGeneration = Generation;
        return Gs2->Cache->Subscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryDataObjectName, QueryGeneration]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FDataObjectHistoryDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryDataObjectName,
                    QueryGeneration
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDataObjectHistoryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            DataObjectName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheKey(

            Generation
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
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
