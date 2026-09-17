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

#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"
#include "Inbox/Domain/SpeculativeExecutor/Transaction/BatchReadMessagesByUserIdSpeculativeExecutor.h"
#include "Inbox/Model/Cache/Message.h"
#include "Inbox/Model/Cache/Received.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserAccessTokenDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FReceiveGlobalMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const FReceiveGlobalMessageTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FReceiveGlobalMessageTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->ReceiveGlobalMessage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItem())
            {
                if (!Item.IsValid()) continue;
                Gs2::Inbox::Model::Cache::FMessageCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Item->GetName(),
                    CacheOwnerSnapshotTimeOffset, Item
                );
            }
        }
        Self->Gs2->Cache->ClearListCache(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
                Request->GetNamespaceName(),
                CacheOwnerSnapshotUserId,
                CacheOwnerSnapshotTimeOffset
            )
        );
        Gs2::Inbox::Model::Cache::FReceivedCache::Delete(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            CacheOwnerSnapshotUserId,
            CacheOwnerSnapshotTimeOffset
        );

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItem()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItem())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FReceiveGlobalMessageTask>> FUserAccessTokenDomain::ReceiveGlobalMessage(
        Request::FReceiveGlobalMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveGlobalMessageTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FBatchReadMessagesTask::FBatchReadMessagesTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FBatchReadMessagesRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FUserAccessTokenDomain::FBatchReadMessagesTask::FBatchReadMessagesTask(
        const FBatchReadMessagesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FBatchReadMessagesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->BatchReadMessages(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Inbox::Model::Cache::FMessageCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Item->GetName(),
                    CacheOwnerSnapshotTimeOffset, Item
                );
            }
        }

        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            Self->AccessToken,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            ResultModel->GetTransactionId().IsSet() ? *ResultModel->GetTransactionId() : FString(),
            ResultModel->GetStampSheet().IsSet() ? *ResultModel->GetStampSheet() : FString(),
            ResultModel->GetStampSheetEncryptionKeyId().IsSet() ? *ResultModel->GetStampSheetEncryptionKeyId() : FString(),
            ResultModel->GetAtomicCommit().IsSet() ? *ResultModel->GetAtomicCommit() : false,
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FBatchReadMessagesTask>> FUserAccessTokenDomain::BatchReadMessages(
        Request::FBatchReadMessagesRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchReadMessagesTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    Gs2::Inbox::Domain::Iterator::FDescribeMessagesIteratorPtr FUserAccessTokenDomain::Messages(
        const TOptional<bool> IsRead
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Iterator::FDescribeMessagesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            IsRead
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeMessages(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectMessagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inbox::Model::FMessagePtr>>, public TSharedFromThis<FCollectMessagesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> OnCollected;
    const TOptional<bool> QueryIsRead;
    public:
        explicit FCollectMessagesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> OnCollected,const TOptional<bool> IsRead) : Self(Self), OnCollected(OnCollected), QueryIsRead(IsRead) {}
        FCollectMessagesTask(const FCollectMessagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryIsRead(From.QueryIsRead) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Inbox::Model::FMessagePtr>>> Result) override
        {
            TArray<Gs2::Inbox::Model::FMessagePtr> Items;
            auto Iterator = Self->Messages(QueryIsRead)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Inbox::Model::FMessagePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeMessages(
        TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> Callback,const TOptional<bool> IsRead
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Inbox::Domain::FGs2InboxDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryIsRead = IsRead;
        const auto Parent = Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Inbox::Model::FMessage::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Inbox::Model::FMessagePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Inbox::Model::FMessage>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryIsRead, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Domain, Callback, QueryIsRead);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateMessages(const TOptional<bool> IsRead)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> Callback,const TOptional<bool> IsRead) : Self(Self), Callback(Callback), QueryIsRead(IsRead) {}
    FUserAccessTokenDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const FSubscribeMessagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryIsRead(From.QueryIsRead) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeMessagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Self, TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)>(), QueryIsRead);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMessages(Callback, QueryIsRead);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeMessagesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeMessagesWithInitialCall(TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> Callback,const TOptional<bool> IsRead)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMessagesWithInitialCallTask>>(this->AsShared(), Callback, IsRead);
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain> FUserAccessTokenDomain::Message(
        const FString MessageName
    )
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FMessageAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedAccessTokenDomain> FUserAccessTokenDomain::Received(
    )
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FReceivedAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
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
