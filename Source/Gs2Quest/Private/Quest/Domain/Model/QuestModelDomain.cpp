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

#include "Quest/Domain/Model/QuestModel.h"
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
#include "Quest/Model/Cache/QuestModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestModelDomain::FQuestModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Quest::Domain::FGs2QuestDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName,
        const TOptional<FString> QuestName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        QuestName(QuestName),
        ParentKey(Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
            NamespaceName,
            QuestGroupName,
            "QuestModel"
        ))
    {
    }

    FQuestModelDomain::FQuestModelDomain(
        const FQuestModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        QuestGroupName(From.QuestGroupName),
        QuestName(From.QuestName),
        ParentKey(From.ParentKey)
    {

    }

    FQuestModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestModelDomain>& Self,
        const Request::FGetQuestModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->GetQuestModel(
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


        Gs2::Quest::Model::Cache::FQuestModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetQuestGroupName(),
            Request->GetQuestName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelDomain::FGetTask>> FQuestModelDomain::Get(
        Request::FGetQuestModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FQuestModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> QuestGroupName,
        TOptional<FString> QuestName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            (QuestName.IsSet() ? *QuestName : "null") + ":" +
            ChildType;
    }

    FString FQuestModelDomain::CreateCacheKey(
        TOptional<FString> QuestName
    )
    {
        return FString("") +
            (QuestName.IsSet() ? *QuestName : "null");
    }

    FQuestModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestModelDomain> Self
    ): Self(Self)
    {

    }

    FQuestModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->QuestGroupName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheKey(

            Self->QuestName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Quest::Model::FQuestModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Quest::Model::FQuestModelPtr Value;
                const auto CacheHit = Gs2::Quest::Model::Cache::FQuestModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->QuestGroupName,
                    Self->QuestName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Quest::Model::Cache::FQuestModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->QuestGroupName,
                    Self->QuestName,
                    TOptional<int32>(),
                    [Self](Gs2::Quest::Model::FQuestModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Quest::Request::FGetQuestModelRequest>()
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

    TSharedPtr<FAsyncTask<FQuestModelDomain::FModelTask>> FQuestModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestModelDomain::FModelTask>>(this->AsShared());
    }

    void FQuestModelDomain::Invalidate()
    {
        Gs2::Quest::Model::Cache::FQuestModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            QuestGroupName,
            QuestName,
            TOptional<int32>()
        );
    }

    FQuestModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FQuestModelDomain>& Self,
        TFunction<void(Gs2::Quest::Model::FQuestModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FQuestModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FQuestModelDomain::FSubscribeWithInitialCallTask>> FQuestModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Quest::Model::FQuestModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FQuestModelDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FQuestModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(

            NamespaceName,
            QuestGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheKey(

            QuestName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Quest::Domain::FGs2QuestDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryQuestGroupName = QuestGroupName;
        const TOptional<FString> QueryQuestName = QuestName;
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FQuestModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryQuestGroupName, QueryQuestName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FQuestModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryQuestGroupName,
                    QueryQuestName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FQuestModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheParentKey(

            NamespaceName,
            QuestGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestModelCache::CreateCacheKey(

            QuestName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
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
