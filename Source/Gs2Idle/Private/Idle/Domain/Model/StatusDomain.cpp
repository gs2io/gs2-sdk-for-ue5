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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Idle/Domain/Model/Status.h"
#include "Idle/Domain/Model/Namespace.h"
#include "Idle/Domain/Model/CategoryModelMaster.h"
#include "Idle/Domain/Model/CategoryModel.h"
#include "Idle/Domain/Model/User.h"
#include "Idle/Domain/Model/UserAccessToken.h"
#include "Idle/Domain/Model/Status.h"
#include "Idle/Domain/Model/StatusAccessToken.h"
#include "Idle/Domain/Model/CurrentCategoryMaster.h"
#include "Idle/Model/Cache/Status.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Idle::Domain::Model
{

    FStatusDomain::FStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Idle::Domain::FGs2IdleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> CategoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Idle::FGs2IdleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        CategoryName(CategoryName),
        ParentKey(Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(
            NamespaceName,
            UserId,
            TOptional<int32>()
        ))
    {
    }

    FStatusDomain::FStatusDomain(
        const FStatusDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        CategoryName(From.CategoryName),
        ParentKey(From.ParentKey)
    {

    }

    FStatusDomain::FGetTask::FGetTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FGetStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FStatus>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->GetStatusByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Idle::Model::Cache::FStatusCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    ResultModel->GetItem()->GetCategoryName(),
                    TOptional<int32>(),
                    ResultModel->GetItem()
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FGetTask>> FStatusDomain::Get(
        Request::FGetStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FPredictionTask::FPredictionTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FPredictionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FPredictionTask::FPredictionTask(
        const FPredictionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FPredictionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Idle::Model::FAcquireAction>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->PredictionByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetStatus() != nullptr)
            {
                Gs2::Idle::Model::Cache::FStatusCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    Request->GetCategoryName(),
                    TOptional<int32>(),
                    ResultModel->GetStatus()
                );
            }
        }
        const auto Items = ResultModel->GetItems();
        if (Items != nullptr)
        {
            const auto UserId = Self->UserId.IsSet() ? *Self->UserId : FString();
            for (const auto& Item : *Items)
            {
                if (!Item.IsValid() || !Item->GetRequest().IsSet())
                {
                    continue;
                }
                auto RequestString = Item->GetRequest().GetValue();
                RequestString = RequestString.Replace(TEXT("#{userId}"), *UserId);
                RequestString = RequestString.Replace(TEXT("{userId}"), *UserId);
                Item->WithRequest(RequestString);
            }
        }
        *Result = Items;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FPredictionTask>> FStatusDomain::Prediction(
        Request::FPredictionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPredictionTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FReceiveTask::FReceiveTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FReceiveByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FReceiveTask::FReceiveTask(
        const FReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->ReceiveByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetStatus().IsValid())
        {
            Gs2::Idle::Model::Cache::FStatusCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Request->GetUserId(),
                Request->GetCategoryName(),
                TOptional<int32>(),
                ResultModel->GetStatus()
            );
        }
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            ResultModel->GetTransactionId().IsSet() ? *ResultModel->GetTransactionId() : FString(),
            ResultModel->GetStampSheet().IsSet() ? *ResultModel->GetStampSheet() : FString(),
            ResultModel->GetStampSheetEncryptionKeyId().IsSet() ? *ResultModel->GetStampSheetEncryptionKeyId() : FString(),
            ResultModel->GetAtomicCommit().IsSet() ? *ResultModel->GetAtomicCommit() : false,
            ResultModel->GetTransactionResult()
        );
        const bool HasInlineTransactionResult =
            ResultModel->GetAutoRunStampSheet().Get(false) &&
            ResultModel->GetAtomicCommit().Get(false) &&
            ResultModel->GetTransactionResult().IsValid();
        if (ResultModel->GetStampSheet().IsSet() || HasInlineTransactionResult)
        {
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FReceiveTask>> FStatusDomain::Receive(
        Request::FReceiveByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FIncreaseMaximumIdleMinutesTask::FIncreaseMaximumIdleMinutesTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FIncreaseMaximumIdleMinutesTask::FIncreaseMaximumIdleMinutesTask(
        const FIncreaseMaximumIdleMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FIncreaseMaximumIdleMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->IncreaseMaximumIdleMinutesByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Idle::Model::Cache::FStatusCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    ResultModel->GetItem()->GetCategoryName(),
                    TOptional<int32>(),
                    ResultModel->GetItem()
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FIncreaseMaximumIdleMinutesTask>> FStatusDomain::IncreaseMaximumIdleMinutes(
        Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIncreaseMaximumIdleMinutesTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FDecreaseMaximumIdleMinutesTask::FDecreaseMaximumIdleMinutesTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FDecreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FDecreaseMaximumIdleMinutesTask::FDecreaseMaximumIdleMinutesTask(
        const FDecreaseMaximumIdleMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FDecreaseMaximumIdleMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->DecreaseMaximumIdleMinutesByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Idle::Model::Cache::FStatusCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    ResultModel->GetItem()->GetCategoryName(),
                    TOptional<int32>(),
                    ResultModel->GetItem()
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FDecreaseMaximumIdleMinutesTask>> FStatusDomain::DecreaseMaximumIdleMinutes(
        Request::FDecreaseMaximumIdleMinutesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecreaseMaximumIdleMinutesTask>>(this->AsShared(), Request);
    }

    FStatusDomain::FSetMaximumIdleMinutesTask::FSetMaximumIdleMinutesTask(
        const TSharedPtr<FStatusDomain>& Self,
        const Request::FSetMaximumIdleMinutesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStatusDomain::FSetMaximumIdleMinutesTask::FSetMaximumIdleMinutesTask(
        const FSetMaximumIdleMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FSetMaximumIdleMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->SetMaximumIdleMinutesByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Idle::Model::Cache::FStatusCache::Put(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    ResultModel->GetItem()->GetCategoryName(),
                    TOptional<int32>(),
                    ResultModel->GetItem()
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStatusDomain::FSetMaximumIdleMinutesTask>> FStatusDomain::SetMaximumIdleMinutes(
        Request::FSetMaximumIdleMinutesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaximumIdleMinutesTask>>(this->AsShared(), Request);
    }

    FString FStatusDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> CategoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            ChildType;
    }

    FString FStatusDomain::CreateCacheKey(
        TOptional<FString> CategoryName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null");
    }

    FStatusDomain::FModelTask::FModelTask(
        const TSharedPtr<FStatusDomain> Self
    ): Self(Self)
    {

    }

    FStatusDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStatusDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Idle::Model::FStatus>> Result
    )
    {
        const auto CacheParentKey = Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Idle::Model::Cache::FStatusCache::CreateCacheKey(
            Self->CategoryName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Idle::Model::FStatus::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Idle::Model::FStatusPtr Value;
                const auto CacheHit = Gs2::Idle::Model::Cache::FStatusCache::TryGet(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    Self->CategoryName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Idle::Model::Cache::FStatusCache::Fetch(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->UserId,
                    Self->CategoryName,
                    TOptional<int32>(),
                    [Self](Gs2::Idle::Model::FStatusPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Idle::Request::FGetStatusByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FStatusDomain::FModelTask>> FStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStatusDomain::FModelTask>>(this->AsShared());
    }

    void FStatusDomain::Invalidate()
    {
        Gs2::Idle::Model::Cache::FStatusCache::Delete(
            Gs2->Cache,
            NamespaceName,
            UserId,
            CategoryName,
            TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FStatusDomain::Subscribe(
        TFunction<void(Gs2::Idle::Model::FStatusPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Idle::Domain::FGs2IdleDomain> WeakService = Service;
        const auto SubscriptionParentKey = Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(
            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Idle::Model::Cache::FStatusCache::CreateCacheKey(
            CategoryName
        );
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryCategoryName = CategoryName;
        return Gs2->Cache->Subscribe(
            Gs2::Idle::Model::FStatus::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryCategoryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FStatusDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryCategoryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStatusDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Idle::Model::FStatus::TypeName,
            Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(NamespaceName, UserId, TOptional<int32>()),
            Gs2::Idle::Model::Cache::FStatusCache::CreateCacheKey(CategoryName),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
