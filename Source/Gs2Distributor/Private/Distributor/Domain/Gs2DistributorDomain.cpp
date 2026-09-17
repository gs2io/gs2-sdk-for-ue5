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

// ReSharper disable CppUnusedIncludeDirective

#include "Distributor/Domain/Gs2Distributor.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/Expression.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Core/Domain/Transaction/AutoTransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/AutoTransactionDomain.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Distributor/Model/Cache/Namespace.h"
#include "Distributor/Model/Cache/StampSheetResult.h"
#include "Distributor/Model/Cache/TransactionResult.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Distributor::Domain
{

    FGs2DistributorDomain::FGs2DistributorDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        CompletedStampSheets(MakeShared<TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr>>()),
        CompletedStampSheetsMutex(MakeShared<FCriticalSection>()),
        CompletedTransactions(MakeShared<TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr>>()),
        CompletedTransactionsMutex(MakeShared<FCriticalSection>()),
        Gs2(Gs2),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Gs2->RestSession)),
        ParentKey("distributor")
    {
    }

    FGs2DistributorDomain::FGs2DistributorDomain(
        const FGs2DistributorDomain& From
    ):
        CompletedStampSheets(From.CompletedStampSheets),
        CompletedStampSheetsMutex(From.CompletedStampSheetsMutex),
        CompletedTransactions(From.CompletedTransactions),
        CompletedTransactionsMutex(From.CompletedTransactionsMutex),
        AutoRunStampSheetNotificationEvent(From.AutoRunStampSheetNotificationEvent),
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2DistributorDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2DistributorDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DistributorDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DistributorDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Distributor::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DistributorDomain::FCreateNamespaceTask>> FGs2DistributorDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Distributor::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2DistributorDomain::Namespaces(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Distributor::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FGs2DistributorDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Distributor::Model::FNamespace::TypeName,
            Gs2::Distributor::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2DistributorDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Distributor::Model::FNamespace::TypeName,
            Gs2::Distributor::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2DistributorDomain::FCollectNamespacesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Distributor::Model::FNamespacePtr>>, public TSharedFromThis<FCollectNamespacesTask>
    {
        const TSharedPtr<FGs2DistributorDomain> Self;
        const TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectNamespacesTask(const TSharedPtr<FGs2DistributorDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectNamespacesTask(const FCollectNamespacesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Distributor::Model::FNamespacePtr>>> Result) override
        {
            TArray<Gs2::Distributor::Model::FNamespacePtr> Items;
            auto Iterator = Self->Namespaces(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Distributor::Model::FNamespacePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2DistributorDomain::SubscribeNamespaces(
        TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Distributor::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Distributor::Model::FNamespace::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Distributor::Model::FNamespacePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Distributor::Model::FNamespace>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2DistributorDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2DistributorDomain::InvalidateNamespaces(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Distributor::Model::FNamespace::TypeName,
            Gs2::Distributor::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2DistributorDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2DistributorDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FGs2DistributorDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2DistributorDomain::FSubscribeNamespacesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Self, TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNamespaces(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2DistributorDomain::FSubscribeNamespacesWithInitialCallTask>> FGs2DistributorDomain::SubscribeNamespacesWithInitialCall(TFunction<void(TArray<Gs2::Distributor::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain> FGs2DistributorDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2DistributorDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2DistributorDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2DistributorDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2DistributorDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "AutoRunStampSheetNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CompletedStampSheetsMutex->Lock();
            {
                const auto Notification = Gs2::Distributor::Model::FAutoRunStampSheetNotification::FromJson(PayloadJson);
                Gs2::Distributor::Model::Cache::FStampSheetResultCache::Delete(
                    Gs2->Cache,
                    Notification->GetNamespaceName(),
                    Notification->GetUserId(),
                    Notification->GetTransactionId(),
                    TOptional<int32>()
                );
                CompletedStampSheets->Add(Notification);
                AutoRunStampSheetNotificationEvent.Broadcast(Notification);
            }
            CompletedStampSheetsMutex->Unlock();
        }
        if (Action == "AutoRunTransactionNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CompletedTransactionsMutex->Lock();
            {
                const auto Notification = Gs2::Distributor::Model::FAutoRunTransactionNotification::FromJson(PayloadJson);
                Gs2::Distributor::Model::Cache::FTransactionResultCache::Delete(
                    Gs2->Cache,
                    Notification->GetNamespaceName(),
                    Notification->GetUserId(),
                    Notification->GetTransactionId(),
                    TOptional<int32>()
                );
                CompletedTransactions->Add(Notification);
                AutoRunTransactionNotificationEvent.Broadcast(Notification);
            }
            CompletedTransactionsMutex->Unlock();
        }
    }

    FAutoRunStampSheetNotificationEvent& FGs2DistributorDomain::OnAutoRunStampSheetNotification()
    {
        return AutoRunStampSheetNotificationEvent;
    }

    FAutoRunTransactionNotificationEvent& FGs2DistributorDomain::OnAutoRunTransactionNotification()
    {
        return AutoRunTransactionNotificationEvent;
    }

    FGs2DistributorDomain::FDispatchTask::FDispatchTask(
        const TSharedPtr<FGs2DistributorDomain> Self,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ): Self(Self), AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DistributorDomain::FDispatchTask::Action(
        TSharedPtr<TSharedPtr<FGs2DistributorDomain>> Result
    )
    {
        if (!AccessToken.IsValid() || !AccessToken->GetUserId().IsSet())
        {
            return nullptr;
        }
        const FString TargetUserId = *AccessToken->GetUserId();
        TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr> StampSheets;
        TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr> Transactions;

        {
            FScopeLock Lock(Self->CompletedStampSheetsMutex.Get());
            TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr> Remaining;
            for (const auto& Notification : *Self->CompletedStampSheets)
            {
                if (Notification.IsValid() && Notification->GetUserId().IsSet() && *Notification->GetUserId() == TargetUserId)
                {
                    StampSheets.Add(Notification);
                }
                else
                {
                    Remaining.Add(Notification);
                }
            }
            *Self->CompletedStampSheets = MoveTemp(Remaining);
        }
        {
            FScopeLock Lock(Self->CompletedTransactionsMutex.Get());
            TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr> Remaining;
            for (const auto& Notification : *Self->CompletedTransactions)
            {
                if (Notification.IsValid() && Notification->GetUserId().IsSet() && *Notification->GetUserId() == TargetUserId)
                {
                    Transactions.Add(Notification);
                }
                else
                {
                    Remaining.Add(Notification);
                }
            }
            *Self->CompletedTransactions = MoveTemp(Remaining);
        }

        for (const auto& CompletedStampSheet : StampSheets)
        {
            if (!CompletedStampSheet.IsValid() || !CompletedStampSheet->GetNamespaceName().IsSet() || !CompletedStampSheet->GetTransactionId().IsSet())
            {
                continue;
            }
            Gs2::Distributor::Model::Cache::FStampSheetResultCache::Delete(
                Self->Gs2->Cache,
                CompletedStampSheet->GetNamespaceName(),
                AccessToken->GetUserId(),
                CompletedStampSheet->GetTransactionId(),
                AccessToken->GetTimeOffset()
            );
            const auto Future = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                AccessToken,
                true,
                *CompletedStampSheet->GetTransactionId(),
                FString(""),
                FString(""),
                false,
                nullptr,
                CompletedStampSheet->GetNamespaceName()
            )->Wait();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    continue;
                }
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
        }

        for (const auto& CompletedTransaction : Transactions)
        {
            if (!CompletedTransaction.IsValid() || !CompletedTransaction->GetNamespaceName().IsSet() || !CompletedTransaction->GetTransactionId().IsSet())
            {
                continue;
            }
            Gs2::Distributor::Model::Cache::FTransactionResultCache::Delete(
                Self->Gs2->Cache,
                CompletedTransaction->GetNamespaceName(),
                AccessToken->GetUserId(),
                CompletedTransaction->GetTransactionId(),
                AccessToken->GetTimeOffset()
            );
            {
                const auto Future = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                    Self->Gs2,
                    AccessToken,
                    true,
                    *CompletedTransaction->GetTransactionId(),
                    FString(""),
                    FString(""),
                    true,
                    nullptr,
                    CompletedTransaction->GetNamespaceName()
                )->Wait();
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                    {
                        continue;
                    }
                    return Future->GetTask().Error();
                }
                Future->EnsureCompletion();
            }
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DistributorDomain::FDispatchTask>> FGs2DistributorDomain::Dispatch(
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGs2DistributorDomain::FDispatchTask>>(this->AsShared(), AccessToken);
    }

    FGs2DistributorDomain::FDispatchByUserIdTask::FDispatchByUserIdTask(
        const TSharedPtr<FGs2DistributorDomain> Self,
        const FString UserId
    ):
        Self(Self),
        UserId(UserId)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DistributorDomain::FDispatchByUserIdTask::Action(
        TSharedPtr<TSharedPtr<FGs2DistributorDomain>> Result
    )
    {
        TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr> StampSheets;
        TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr> Transactions;

        {
            FScopeLock Lock(Self->CompletedStampSheetsMutex.Get());
            TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr> Remaining;
            for (const auto& Notification : *Self->CompletedStampSheets)
            {
                if (Notification.IsValid() && Notification->GetUserId().IsSet() && *Notification->GetUserId() == UserId)
                {
                    StampSheets.Add(Notification);
                }
                else
                {
                    Remaining.Add(Notification);
                }
            }
            *Self->CompletedStampSheets = MoveTemp(Remaining);
        }
        {
            FScopeLock Lock(Self->CompletedTransactionsMutex.Get());
            TArray<Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr> Remaining;
            for (const auto& Notification : *Self->CompletedTransactions)
            {
                if (Notification.IsValid() && Notification->GetUserId().IsSet() && *Notification->GetUserId() == UserId)
                {
                    Transactions.Add(Notification);
                }
                else
                {
                    Remaining.Add(Notification);
                }
            }
            *Self->CompletedTransactions = MoveTemp(Remaining);
        }

        for (const auto& CompletedStampSheet : StampSheets)
        {
            if (!CompletedStampSheet.IsValid() || !CompletedStampSheet->GetNamespaceName().IsSet() || !CompletedStampSheet->GetTransactionId().IsSet())
            {
                continue;
            }
            Gs2::Distributor::Model::Cache::FStampSheetResultCache::Delete(
                Self->Gs2->Cache,
                CompletedStampSheet->GetNamespaceName(),
                UserId,
                CompletedStampSheet->GetTransactionId(),
                TOptional<int32>()
            );
            {
                const auto Future = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                    Self->Gs2,
                    UserId,
                    true,
                    *CompletedStampSheet->GetTransactionId(),
                    FString(""),
                    FString(""),
                    false,
                    nullptr,
                    CompletedStampSheet->GetNamespaceName()
                )->Wait();
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    if (Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
                    {
                        continue;
                    }
                    return Future->GetTask().Error();
                }
                Future->EnsureCompletion();
            }
        }

        for (const auto& CompletedTransaction : Transactions)
        {
            if (!CompletedTransaction.IsValid() || !CompletedTransaction->GetNamespaceName().IsSet() || !CompletedTransaction->GetTransactionId().IsSet())
            {
                continue;
            }
            Gs2::Distributor::Model::Cache::FTransactionResultCache::Delete(
                Self->Gs2->Cache,
                CompletedTransaction->GetNamespaceName(),
                UserId,
                CompletedTransaction->GetTransactionId(),
                TOptional<int32>()
            );
            {
                const auto Future = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                    Self->Gs2,
                    UserId,
                    true,
                    *CompletedTransaction->GetTransactionId(),
                    FString(""),
                    FString(""),
                    true,
                    nullptr,
                    CompletedTransaction->GetNamespaceName()
                )->Wait();
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    if (Future->GetTask().Error()->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
                    {
                        continue;
                    }
                    return Future->GetTask().Error();
                }
                Future->EnsureCompletion();
            }
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DistributorDomain::FDispatchByUserIdTask>> FGs2DistributorDomain::DispatchByUserId(
        const FString UserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGs2DistributorDomain::FDispatchByUserIdTask>>(this->AsShared(), UserId);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
