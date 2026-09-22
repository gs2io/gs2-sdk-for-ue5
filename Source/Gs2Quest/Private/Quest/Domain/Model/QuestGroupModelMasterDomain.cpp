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

#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"
#include "Quest/Model/Cache/QuestGroupModelMaster.h"
#include "Quest/Model/Cache/QuestModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestGroupModelMasterDomain::FQuestGroupModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Quest::Domain::FGs2QuestDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        ParentKey(Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "QuestGroupModelMaster"
        ))
    {
    }

    FQuestGroupModelMasterDomain::FQuestGroupModelMasterDomain(
        const FQuestGroupModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        QuestGroupName(From.QuestGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FQuestGroupModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestGroupModelMasterDomain>& Self,
        const Request::FGetQuestGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->GetQuestGroupModelMaster(
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


        Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetQuestGroupName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FGetTask>> FQuestGroupModelMasterDomain::Get(
        Request::FGetQuestGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FQuestGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FQuestGroupModelMasterDomain>& Self,
        const Request::FUpdateQuestGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->UpdateQuestGroupModelMaster(
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


        Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetQuestGroupName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FUpdateTask>> FQuestGroupModelMasterDomain::Update(
        Request::FUpdateQuestGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FQuestGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FQuestGroupModelMasterDomain>& Self,
        const Request::FDeleteQuestGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->DeleteQuestGroupModelMaster(
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


              Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetQuestGroupName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FDeleteTask>> FQuestGroupModelMasterDomain::Delete(
        Request::FDeleteQuestGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask::FCreateQuestModelMasterTask(
        const TSharedPtr<FQuestGroupModelMasterDomain>& Self,
        const Request::FCreateQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask::FCreateQuestModelMasterTask(
        const FCreateQuestModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->CreateQuestModelMaster(
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
        Gs2::Quest::Model::Cache::FQuestModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetQuestGroupName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetQuestGroupName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask>> FQuestGroupModelMasterDomain::CreateQuestModelMaster(
        Request::FCreateQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateQuestModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIteratorPtr FQuestGroupModelMasterDomain::QuestModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            QuestGroupName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FQuestGroupModelMasterDomain::SubscribeQuestModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
            Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                QuestGroupName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FQuestGroupModelMasterDomain::UnsubscribeQuestModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
            Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                QuestGroupName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FQuestGroupModelMasterDomain::FCollectQuestModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Quest::Model::FQuestModelMasterPtr>>, public TSharedFromThis<FCollectQuestModelMastersTask>
    {
        const TSharedPtr<FQuestGroupModelMasterDomain> Self;
        const TFunction<void(TArray<Gs2::Quest::Model::FQuestModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectQuestModelMastersTask(const TSharedPtr<FQuestGroupModelMasterDomain>& Self, TFunction<void(TArray<Gs2::Quest::Model::FQuestModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectQuestModelMastersTask(const FCollectQuestModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Quest::Model::FQuestModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Quest::Model::FQuestModelMasterPtr> Items;
            auto Iterator = Self->QuestModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Quest::Model::FQuestModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FQuestGroupModelMasterDomain::SubscribeQuestModelMasters(
        TFunction<void(TArray<Gs2::Quest::Model::FQuestModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Quest::Domain::FGs2QuestDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryQuestGroupName = QuestGroupName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        QuestGroupName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Quest::Model::FQuestModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Quest::Model::FQuestModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryQuestGroupName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FQuestGroupModelMasterDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryQuestGroupName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectQuestModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FQuestGroupModelMasterDomain::InvalidateQuestModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
            Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        QuestGroupName,
        TOptional<int32>()
    )
        );
    }

    FQuestGroupModelMasterDomain::FSubscribeQuestModelMastersWithInitialCallTask::FSubscribeQuestModelMastersWithInitialCallTask(const TSharedPtr<FQuestGroupModelMasterDomain>& Self, TFunction<void(TArray<Gs2::Quest::Model::FQuestModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FQuestGroupModelMasterDomain::FSubscribeQuestModelMastersWithInitialCallTask::FSubscribeQuestModelMastersWithInitialCallTask(const FSubscribeQuestModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FSubscribeQuestModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectQuestModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Quest::Model::FQuestModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeQuestModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FSubscribeQuestModelMastersWithInitialCallTask>> FQuestGroupModelMasterDomain::SubscribeQuestModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Quest::Model::FQuestModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeQuestModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain> FQuestGroupModelMasterDomain::QuestModelMaster(
        const FString QuestName
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            QuestGroupName,
            QuestName == TEXT("") ? TOptional<FString>() : TOptional<FString>(QuestName)
        );
    }

    FString FQuestGroupModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> QuestGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            ChildType;
    }

    FString FQuestGroupModelMasterDomain::CreateCacheKey(
        TOptional<FString> QuestGroupName
    )
    {
        return FString("") +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null");
    }

    FQuestGroupModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestGroupModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FQuestGroupModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::CreateCacheKey(

            Self->QuestGroupName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Quest::Model::FQuestGroupModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Quest::Model::FQuestGroupModelMasterPtr Value;
                const auto CacheHit = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->QuestGroupName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->QuestGroupName,
                    TOptional<int32>(),
                    [Self](Gs2::Quest::Model::FQuestGroupModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Quest::Request::FGetQuestGroupModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FModelTask>> FQuestGroupModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestGroupModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FQuestGroupModelMasterDomain::Invalidate()
    {
        Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            QuestGroupName,
            TOptional<int32>()
        );
    }

    FQuestGroupModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FQuestGroupModelMasterDomain>& Self,
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FQuestGroupModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FSubscribeWithInitialCallTask>> FQuestGroupModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FQuestGroupModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::CreateCacheKey(

            QuestGroupName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Quest::Domain::FGs2QuestDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryQuestGroupName = QuestGroupName;
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FQuestGroupModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryQuestGroupName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FQuestGroupModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryQuestGroupName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FQuestGroupModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestGroupModelMasterCache::CreateCacheKey(

            QuestGroupName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FQuestGroupModelMaster::TypeName,
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
