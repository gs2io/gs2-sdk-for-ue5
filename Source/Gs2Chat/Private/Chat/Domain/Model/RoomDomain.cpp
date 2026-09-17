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

#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/CategoryModel.h"
#include "Chat/Domain/Model/CategoryModelMaster.h"
#include "Chat/Domain/Model/CurrentModelMaster.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"
#include "Chat/Model/Cache/Room.h"
#include "Chat/Model/Cache/Message.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FRoomDomain::FRoomDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RoomName(RoomName),
        Password(Password),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Room"
        ))
    {
    }

    FRoomDomain::FRoomDomain(
        const FRoomDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        RoomName(From.RoomName),
        Password(From.Password),
        ParentKey(From.ParentKey)
    {

    }

    FRoomDomain::FGetTask::FGetTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FGetRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->GetRoom(
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


        Gs2::Chat::Model::Cache::FRoomCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetRoomName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FGetTask>> FRoomDomain::Get(
        Request::FGetRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FUpdateFromBackendTask::FUpdateFromBackendTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FUpdateRoomFromBackendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FUpdateFromBackendTask::FUpdateFromBackendTask(
        const FUpdateFromBackendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FUpdateFromBackendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateRoomFromBackend(
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


        Gs2::Chat::Model::Cache::FRoomCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetRoomName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FUpdateFromBackendTask>> FRoomDomain::UpdateFromBackend(
        Request::FUpdateRoomFromBackendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromBackendTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FDeleteFromBackendTask::FDeleteFromBackendTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FDeleteRoomFromBackendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FDeleteFromBackendTask::FDeleteFromBackendTask(
        const FDeleteFromBackendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FDeleteFromBackendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteRoomFromBackend(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Chat::Model::Cache::FRoomCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetRoomName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FDeleteFromBackendTask>> FRoomDomain::DeleteFromBackend(
        Request::FDeleteRoomFromBackendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFromBackendTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FPostTask::FPostTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FPostByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithUserId(Self->UserId)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->PostByUserId(
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
        Gs2::Chat::Model::Cache::FMessageCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetRoomName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FMessageDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetRoomName(),
            Request->GetPassword(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FPostTask>> FRoomDomain::Post(
        Request::FPostByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(this->AsShared(), Request);
    }

    Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr FRoomDomain::Messages(
        const TOptional<int32> Category,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RoomName,
            Password,
            Category,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRoomDomain::SubscribeMessages(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RoomName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRoomDomain::UnsubscribeMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RoomName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRoomDomain::FCollectMessagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FMessagePtr>>, public TSharedFromThis<FCollectMessagesTask>
    {
        const TSharedPtr<FRoomDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected;
    const TOptional<int32> QueryCategory;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectMessagesTask(const TSharedPtr<FRoomDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryCategory(Category), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectMessagesTask(const FCollectMessagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryCategory(From.QueryCategory), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FMessagePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FMessagePtr> Items;
            auto Iterator = Self->Messages(QueryCategory, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Chat::Model::FMessagePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FRoomDomain::SubscribeMessages(
        TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryRoomName = RoomName;
        const auto QueryPassword = Password;
        const auto QueryCategory = Category;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RoomName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Chat::Model::FMessage::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Chat::Model::FMessagePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Chat::Model::FMessage>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryRoomName, QueryPassword, QueryCategory, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FRoomDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryRoomName, QueryPassword);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Domain, Callback, QueryCategory, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRoomDomain::InvalidateMessages(const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RoomName,
        TOptional<int32>()
    )
        );
    }

    FRoomDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const TSharedPtr<FRoomDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryCategory(Category), QueryTimeOffsetToken(TimeOffsetToken) {}
    FRoomDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const FSubscribeMessagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryCategory(From.QueryCategory), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FSubscribeMessagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)>(), QueryCategory, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMessages(Callback, QueryCategory, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRoomDomain::FSubscribeMessagesWithInitialCallTask>> FRoomDomain::SubscribeMessagesWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMessagesWithInitialCallTask>>(this->AsShared(), Callback, Category, TimeOffsetToken);
    }

    Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesByUserIdIteratorPtr FRoomDomain::LatestMessages(
        const TOptional<int32> Category,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RoomName,
            Password,
            Category,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRoomDomain::SubscribeLatestMessages(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RoomName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRoomDomain::UnsubscribeLatestMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                RoomName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRoomDomain::FCollectLatestMessagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FMessagePtr>>, public TSharedFromThis<FCollectLatestMessagesTask>
    {
        const TSharedPtr<FRoomDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected;
    const TOptional<int32> QueryCategory;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectLatestMessagesTask(const TSharedPtr<FRoomDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryCategory(Category), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectLatestMessagesTask(const FCollectLatestMessagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryCategory(From.QueryCategory), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FMessagePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FMessagePtr> Items;
            auto Iterator = Self->LatestMessages(QueryCategory, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Chat::Model::FMessagePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FRoomDomain::SubscribeLatestMessages(
        TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryRoomName = RoomName;
        const auto QueryPassword = Password;
        const auto QueryCategory = Category;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RoomName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Chat::Model::FMessage::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Chat::Model::FMessagePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Chat::Model::FMessage>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryRoomName, QueryPassword, QueryCategory, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FRoomDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryRoomName, QueryPassword);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLatestMessagesTask>>(Domain, Callback, QueryCategory, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRoomDomain::InvalidateLatestMessages(const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        RoomName,
        TOptional<int32>()
    )
        );
    }

    FRoomDomain::FSubscribeLatestMessagesWithInitialCallTask::FSubscribeLatestMessagesWithInitialCallTask(const TSharedPtr<FRoomDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryCategory(Category), QueryTimeOffsetToken(TimeOffsetToken) {}
    FRoomDomain::FSubscribeLatestMessagesWithInitialCallTask::FSubscribeLatestMessagesWithInitialCallTask(const FSubscribeLatestMessagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryCategory(From.QueryCategory), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FSubscribeLatestMessagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLatestMessagesTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)>(), QueryCategory, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLatestMessages(Callback, QueryCategory, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRoomDomain::FSubscribeLatestMessagesWithInitialCallTask>> FRoomDomain::SubscribeLatestMessagesWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLatestMessagesWithInitialCallTask>>(this->AsShared(), Callback, Category, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain> FRoomDomain::Message(
        const FString MessageName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FMessageDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RoomName,
            Password,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    FString FRoomDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RoomName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RoomName.IsSet() ? *RoomName : "null") + ":" +
            ChildType;
    }

    FString FRoomDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString("") +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FRoomDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoomDomain> Self
    ): Self(Self)
    {

    }

    FRoomDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        const auto CacheParentKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheKey(

            Self->RoomName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Chat::Model::FRoom::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Chat::Model::FRoomPtr Value;
                const auto CacheHit = Gs2::Chat::Model::Cache::FRoomCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->RoomName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Chat::Model::Cache::FRoomCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->RoomName,
                    TOptional<int32>(),
                    [Self](Gs2::Chat::Model::FRoomPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Chat::Request::FGetRoomRequest>()
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

    TSharedPtr<FAsyncTask<FRoomDomain::FModelTask>> FRoomDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoomDomain::FModelTask>>(this->AsShared());
    }

    void FRoomDomain::Invalidate()
    {
        Gs2::Chat::Model::Cache::FRoomCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            RoomName,
            TOptional<int32>()
        );
    }

    FRoomDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRoomDomain>& Self,
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRoomDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRoomDomain::FSubscribeWithInitialCallTask>> FRoomDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRoomDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheKey(

            RoomName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryRoomName = RoomName;
        const TOptional<FString> QueryPassword = Password;
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FRoom>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryRoomName, QueryPassword]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRoomDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryRoomName,
                    QueryPassword
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRoomDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheKey(

            RoomName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Chat::Model::FRoom::TypeName,
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
