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

#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/Like.h"
#include "Dictionary/Domain/Model/LikeAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"
#include "Dictionary/Model/Cache/EntryModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FEntryModelDomain::FEntryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> EntryModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        EntryModelName(EntryModelName),
        ParentKey(Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "EntryModel"
        ))
    {
    }

    FEntryModelDomain::FEntryModelDomain(
        const FEntryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        EntryModelName(From.EntryModelName),
        ParentKey(From.ParentKey)
    {

    }

    FEntryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FEntryModelDomain>& Self,
        const Request::FGetEntryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetEntryModel(
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


        Gs2::Dictionary::Model::Cache::FEntryModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryModelDomain::FGetTask>> FEntryModelDomain::Get(
        Request::FGetEntryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FEntryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> EntryModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (EntryModelName.IsSet() ? *EntryModelName : "null") + ":" +
            ChildType;
    }

    FString FEntryModelDomain::CreateCacheKey(
        TOptional<FString> EntryModelName
    )
    {
        return FString("") +
            (EntryModelName.IsSet() ? *EntryModelName : "null");
    }

    FEntryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FEntryModelDomain> Self
    ): Self(Self)
    {

    }

    FEntryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Dictionary::Model::Cache::FEntryModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Dictionary::Model::Cache::FEntryModelCache::CreateCacheKey(

            Self->EntryModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Dictionary::Model::FEntryModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Dictionary::Model::FEntryModelPtr Value;
                const auto CacheHit = Gs2::Dictionary::Model::Cache::FEntryModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->EntryModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Dictionary::Model::Cache::FEntryModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->EntryModelName,
                    TOptional<int32>(),
                    [Self](Gs2::Dictionary::Model::FEntryModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Dictionary::Request::FGetEntryModelRequest>()
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

    TSharedPtr<FAsyncTask<FEntryModelDomain::FModelTask>> FEntryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEntryModelDomain::FModelTask>>(this->AsShared());
    }

    void FEntryModelDomain::Invalidate()
    {
        Gs2::Dictionary::Model::Cache::FEntryModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            EntryModelName,
            TOptional<int32>()
        );
    }

    FEntryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FEntryModelDomain>& Self,
        TFunction<void(Gs2::Dictionary::Model::FEntryModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FEntryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FEntryModelDomain::FSubscribeWithInitialCallTask>> FEntryModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Dictionary::Model::FEntryModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FEntryModelDomain::Subscribe(
        TFunction<void(Gs2::Dictionary::Model::FEntryModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Dictionary::Model::Cache::FEntryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Dictionary::Model::Cache::FEntryModelCache::CreateCacheKey(

            EntryModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Dictionary::Domain::FGs2DictionaryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryEntryModelName = EntryModelName;
        return Gs2->Cache->Subscribe(
            Gs2::Dictionary::Model::FEntryModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Dictionary::Model::FEntryModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryEntryModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FEntryModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryEntryModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FEntryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Dictionary::Model::Cache::FEntryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Dictionary::Model::Cache::FEntryModelCache::CreateCacheKey(

            EntryModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Dictionary::Model::FEntryModel::TypeName,
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
