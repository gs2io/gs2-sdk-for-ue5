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
#include "Inbox/Model/Cache/Message.h"
#include "Inbox/Model/Cache/Received.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserDomain::FSendMessageTask::FSendMessageTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FSendMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendMessageTask::FSendMessageTask(
        const FSendMessageTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendMessageTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendMessageByUserId(
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
        Gs2::Inbox::Model::Cache::FMessageCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendMessageTask>> FUserDomain::SendMessage(
        Request::FSendMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendMessageTask>>(this->AsShared(), Request);
    }

    FUserDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FReceiveGlobalMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FReceiveGlobalMessageTask::FReceiveGlobalMessageTask(
        const FReceiveGlobalMessageTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FReceiveGlobalMessageTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ReceiveGlobalMessageByUserId(
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
                    Request->GetNamespaceName(), Request->GetUserId(), Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
        }
        Self->Gs2->Cache->ClearListCache(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
                Request->GetNamespaceName(),
                Request->GetUserId(),
                TOptional<int32>()
            )
        );
        Gs2::Inbox::Model::Cache::FReceivedCache::Delete(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            TOptional<int32>()
        );

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItem()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItem())[i]->GetUserId(),
                    (*ResultModel->GetItem())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FReceiveGlobalMessageTask>> FUserDomain::ReceiveGlobalMessage(
        Request::FReceiveGlobalMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveGlobalMessageTask>>(this->AsShared(), Request);
    }

    FUserDomain::FBatchReadMessagesTask::FBatchReadMessagesTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FBatchReadMessagesByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FBatchReadMessagesTask::FBatchReadMessagesTask(
        const FBatchReadMessagesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FBatchReadMessagesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->BatchReadMessagesByUserId(
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
                    Request->GetNamespaceName(), Request->GetUserId(), Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
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
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FBatchReadMessagesTask>> FUserDomain::BatchReadMessages(
        Request::FBatchReadMessagesByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchReadMessagesTask>>(this->AsShared(), Request);
    }

    Gs2::Inbox::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr FUserDomain::Messages(
        const TOptional<bool> IsRead,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Iterator::FDescribeMessagesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            IsRead,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeMessages(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectMessagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inbox::Model::FMessagePtr>>, public TSharedFromThis<FCollectMessagesTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> OnCollected;
    const TOptional<bool> QueryIsRead;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectMessagesTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> OnCollected,const TOptional<bool> IsRead,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryIsRead(IsRead), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectMessagesTask(const FCollectMessagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryIsRead(From.QueryIsRead), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Inbox::Model::FMessagePtr>>> Result) override
        {
            TArray<Gs2::Inbox::Model::FMessagePtr> Items;
            auto Iterator = Self->Messages(QueryIsRead, QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeMessages(
        TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> Callback,const TOptional<bool> IsRead,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Inbox::Domain::FGs2InboxDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryIsRead = IsRead;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryIsRead, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Domain, Callback, QueryIsRead, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateMessages(const TOptional<bool> IsRead,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Inbox::Model::FMessage::TypeName,
            Gs2::Inbox::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> Callback,const TOptional<bool> IsRead,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryIsRead(IsRead), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const FSubscribeMessagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryIsRead(From.QueryIsRead), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeMessagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Self, TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)>(), QueryIsRead, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMessages(Callback, QueryIsRead, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeMessagesWithInitialCallTask>> FUserDomain::SubscribeMessagesWithInitialCall(TFunction<void(TArray<Gs2::Inbox::Model::FMessagePtr>)> Callback,const TOptional<bool> IsRead,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMessagesWithInitialCallTask>>(this->AsShared(), Callback, IsRead, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FMessageDomain> FUserDomain::Message(
        const FString MessageName
    )
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FMessageDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain> FUserDomain::Received(
    )
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FReceivedDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
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
