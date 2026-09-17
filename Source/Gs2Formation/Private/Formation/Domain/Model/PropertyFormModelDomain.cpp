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

#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"
#include "Formation/Model/Cache/PropertyFormModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FPropertyFormModelDomain::FPropertyFormModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PropertyFormModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        PropertyFormModelName(PropertyFormModelName),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "PropertyFormModel"
        ))
    {
    }

    FPropertyFormModelDomain::FPropertyFormModelDomain(
        const FPropertyFormModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PropertyFormModelName(From.PropertyFormModelName),
        ParentKey(From.ParentKey)
    {

    }

    FPropertyFormModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FPropertyFormModelDomain>& Self,
        const Request::FGetPropertyFormModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPropertyFormModelName(Self->PropertyFormModelName);
        const auto Future = Self->Client->GetPropertyFormModel(
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


        Gs2::Formation::Model::Cache::FPropertyFormModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetPropertyFormModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormModelDomain::FGetTask>> FPropertyFormModelDomain::Get(
        Request::FGetPropertyFormModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FPropertyFormModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PropertyFormModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PropertyFormModelName.IsSet() ? *PropertyFormModelName : "null") + ":" +
            ChildType;
    }

    FString FPropertyFormModelDomain::CreateCacheKey(
        TOptional<FString> PropertyFormModelName
    )
    {
        return FString("") +
            (PropertyFormModelName.IsSet() ? *PropertyFormModelName : "null");
    }

    FPropertyFormModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FPropertyFormModelDomain> Self
    ): Self(Self)
    {

    }

    FPropertyFormModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheKey(

            Self->PropertyFormModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Formation::Model::FPropertyFormModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Formation::Model::FPropertyFormModelPtr Value;
                const auto CacheHit = Gs2::Formation::Model::Cache::FPropertyFormModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->PropertyFormModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Formation::Model::Cache::FPropertyFormModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->PropertyFormModelName,
                    TOptional<int32>(),
                    [Self](Gs2::Formation::Model::FPropertyFormModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Formation::Request::FGetPropertyFormModelRequest>()
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

    TSharedPtr<FAsyncTask<FPropertyFormModelDomain::FModelTask>> FPropertyFormModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPropertyFormModelDomain::FModelTask>>(this->AsShared());
    }

    void FPropertyFormModelDomain::Invalidate()
    {
        Gs2::Formation::Model::Cache::FPropertyFormModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            PropertyFormModelName,
            TOptional<int32>()
        );
    }

    FPropertyFormModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FPropertyFormModelDomain>& Self,
        TFunction<void(Gs2::Formation::Model::FPropertyFormModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FPropertyFormModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FPropertyFormModelDomain::FSubscribeWithInitialCallTask>> FPropertyFormModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Formation::Model::FPropertyFormModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FPropertyFormModelDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FPropertyFormModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheKey(

            PropertyFormModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Formation::Domain::FGs2FormationDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryPropertyFormModelName = PropertyFormModelName;
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FPropertyFormModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FPropertyFormModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryPropertyFormModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FPropertyFormModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryPropertyFormModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FPropertyFormModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheKey(

            PropertyFormModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FPropertyFormModel::TypeName,
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
