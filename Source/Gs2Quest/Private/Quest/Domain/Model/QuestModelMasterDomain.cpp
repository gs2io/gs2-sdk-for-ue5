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

#include "Quest/Domain/Model/QuestModelMaster.h"
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
#include "Quest/Model/Cache/QuestModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestModelMasterDomain::FQuestModelMasterDomain(
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
        ParentKey(Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            QuestGroupName,
            "QuestModelMaster"
        ))
    {
    }

    FQuestModelMasterDomain::FQuestModelMasterDomain(
        const FQuestModelMasterDomain& From
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

    FQuestModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestModelMasterDomain>& Self,
        const Request::FGetQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->GetQuestModelMaster(
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
            Request->GetQuestName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FGetTask>> FQuestModelMasterDomain::Get(
        Request::FGetQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FQuestModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FQuestModelMasterDomain>& Self,
        const Request::FUpdateQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->UpdateQuestModelMaster(
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
            Request->GetQuestName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FUpdateTask>> FQuestModelMasterDomain::Update(
        Request::FUpdateQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FQuestModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FQuestModelMasterDomain>& Self,
        const Request::FDeleteQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->DeleteQuestModelMaster(
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

              if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Quest::Model::Cache::FQuestModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetQuestGroupName(),
            Request->GetQuestName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FDeleteTask>> FQuestModelMasterDomain::Delete(
        Request::FDeleteQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FQuestModelMasterDomain::CreateCacheParentKey(
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

    FString FQuestModelMasterDomain::CreateCacheKey(
        TOptional<FString> QuestName
    )
    {
        return FString("") +
            (QuestName.IsSet() ? *QuestName : "null");
    }

    FQuestModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FQuestModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->QuestGroupName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheKey(

            Self->QuestName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Quest::Model::FQuestModelMasterPtr Value;
                const auto CacheHit = Gs2::Quest::Model::Cache::FQuestModelMasterCache::TryGet(
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
                const auto Error = Gs2::Quest::Model::Cache::FQuestModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->QuestGroupName,
                    Self->QuestName,
                    TOptional<int32>(),
                    [Self](Gs2::Quest::Model::FQuestModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Quest::Request::FGetQuestModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FModelTask>> FQuestModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FQuestModelMasterDomain::Invalidate()
    {
        Gs2::Quest::Model::Cache::FQuestModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            QuestGroupName,
            QuestName,
            TOptional<int32>()
        );
    }

    FQuestModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FQuestModelMasterDomain>& Self,
        TFunction<void(Gs2::Quest::Model::FQuestModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FQuestModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FQuestModelMasterDomain::FSubscribeWithInitialCallTask>> FQuestModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Quest::Model::FQuestModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FQuestModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FQuestModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            QuestGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheKey(

            QuestName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Quest::Domain::FGs2QuestDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryQuestGroupName = QuestGroupName;
        const TOptional<FString> QueryQuestName = QuestName;
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FQuestModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryQuestGroupName, QueryQuestName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FQuestModelMasterDomain>(
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

    void FQuestModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            QuestGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Quest::Model::Cache::FQuestModelMasterCache::CreateCacheKey(

            QuestName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FQuestModelMaster::TypeName,
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
