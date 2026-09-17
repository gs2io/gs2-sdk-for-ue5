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

#include "Chat/Domain/Model/CategoryModel.h"
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
#include "Chat/Model/Cache/CategoryModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FCategoryModelDomain::FCategoryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Category
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Category(Category),
        ParentKey(Gs2::Chat::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CategoryModel"
        ))
    {
    }

    FCategoryModelDomain::FCategoryModelDomain(
        const FCategoryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Category(From.Category),
        ParentKey(From.ParentKey)
    {

    }

    FCategoryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FCategoryModelDomain>& Self,
        const Request::FGetCategoryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FCategoryModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategory(Self->Category);
        const auto Future = Self->Client->GetCategoryModel(
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
        Gs2::Chat::Model::Cache::FCategoryModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetCategory().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCategoryModelDomain::FGetTask>> FCategoryModelDomain::Get(
        Request::FGetCategoryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FCategoryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int32> Category,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Category.IsSet() ? FString::FromInt(*Category) : "null") + ":" +
            ChildType;
    }

    FString FCategoryModelDomain::CreateCacheKey(
        TOptional<int32> Category
    )
    {
        return FString("") +
            (Category.IsSet() ? FString::FromInt(*Category) : "null");
    }

    FCategoryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FCategoryModelDomain> Self
    ): Self(Self)
    {

    }

    FCategoryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FCategoryModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Chat::Model::Cache::FCategoryModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Chat::Model::Cache::FCategoryModelCache::CreateCacheKey(

            Self->Category
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Chat::Model::FCategoryModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Chat::Model::FCategoryModelPtr Value;
                const auto CacheHit = Gs2::Chat::Model::Cache::FCategoryModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Category,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Chat::Model::Cache::FCategoryModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Category,
                    TOptional<int32>(),
                    [Self](Gs2::Chat::Model::FCategoryModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Chat::Request::FGetCategoryModelRequest>()
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

    TSharedPtr<FAsyncTask<FCategoryModelDomain::FModelTask>> FCategoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCategoryModelDomain::FModelTask>>(this->AsShared());
    }

    void FCategoryModelDomain::Invalidate()
    {
        Gs2::Chat::Model::Cache::FCategoryModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            Category,
            TOptional<int32>()
        );
    }

    FCategoryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FCategoryModelDomain>& Self,
        TFunction<void(Gs2::Chat::Model::FCategoryModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FCategoryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FCategoryModelDomain::FSubscribeWithInitialCallTask>> FCategoryModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Chat::Model::FCategoryModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FCategoryModelDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FCategoryModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FCategoryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FCategoryModelCache::CreateCacheKey(

            Category
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<int32> QueryCategory = Category;
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FCategoryModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FCategoryModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryCategory]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FCategoryModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryCategory
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FCategoryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FCategoryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FCategoryModelCache::CreateCacheKey(

            Category
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Chat::Model::FCategoryModel::TypeName,
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
