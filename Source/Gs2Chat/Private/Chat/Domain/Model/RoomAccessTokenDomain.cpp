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

#include "Chat/Domain/Model/RoomAccessToken.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FRoomAccessTokenDomain::FRoomAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RoomName(RoomName),
        Password(Password),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Room"
        ))
    {
    }

    FRoomAccessTokenDomain::FRoomAccessTokenDomain(
        const FRoomAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RoomName(From.RoomName),
        Password(From.Password),
        ParentKey(From.ParentKey)
    {

    }

    FRoomAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FUpdateRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->UpdateRoom(
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
            (CacheOwnerSnapshotUserId),
            Request->GetRoomName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FUpdateTask>> FRoomAccessTokenDomain::Update(
        Request::FUpdateRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FDeleteRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeleteRoom(
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
            (CacheOwnerSnapshotUserId),
            Request->GetRoomName(),
            CacheOwnerSnapshotTimeOffset
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FDeleteTask>> FRoomAccessTokenDomain::Delete(
        Request::FDeleteRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FPostTask::FPostTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FPostRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPassword(Self->Password);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->Post(
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
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetRoomName(),
            ResultModel->GetItem()->GetName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetRoomName(),
            Request->GetPassword(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FPostTask>> FRoomAccessTokenDomain::Post(
        Request::FPostRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FGetRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName);
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
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
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FGetTask>> FRoomAccessTokenDomain::Get(
        Request::FGetRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Chat::Domain::Iterator::FDescribeMessagesIteratorPtr FRoomAccessTokenDomain::Messages(
        const TOptional<int32> Category
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeMessagesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RoomName,
            Password,
            Category
        );
    }

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::SubscribeMessages(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RoomName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRoomAccessTokenDomain::UnsubscribeMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RoomName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRoomAccessTokenDomain::FCollectMessagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FMessagePtr>>, public TSharedFromThis<FCollectMessagesTask>
    {
        const TSharedPtr<FRoomAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected;
    const TOptional<int32> QueryCategory;
    public:
        explicit FCollectMessagesTask(const TSharedPtr<FRoomAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected,const TOptional<int32> Category) : Self(Self), OnCollected(OnCollected), QueryCategory(Category) {}
        FCollectMessagesTask(const FCollectMessagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryCategory(From.QueryCategory) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FMessagePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FMessagePtr> Items;
            auto Iterator = Self->Messages(QueryCategory)->begin();
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

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::SubscribeMessages(
        TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRoomName = RoomName;
        const auto QueryPassword = Password;
        const auto QueryCategory = Category;
        const auto Parent = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RoomName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRoomName, QueryPassword, QueryCategory, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FRoomAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot, QueryRoomName, QueryPassword);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Domain, Callback, QueryCategory);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRoomAccessTokenDomain::InvalidateMessages(const TOptional<int32> Category)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RoomName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FRoomAccessTokenDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const TSharedPtr<FRoomAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category) : Self(Self), Callback(Callback), QueryCategory(Category) {}
    FRoomAccessTokenDomain::FSubscribeMessagesWithInitialCallTask::FSubscribeMessagesWithInitialCallTask(const FSubscribeMessagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryCategory(From.QueryCategory) {}
    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FSubscribeMessagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMessagesTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)>(), QueryCategory);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMessages(Callback, QueryCategory);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FSubscribeMessagesWithInitialCallTask>> FRoomAccessTokenDomain::SubscribeMessagesWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMessagesWithInitialCallTask>>(this->AsShared(), Callback, Category);
    }

    Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIteratorPtr FRoomAccessTokenDomain::LatestMessages(
        const TOptional<int32> Category
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RoomName,
            Password,
            Category
        );
    }

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::SubscribeLatestMessages(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RoomName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FRoomAccessTokenDomain::UnsubscribeLatestMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                RoomName,
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FRoomAccessTokenDomain::FCollectLatestMessagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FMessagePtr>>, public TSharedFromThis<FCollectLatestMessagesTask>
    {
        const TSharedPtr<FRoomAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected;
    const TOptional<int32> QueryCategory;
    public:
        explicit FCollectLatestMessagesTask(const TSharedPtr<FRoomAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> OnCollected,const TOptional<int32> Category) : Self(Self), OnCollected(OnCollected), QueryCategory(Category) {}
        FCollectLatestMessagesTask(const FCollectLatestMessagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryCategory(From.QueryCategory) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FMessagePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FMessagePtr> Items;
            auto Iterator = Self->LatestMessages(QueryCategory)->begin();
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

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::SubscribeLatestMessages(
        TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRoomName = RoomName;
        const auto QueryPassword = Password;
        const auto QueryCategory = Category;
        const auto Parent = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RoomName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRoomName, QueryPassword, QueryCategory, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FRoomAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot, QueryRoomName, QueryPassword);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLatestMessagesTask>>(Domain, Callback, QueryCategory);
                Task->StartBackgroundTask();
            }
        );
    }

    void FRoomAccessTokenDomain::InvalidateLatestMessages(const TOptional<int32> Category)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        RoomName,
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FRoomAccessTokenDomain::FSubscribeLatestMessagesWithInitialCallTask::FSubscribeLatestMessagesWithInitialCallTask(const TSharedPtr<FRoomAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category) : Self(Self), Callback(Callback), QueryCategory(Category) {}
    FRoomAccessTokenDomain::FSubscribeLatestMessagesWithInitialCallTask::FSubscribeLatestMessagesWithInitialCallTask(const FSubscribeLatestMessagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryCategory(From.QueryCategory) {}
    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FSubscribeLatestMessagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLatestMessagesTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)>(), QueryCategory);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLatestMessages(Callback, QueryCategory);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FSubscribeLatestMessagesWithInitialCallTask>> FRoomAccessTokenDomain::SubscribeLatestMessagesWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FMessagePtr>)> Callback,const TOptional<int32> Category)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLatestMessagesWithInitialCallTask>>(this->AsShared(), Callback, Category);
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain> FRoomAccessTokenDomain::Message(
        const FString MessageName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RoomName,
            Password,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    FString FRoomAccessTokenDomain::CreateCacheParentKey(
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

    FString FRoomAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString("") +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FRoomAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoomAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRoomAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        const auto CacheParentKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
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
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->RoomName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
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
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->RoomName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
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

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FModelTask>> FRoomAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoomAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FRoomAccessTokenDomain::Invalidate()
    {
        Gs2::Chat::Model::Cache::FRoomCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            RoomName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FRoomAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRoomAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FSubscribeWithInitialCallTask>> FRoomAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheKey(

            RoomName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRoomName = RoomName;
        const TOptional<FString> QueryPassword = Password;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FRoom>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRoomName, QueryPassword, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FRoomAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryRoomName,
                    QueryPassword
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRoomAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
