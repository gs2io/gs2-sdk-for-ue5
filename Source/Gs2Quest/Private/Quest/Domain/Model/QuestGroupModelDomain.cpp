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

#include "Quest/Domain/Model/QuestGroupModel.h"
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
#include "Quest/Model/Cache/QuestGroupModel.h"
#include "Quest/Model/Cache/QuestModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestGroupModelDomain::FQuestGroupModelDomain(
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
            "QuestGroupModel"
        ))
    {
    }

    FQuestGroupModelDomain::FQuestGroupModelDomain(
        const FQuestGroupModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        QuestGroupName(From.QuestGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FQuestGroupModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestGroupModelDomain>& Self,
        const Request::FGetQuestGroupModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->GetQuestGroupModel(
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


        Gs2::Quest::Model::Cache::FQuestGroupModelCache::Put(
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

    TSharedPtr<FAsyncTask<FQuestGroupModelDomain::FGetTask>> FQuestGroupModelDomain::Get(
        Request::FGetQuestGroupModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIteratorPtr FQuestGroupModelDomain::QuestModels(
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            QuestGroupName
        );
    }

    Gs2::Core::Domain::CallbackID FQuestGroupModelDomain::SubscribeQuestModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(
                NamespaceName,
                QuestGroupName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FQuestGroupModelDomain::UnsubscribeQuestModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(
                NamespaceName,
                QuestGroupName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FQuestGroupModelDomain::FCollectQuestModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Quest::Model::FQuestModelPtr>>, public TSharedFromThis<FCollectQuestModelsTask>
    {
        const TSharedPtr<FQuestGroupModelDomain> Self;
        const TFunction<void(TArray<Gs2::Quest::Model::FQuestModelPtr>)> OnCollected;

    public:
        explicit FCollectQuestModelsTask(const TSharedPtr<FQuestGroupModelDomain>& Self, TFunction<void(TArray<Gs2::Quest::Model::FQuestModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectQuestModelsTask(const FCollectQuestModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Quest::Model::FQuestModelPtr>>> Result) override
        {
            TArray<Gs2::Quest::Model::FQuestModelPtr> Items;
            auto Iterator = Self->QuestModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Quest::Model::FQuestModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FQuestGroupModelDomain::SubscribeQuestModels(
        TFunction<void(TArray<Gs2::Quest::Model::FQuestModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Quest::Domain::FGs2QuestDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryQuestGroupName = QuestGroupName;
        const auto Parent = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(
        NamespaceName,
        QuestGroupName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Quest::Model::FQuestModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Quest::Model::FQuestModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Quest::Model::FQuestModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryQuestGroupName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FQuestGroupModelDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryQuestGroupName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectQuestModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FQuestGroupModelDomain::InvalidateQuestModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Quest::Model::FQuestModel::TypeName,
            Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(
        NamespaceName,
        QuestGroupName,
        TOptional<int32>()
    )
        );
    }

    FQuestGroupModelDomain::FSubscribeQuestModelsWithInitialCallTask::FSubscribeQuestModelsWithInitialCallTask(const TSharedPtr<FQuestGroupModelDomain>& Self, TFunction<void(TArray<Gs2::Quest::Model::FQuestModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FQuestGroupModelDomain::FSubscribeQuestModelsWithInitialCallTask::FSubscribeQuestModelsWithInitialCallTask(const FSubscribeQuestModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelDomain::FSubscribeQuestModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectQuestModelsTask>>(Self, TFunction<void(TArray<Gs2::Quest::Model::FQuestModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeQuestModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FQuestGroupModelDomain::FSubscribeQuestModelsWithInitialCallTask>> FQuestGroupModelDomain::SubscribeQuestModelsWithInitialCall(TFunction<void(TArray<Gs2::Quest::Model::FQuestModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeQuestModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelDomain> FQuestGroupModelDomain::QuestModel(
        const FString QuestName
    )
    {
        return MakeShared<Gs2::Quest::Domain::Model::FQuestModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            QuestGroupName,
            QuestName == TEXT("") ? TOptional<FString>() : TOptional<FString>(QuestName)
        );
    }

    FString FQuestGroupModelDomain::CreateCacheParentKey(
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

    FString FQuestGroupModelDomain::CreateCacheKey(
        TOptional<FString> QuestGroupName
    )
    {
        return FString("") +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null");
    }

    FQuestGroupModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestGroupModelDomain> Self
    ): Self(Self)
    {

    }

    FQuestGroupModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Quest::Model::Cache::FQuestGroupModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Quest::Model::Cache::FQuestGroupModelCache::CreateCacheKey(

            Self->QuestGroupName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Quest::Model::FQuestGroupModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Quest::Model::FQuestGroupModelPtr Value;
                const auto CacheHit = Gs2::Quest::Model::Cache::FQuestGroupModelCache::TryGet(
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
                const auto Error = Gs2::Quest::Model::Cache::FQuestGroupModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->QuestGroupName,
                    TOptional<int32>(),
                    [Self](Gs2::Quest::Model::FQuestGroupModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Quest::Request::FGetQuestGroupModelRequest>()
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

    TSharedPtr<FAsyncTask<FQuestGroupModelDomain::FModelTask>> FQuestGroupModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestGroupModelDomain::FModelTask>>(this->AsShared());
    }

    void FQuestGroupModelDomain::Invalidate()
    {
        Gs2::Quest::Model::Cache::FQuestGroupModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            QuestGroupName,
            TOptional<int32>()
        );
    }

    FQuestGroupModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FQuestGroupModelDomain>& Self,
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FQuestGroupModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FQuestGroupModelDomain::FSubscribeWithInitialCallTask>> FQuestGroupModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FQuestGroupModelDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FQuestGroupModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestGroupModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestGroupModelCache::CreateCacheKey(

            QuestGroupName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Quest::Domain::FGs2QuestDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryQuestGroupName = QuestGroupName;
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FQuestGroupModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FQuestGroupModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryQuestGroupName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FQuestGroupModelDomain>(
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

    void FQuestGroupModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestGroupModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestGroupModelCache::CreateCacheKey(

            QuestGroupName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FQuestGroupModel::TypeName,
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
